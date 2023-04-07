#include <vector>
#include <string>

std::vector<int> naive(std::string s, std::string t, uint64_t *oper) {
    int n = s.size(), m = t.size();
    std::vector<int> answer;
    for (int i = 0; i <= m - n; ++i) {
        bool status = true;
        for (int j = 0; j < n && status; ++j) {
            *oper += 2;
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
