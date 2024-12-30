#include "Network.hpp"
#include <iostream>

tcp::socket connect_to_server(boost::asio::io_context& context, const std::string& server_address, int server_port) {
    tcp::socket socket(context);
    tcp::resolver resolver(context);
    boost::asio::connect(socket, resolver.resolve(server_address, std::to_string(server_port)));
    return socket;
}

void send_request(tcp::socket& socket) {
    uint8_t request_type = 1; // Stream All Packets
    boost::asio::write(socket, boost::asio::buffer(&request_type, sizeof(request_type)));
}

json receive_data(tcp::socket& socket) {
    json result = json::array();
    boost::system::error_code ec;

    std::vector<uint8_t> buffer(17); // Each packet is 17 bytes
    while (boost::asio::read(socket, boost::asio::buffer(buffer), ec)) {
        if (ec == boost::asio::error::eof) {
            break; // Connection closed by server
        }

        // Parse the packet
        std::string symbol(buffer.begin(), buffer.begin() + 4);
        char buy_sell = buffer[4];
        int quantity = ntohl(*reinterpret_cast<int32_t*>(&buffer[5]));
        int price = ntohl(*reinterpret_cast<int32_t*>(&buffer[9]));
        int sequence = ntohl(*reinterpret_cast<int32_t*>(&buffer[13]));

        result.push_back({{"symbol", symbol}, {"buy_sell", buy_sell}, {"quantity", quantity}, {"price", price}, {"sequence", sequence}});
    }

    return result;
}
