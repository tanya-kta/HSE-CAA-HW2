#include <vector>
#include <iostream>

void printArray(std::vector<int>& array) {
    for (int i : array) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

bool checker(std::vector<int>& answer, std::string s, std::string t) {
    int m = s.size();
    for (auto ind : answer) {
        for (int i = ind; i < ind + m; ++i) {
            if (s[i - ind] != t[i]) {
                std::cout << "Ошибка проверки\n" <<
                    "Некоторый индекс не является вхождением.\nСтроки:\n" <<
                    s << "\n" << t << "\n";
                return false;
            }
        }
    }
    return true;
}
