#include <vector>
#include <string>

std::vector<int> naive(std::string s, std::string t) {
    int n = s.size(), m = t.size();
    std::vector<int> answer;
    for (int i = 0; i <= m - n; ++i) {
        bool status = true;
        for (int j = 0; j < n && status; ++j) {
            if (s[j] != '?' && t[i + j] != s[j]) {
                status = false;
            }
        }
        if (status) {
            answer.push_back(i);
        }
    }
    return answer;
}
