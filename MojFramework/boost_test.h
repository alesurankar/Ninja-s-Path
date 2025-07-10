#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <string>

using namespace boost;


void test_asio()
{
    asio::io_context io;
    asio::ip::tcp::resolver resolver(io);
    std::cout << "[ASIO]\n";
}

void test_beast()
{
    beast::http::request<beast::http::string_body> req{ beast::http::verb::get, "/", 11 };
    req.set(beast::http::field::host, "localhost");
    std::cout << "[BEAST]\n";
}

void test_json()
{
    const char* json_str = R"({"hello": "world"})";
    json::value jv = json::parse(json_str);
    std::cout << "[JSON] Parsed: " << jv.at("hello").as_string() << "\n";
}