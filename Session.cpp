#include <sstream>
#include <memory>
#include "Include/Session.hpp"


Session::Session(tcp::socket socket)
    : _socket(std::move(socket))
{
}

void Session::start()
{
    do_read();
}

// копится же список вызовов do_read, на стеке  
void Session::do_read()
{
    auto self(shared_from_this());
    boost::asio::async_read_until(_socket, _buffer, '\n',
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                _buffer.commit(length);
                std::string str;
                std::istream is(&_buffer);
                std::getline(is, str);
                _buffer.consume(length);
                do_write(_controller.process(str));
            }
        });
}

void Session::do_write(std::string_view message) 
{
  auto self(shared_from_this());
  _socket.async_write_some(
      boost::asio::buffer(message),
      [this, self](auto const &ec, size_t) {
        if (!ec) {
            do_read();
        }
      });
}