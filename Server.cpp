#include "Include/Server.hpp"
#include "Include/Session.hpp"

Server::Server(boost::asio::io_service& io_context, short port)
    : _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
    do_accept();
}

// не могу понять почему не рекурсия
void Server::do_accept()
{
    _acceptor.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<Session>(std::move(socket))->start();
            }
            do_accept();
        });
}

