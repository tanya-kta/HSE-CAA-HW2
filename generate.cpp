#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

std::string binaryText(int size) {
    std::srand(std::time(nullptr));
    std::string array;
    for (int i = 0; i < size; ++i) {
        array += std::rand() % 2 + '0';
    }
    return array;
}

std::string dnaText(int size) {
    std::srand(std::time(nullptr));
    std::string dna = "ATCG";
    std::string array;
    for (int i = 0; i < size; ++i) {
        array += dna[std::rand() % 4];
    }
    return array;
}

std::vector<std::string> getSamples(std::string text) {
    std::srand(std::time(nullptr));
    std::vector<std::string> samples;
    for (int size = 100; size <= 3000; size += 100) {
        samples.push_back(text.substr(std::rand() % (text.size() - size), size));
    }
    return samples;
}

std::vector<int> getIdToInsert(int size) {
    std::srand(std::time(nullptr));
    std::vector<int> ids;
    for (int i = 0; i <= 4;) {
        int val = std::rand() % size;
        if (std::find(std::begin(ids), std::end(ids), val) == std::end(ids)) {
            ids.push_back(val);
            ++i;
        }
    }
    return ids;
}
