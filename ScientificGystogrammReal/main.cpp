#include "Gyst.hpp"
#include "Parser.hpp"
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Usage: ./program_name input_file output_file" << std::endl;
        return 0;
    }

    std::ifstream input_file;
    input_file.open(argv[1]);
    if (!input_file.is_open()) {
        std::cout << "Could not open input file " << argv[1] << std::endl;
        return 0;
    }

    std::ofstream output_file(argv[2]);
    if (!output_file.is_open()) {
        std::cout << "Could not open output file " << argv[2] << std::endl;
        return 0;
    }

    try {
        int min, max, count;
        std::cin >> min >> max >> count;
        std::vector<int> data = Parser::parse(input_file);
        Gyst gyst(min, max, count, data);
        output_file << "Keys/Values\n" << gyst.string_format();
    }
    catch (const std::exception& e) {
        std::cout << e.what();
    }
    input_file.close();
    output_file.close();
}