#ifndef SESSION_HPP
#define SESSION_HPP

#include <boost/asio.hpp>
#include <string>
#include <memory>
#include <mutex>
#include <string_view>
#include "SessionController.hpp"

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket);
    void start();

private:
    void do_read();
    void do_write(std::string_view message);

    SessionController _controller;
    tcp::socket _socket;
    boost::asio::streambuf _buffer { };
    std::string _streamStr;
};

#endif // NETWORK_SESSION_H
