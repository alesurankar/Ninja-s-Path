#include "TCP_Client.h"
#include <chrono>
#include <thread>

using namespace boost;

TCP_Client::TCP_Client(asio::io_context& io_in, const std::string& host_in, unsigned short port_in, const std::string& username_in, std::shared_ptr<MessageHandler> msgHandler_in)
    :
    socket(io_in),
    username(username_in),
    host(host_in),
    port(port_in),
    msgHandler(msgHandler_in),
    timer(io_in)
{}


void TCP_Client::Start()
{
    //std::cout << "NetworkingThread::TCP_Client::Start\n\n";
    auto self = shared_from_this();
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(host), port);

    socket.async_connect(endpoint, [this, self](boost::system::error_code ec)
        {
            if (!ec)
            {
                boost::asio::ip::tcp::no_delay option(true);
                socket.set_option(option);
                //SendUsername();
                ReceiveMessages();
                CheckAndSend();
            }
            else
            {
                //std::cerr << "Connect failed: " << ec.message() << "\n";
            }
        });
}


//void TCP_Client::SendUsername()
//{
//    //std::string first_command = "UP";
//    //std::cout << "TCP_Client::SendUsername: " << first_command << "\n";
//    //asio::write(socket, asio::buffer(first_command + "\n"));
//    std::cout << "TCP_Client::SendUsername: "<< username << "\n";
//    asio::write(socket, asio::buffer(username + "\n"));
//}


void TCP_Client::ReceiveMessages() //12. Client(TCP)
{
    auto self = shared_from_this();
    boost::asio::async_read_until(socket, input_buffer, '\n',    //12. Client(TCP)
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                std::istream is(&input_buffer);
                std::string msg;
                std::getline(is, msg);

                //std::cout << "Step 12, TCP_Client::ReadMessage::Received: " << msg << "\n";

                size_t commaPos = msg.find(',');
                if (commaPos != std::string::npos)
                {
                    int x = std::stoi(msg.substr(0, commaPos));
                    int y = std::stoi(msg.substr(commaPos + 1));
                    //std::cout << "Step 12, converted: " << "x = " << x << ", y = " << y << "\n";
                    msgHandler->ClientToMSG(x, y); //13. MSGClient(middleman)
                }
                else
                {
                    //std::cout << "Invalid coordinate format: " << msg << "\n";
                }
                ReceiveMessages();
            }
            else
            {
                //Shutdown();
            }
        });
    //std::cout << "Step 12--------------\n";
}


void TCP_Client::CheckAndSend() //3. Client(TCP)
{
    //std::cout << "TCP_Client::CheckAndSendMessage: " << ", Step 3. Client(TCP)\n";
    auto self = shared_from_this();
    msg = msgHandler->MSGToClient();   //3. Client(TCP)
    if (!msg.empty())
    {
        boost::asio::async_write(socket, boost::asio::buffer(msg),
            [this, self](const boost::system::error_code& ec, std::size_t)
            {
                if (!ec)
                {
                    //std::cout << "Step 4: NetworkingThread::TCP_Client::CheckAndSendMessage: " << msg;
                }
                else
                {
                    //std::cerr << "Send error: " << ec.message() << "\n";
                    //Shutdown();
                    return;
                }
                boost::asio::post(socket.get_executor(), [this, self]()
                    {
                        CheckAndSend();
                    });
                //std::cout << "Step4--------------\n";
            });
    }
    else
    {
        timer.expires_after(std::chrono::milliseconds(2));
        timer.async_wait([this, self](boost::system::error_code ec)
            {
                if (!ec)
                {
                    CheckAndSend();
                }
            });
    }
}


//void TCP_Client::Shutdown()
//{
//    std::cout << "TCP_Client::Shutdown:\n";
//    try
//    {
//        socket.cancel();
//        socket.shutdown(asio::ip::tcp::socket::shutdown_both); 
//    }
//    catch (const system::system_error& e)
//    {
//        std::cout << "Shutdown failed: " << e.what() << "\n";
//    }
//    socket.close();
//}
