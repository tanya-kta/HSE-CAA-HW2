#include <vector>
#include <string>

std::vector<int> calcBr(std::string s, uint64_t *oper) {
    int n = s.length();
    std::vector<int> br(n);
    for (int i = 1; i < n; ++i) {
        int prev = br[i - 1];
        *oper += 1;
        while (prev > 0 && s[i] != '?' && s[prev] != '?' && s[i] != s[prev]) {
            *oper += 1;
            prev = br[prev - 1];
        }
        *oper += 1;
        if (s[i] == '?' || s[prev] == '?' || s[i] == s[prev]) {
            ++prev;
        }
        br[i] = prev;
    }
    return br;
}

std::vector<int> standardKmp(std::string s, std::string t, uint64_t *oper) {
    int n = s.length();
    std::vector<int> br = calcBr(s, oper);
    int num = 0;
    int m = t.length();
    std::vector<int> answer;
    for (int i = 0; i < m; ++i) {
        *oper += 1;
        while (num > 0 && s[num] != '?' && t[i] != s[num]) {
            *oper += 1;
            num = br[num - 1];
        }
        *oper += 1;
        if (s[num] == '?' || t[i] == s[num]) {
            ++num;
        }
        if (num == n) {
            answer.push_back(i - num + 1);
            num = br[num - 1];
        }
    }
    return answer;
}
