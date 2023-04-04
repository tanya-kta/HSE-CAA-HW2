#include <vector>
#include <iostream>

void printArray(std::vector<int>& array) {
    for (int i : array) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

bool checker(std::vector<int>& naive_ans, std::vector<int>& stand_kmp,
             std::vector<int>& smart_kmp, std::string s, std::string t) {
    if (naive_ans.size() != stand_kmp.size() || naive_ans.size() != smart_kmp.size()) {
        std::cout << "Количества найденных вхождений от разных алгоритмов не совпадают\nСтроки:\n" <<
            s << "\n" << t << "\n";
        return false;
    }
    int n = naive_ans.size();
    for (int i = 0; i < n; ++i) {
        if (naive_ans[i] != stand_kmp[i] || naive_ans[i] != smart_kmp[i]) {
            std::cout << "Индексы вхождения от разных алгоритмов не совпадают\nСтроки:\n" <<
                s << "\n" << t << "\n";
            return false;
        }
    }
    int m = s.size();
    for (auto ind : naive_ans) {
        for (int i = ind; i < ind + m; ++i) {
            if (s[i - ind] != t[i]) {
                std::cout << "Некоторый индекс не является вхождением\nСтроки:\n" <<
                    s << "\n" << t << "\n";
                return false;
            }
        }
    }
    return true;
}
