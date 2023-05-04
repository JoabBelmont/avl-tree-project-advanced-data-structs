#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "avl.hpp"
using namespace std;

void csvToVector(string fileName) {
    std::ifstream file(fileName); // Open the CSV file

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    std::string line;
    std::vector<std::vector<std::string>> data; // Store the CSV data

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::vector<std::string> row;
        std::string cell;

        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    file.close(); // Close the file

    return;
}

int main() {
    avl_tree<int> t1;
    avl_tree<string> t2;
    avl_tree<Date> t3;

    for (int i = 1; i <= 20; i++)
        t1.add(i);

    t2.add("a"); t2.add("b"); t2.add("c");
    t2.add("d"); t2.add("e"); t2.add("f");
    t2.add("g"); t2.add("h"); t2.add("i");
    t2.add("j"); t2.add("k"); t2.add("l");
    t2.add("m"); t2.add("n"); t2.add("o");
    t2.add("p"); t2.add("q"); t2.add("r");
    t2.add("s"); t2.add("t"); t2.add("u");
    t2.add("v"); t2.add("w"); t2.add("x");

    for (int i = 1; i <= 20; i++)
        t3.add(Date(i, i, i));

    t1.bshow(); cout << endl;
    t2.bshow(); cout << endl;
    t3.bshow(); cout << endl;

    // csvToVector("test.csv");
}
