#include <vector>
#include <iostream>

void printArray(std::vector<int>& array) {
    for (int i : array) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

bool checker(std::vector<int>& answer, std::vector<int>& orig, std::string s, std::string t) {
    int m = s.size();
    if (answer.size() != orig.size()) {
        std::cout << "Ошибка проверки\n" <<
            "Размеры ответов алгоритмов не совпадают.\nСтроки:\n" <<
            s << "\n" << t << "\n";
        return false;
    }
    for (int ind = 0; ind < answer.size(); ++ind) {
        for (int i = answer[ind]; i < answer[ind] + m; ++i) {
            if (s[i - answer[ind]] != '?' && s[i - answer[ind]] != t[i]) {
                std::cout << "Ошибка проверки\n" <<
                    "Некоторый индекс не является вхождением.\nСтроки:\n" <<
                    s << "\n" << t << "\n";
                return false;
            }
            if (answer[ind] != orig[ind]) {
                std::cout << "Ошибка проверки\n" <<
                    "Вхождения алгоритмов не совпали.\nСтроки:\n" <<
                    s << "\n" << t << "\n";
            }
        }
    }
    return true;
}
