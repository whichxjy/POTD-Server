#pragma once

#include <string>
#include <fstream>
#include <vector>

class Potd {
public:
    // Constructor
    Potd(const std::string& filename);

    // Get a random poem from the file
    std::string getRandomPoem();

private:
    // Poems
    std::vector<std::string> poems;
};