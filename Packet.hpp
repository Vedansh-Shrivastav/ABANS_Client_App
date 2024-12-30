#ifndef PACKET_HPP
#define PACKET_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Define the Packet struct
struct Packet {
    std::string symbol; // 4-character symbol
    char buy_sell;      // Buy/Sell indicator
    int quantity;       // Quantity
    int price;          // Price
    int sequence;       // Sequence number

    // Parse a Packet from a buffer
    static Packet from_buffer(const std::vector<char>& buffer, size_t offset);

    // Convert the Packet to a JSON object
    json to_json() const;

private:
    // Helper to parse a 4-byte big-endian integer
    static int parse_int(const std::vector<char>& buffer, size_t offset);
};

#endif // PACKET_HPP
