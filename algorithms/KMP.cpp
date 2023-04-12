#include <vector>
#include <string>

std::vector<int> calcBr(std::string s, uint64_t *oper) {
    int n = s.length();
    std::vector<int> br(n);
    for (int i = 1; i < n; ++i) {
        int prev = br[i - 1];
        *oper += 1;
        while (prev > 0 && s[i] != s[prev]) {
            *oper += 1;
            prev = br[prev - 1];
        }
        *oper += 1;
        if (s[i] == s[prev]) {
            ++prev;
        }
        br[i] = prev;
    }
    return br;
}

std::vector<int> calcBrs(std::string s, uint64_t *oper) {
    int n = s.length();
    std::vector<int> brs = calcBr(s, oper);
    for (int i = 1; i < n; ++i) {
        if (brs[i] > 0) {
            *oper += 1;
            if (i < n - 1 && s[brs[i]] == s[i + 1]) {
                brs[i] = brs[brs[i] - 1];
            }
        }
    }
    return brs;
}

std::vector<int> algorithmKmp(std::string s, std::string t,
                              std::vector<int> (*preff)(std::string s, uint64_t *oper),
                              uint64_t *oper) {
    int n = s.length();
    int num = 0;
    int m = t.length();
    std::vector<int> br = preff(s, oper);
    std::vector<int> answer;
    for (int i = 0; i < m; ++i) {
        *oper += 1;
        while (num > 0 && t[i] != s[num]) {
            *oper += 1;
            num = br[num - 1];
        }
        *oper += 1;
        if (t[i] == s[num]) {
            ++num;
        }
        if (num == n) {
            answer.push_back(i - num + 1);
            num = br[num - 1];
        }
    }
    return answer;
}

std::vector<std::string> splitting(std::string s) {
    std::vector<std::string> split;
    int id = s.find('?');
    while (id != std::string::npos) {
        split.push_back(s.substr(0, id));
        s = s.substr(id + 1, std::string::npos);
        id = s.find('?');
    }
    split.push_back(s);
    return split;
}

/*
 * ab?ab
 * abbabab
 */

std::vector<int> runKmp(std::string s, std::string t,
                        std::vector<int> (*preff)(std::string s, uint64_t *oper), uint64_t *oper) {
    std::vector<std::string> split = splitting(s);
    std::vector<std::vector<int>> entries;
    for (int i = 0; i < split.size(); ++i) {
        entries.push_back(algorithmKmp(split[i], t, preff, oper));
    }
    if (entries.size() == 1) {
        return entries[0];
    }
    std::vector<int> merged(entries[0]);
    int sz = split[0].size() + 1;
    std::for_each(merged.begin(), merged.end(), [&sz](int &n){ n += sz; });
    for (int i = 1; i < entries.size(); ++i) {
        std::vector<int> v_intersection;
        std::set_intersection(merged.begin(), merged.end(), entries[i].begin(), entries[i].end(),
                              std::back_inserter(v_intersection));
        merged = v_intersection;
        sz = split[i].size() + 1;
        std::for_each(merged.begin(), merged.end(), [&sz](int &n){ n += sz; });
    }
    sz = s.size() + 1;
    std::for_each(merged.begin(), merged.end(), [&sz](int &n){ n -= sz; });
    return merged;
}
