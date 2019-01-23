#include "Potd.h"
#include <ctime>
#include <iostream>

Potd::Potd(const std::string& filename) {
    std::ifstream file;
    file.open(filename);

    if (file.is_open()) {
        std::string line;
        std::string reading;

        while (std::getline(file, line)) {
            if (line != "%") {
                // Keeping reading the poem
                reading += line + "\n";
            }
            else {
                // Finish reading a poem
                std::cout << reading << std::endl;
                poems.push_back(reading);
                reading = "";
            }
        }
    }
}

std::string Potd::getRandomPoem() {
    srand(time(NULL));
    return poems[rand() % poems.size()];
}