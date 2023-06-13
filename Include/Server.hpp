#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>

#include <mutex>

using boost::asio::ip::tcp;

class Server
{
public:
    Server(boost::asio::io_service& io_context, short port);

private:
    void do_accept();

    tcp::acceptor _acceptor;
};

#endif