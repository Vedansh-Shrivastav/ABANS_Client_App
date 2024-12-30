#include "Packet.hpp"

Packet Packet::from_buffer(const std::vector<char>& buffer, size_t offset) {
    Packet packet;

    // Extract fields from the buffer
    packet.symbol = std::string(buffer.begin() + offset, buffer.begin() + offset + 4); // Symbol (4 bytes)
    packet.buy_sell = buffer[offset + 4];                                             // Buy/Sell (1 byte)
    packet.quantity = parse_int(buffer, offset + 5);                                  // Quantity (4 bytes)
    packet.price = parse_int(buffer, offset + 9);                                     // Price (4 bytes)
    packet.sequence = parse_int(buffer, offset + 13);                                 // Sequence (4 bytes)

    return packet;
}

json Packet::to_json() const {
    return {
        {"symbol", symbol},
        {"buy_sell", std::string(1, buy_sell)},
        {"quantity", quantity},
        {"price", price},
        {"sequence", sequence}
    };
}

int Packet::parse_int(const std::vector<char>& buffer, size_t offset) {
    return (static_cast<unsigned char>(buffer[offset]) << 24) |
           (static_cast<unsigned char>(buffer[offset + 1]) << 16) |
           (static_cast<unsigned char>(buffer[offset + 2]) << 8) |
           static_cast<unsigned char>(buffer[offset + 3]);
}
