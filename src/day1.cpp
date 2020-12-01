#include <fstream>
#include <iostream>
#include <vector>

void day1() {
    std::ifstream input("../data/day1.txt");
    unsigned int tmp;
    std::vector<unsigned int> input_data; 
    while ( input >> tmp) {
        input_data.push_back(tmp);
    }
    for(auto val1: input_data) {
        for(auto val2: input_data) {
            for(auto val3: input_data) {
                if(2020 == (val1 + val2 + val3)) {
                    std::cout << val1 << " " << val2 << " " << val3 << std::endl;
                    std::cout << val1 * val2 * val3<< std::endl;
                    return;
                }
            }
        }
    }
}
