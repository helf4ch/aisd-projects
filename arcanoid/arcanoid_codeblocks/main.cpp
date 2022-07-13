#include <fstream>
#include <vector>
#include <string>

#include "arcanoid.h"

void addLevel(const std::string &filename, std::vector<Arcanoid::Level> &levels) {
    std::ifstream fin;
    fin.open(filename);
    levels.emplace_back(fin);
    fin.close();
}

int main() {
    std::vector<Arcanoid::Level> levels;

    addLevel("level1.txt", levels);
    addLevel("level2.txt", levels);
    addLevel("level3.txt", levels);

    Arcanoid::Game(levels).run();
}
