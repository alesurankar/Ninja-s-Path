#pragma once
#define _WIN32_WINNT 0x0A00
#include "MessageHandler.h"
#include <boost/asio.hpp>
#include <string>
#include <atomic>
#include <mutex>

class TCP_Client : public std::enable_shared_from_this<TCP_Client>
{
public:
    TCP_Client(boost::asio::io_context& io_in, const std::string& host_in, unsigned short port_in, const std::string& username_in, std::shared_ptr<MessageHandler> msgHandler_in);
    void Start();
private:
    //    void SendUsername();
    void ReceiveMessages();
    void CheckAndSend();
    //    void Shutdown();
private:
    boost::asio::ip::tcp::socket socket;
    std::string username;
    std::string host;
    unsigned short port;
    std::shared_ptr<MessageHandler> msgHandler;
    boost::asio::steady_timer timer;
    std::string msg;
    boost::asio::streambuf input_buffer;
    //    std::mutex mtx;
    //    std::queue<std::string> command_queue;
    //    boost::asio::steady_timer message_timer; 
};