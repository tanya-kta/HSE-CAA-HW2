#include <vector>
#include <string>

std::vector<int> calcBr(std::string s) {
    int n = s.length();
    std::vector<int> br(n);
    for (int i = 1; i < n; ++i) {
        int prev = br[i - 1];
        while (prev > 0 && s[i] != '?' && s[prev] != '?' && s[i] != s[prev]) {
            prev = br[prev - 1];
        }
        if (s[i] == '?' || s[prev] == '?' || s[i] == s[prev]) {
            ++prev;
        }
        br[i] = prev;
    }
    return br;
}

std::vector<int> standardKmp(std::string s, std::string t) {
    int n = s.length();
    std::vector<int> br = calcBr(s);
    int num = 0;
    int m = t.length();
    std::vector<int> answer;
    for (int i = 0; i < m; ++i) {
        while (num > 0 && s[num] != '?' && t[i] != s[num]) {
            num = br[num - 1];
        }
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
