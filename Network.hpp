#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <string>

using boost::asio::ip::tcp;
using nlohmann::json;

tcp::socket connect_to_server(boost::asio::io_context& context, const std::string& server_address, int server_port);
void send_request(tcp::socket& socket);
json receive_data(tcp::socket& socket);

#endif