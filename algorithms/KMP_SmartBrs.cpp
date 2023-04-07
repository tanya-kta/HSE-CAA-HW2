#include "KMP_StandardBr.cpp"

std::vector<int> calcBrs(std::string s, uint64_t *oper) {
    int n = s.length();
    std::vector<int> br = calcBr(s, oper), brs(n);
    for (int i = 1; i < n; ++i) {
        if (br[i] > 0) {
            *oper += 1;
            if (i == n - 1 || (s[i + 1] != '?' && s[br[i]] != '?' &&
                               s[br[i]] != s[i + 1])) {
                brs[i] = br[i];
            } else {
                brs[i] = brs[br[i] - 1];
            }
        }
    }
    return brs;
}

std::vector<int> smartKmp(std::string s, std::string t, uint64_t *oper) {
    int n = s.length();
    std::vector<int> brs = calcBrs(s, oper);
    int num = 0;
    int m = t.length();
    std::vector<int> answer;
    for (int i = 0; i < m; ++i) {
        *oper += 1;
        while (num > 0 && s[num] != '?' && t[i] != s[num]) {
            *oper += 1;
            num = brs[num - 1];
        }
        *oper += 1;
        if (s[num] == '?' || t[i] == s[num]) {
            ++num;
        }
        if (num == n) {
            answer.push_back(i - num + 1);
            num = brs[num - 1];
        }
    }
    return answer;
}
