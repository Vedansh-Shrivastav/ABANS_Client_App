/**
 * Instructions to Compile and Run:
 * 
 * 1. Ensure Boost and nlohmann-json libraries are installed on your system.
 *    - For macOS with Homebrew:
 *      `brew install boost nlohmann-json`
 *
 * 2. Compile the code using the following command:
 *    g++ -std=c++17 -I/opt/homebrew/opt/boost/include -I/opt/homebrew/opt/nlohmann-json/include \
 *        Main.cpp Network.cpp Packet.cpp -o Client -L/opt/homebrew/opt/boost/lib -lboost_system
 *
 * 3. Run the compiled executable:
 *    ./Client
 *
 * 4. After running, the program will save the received data to a file named "output.json".
 */

#include "Network.hpp"
#include "Packet.hpp"
#include <iostream>  // For std::cout and std::cerr
#include <fstream>   // For std::ofstream


int main() {
    const std::string server_address = "127.0.0.1";
    const int server_port = 3000;

    try {
        boost::asio::io_context context;
        tcp::socket socket = connect_to_server(context, server_address, server_port);

        send_request(socket);
        json data = receive_data(socket);

        std::ofstream file("output.json");
        file << data.dump(4);
        file.close();

        std::cout << "Data received and saved to output.json.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
