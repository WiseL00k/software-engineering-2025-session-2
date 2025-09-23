// Similarity.cpp : 定义静态库的函数。
//

#include "pch.h"
#include "framework.h"
#include "Similarity.h"
#include <vector>
#include <algorithm>

int Similarity::lcsLength(const std::string& a, const std::string& b) {
    int n = a.size();
    int m = b.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
}

int Similarity::lcsLengthOptimized(const std::string& a, const std::string& b) {
    int n = a.size();
    int m = b.size();

    if (m > n) return lcsLengthOptimized(b, a); // 确保 b 是更短的

    std::vector<int> dp(m + 1, 0);
    int prev, tmp;

    for (int i = 1; i <= n; i++) {
        prev = 0;
        for (int j = 1; j <= m; j++) {
            tmp = dp[j]; // dp[i-1][j]
            if (a[i - 1] == b[j - 1]) {
                dp[j] = prev + 1;
            }
            else {
                dp[j] = std::max(dp[j], dp[j - 1]);
            }
            prev = tmp; // 更新左上角
        }
    }
    return dp[m];
}

int Similarity::lcsLengthOptimizedPlus(const std::string& a, const std::string& b) {
    int n = a.size(), m = b.size();
    if (n == 0 || m == 0) return 0;

    // 确保 b 是更短的
    const std::string* longStr = &a;
    const std::string* shortStr = &b;
    if (m > n) std::swap(longStr, shortStr);

    int lenLong = longStr->size();
    int lenShort = shortStr->size();

    std::vector<int> dp(lenShort + 1, 0);
    int prev, tmp;

    for (int i = 1; i <= lenLong; ++i) {
        prev = 0;
        for (int j = 1; j <= lenShort; ++j) {
            tmp = dp[j];
            if ((*longStr)[i - 1] == (*shortStr)[j - 1]) dp[j] = prev + 1;
            else dp[j] = std::max(dp[j], dp[j - 1]);
            prev = tmp;
        }
    }

    return dp[lenShort]; // 返回 LCS 长度
}


double Similarity::calculate(const std::string& text1, const std::string& text2, algorithm_type type) {
    if (text1.empty()) return -1.0;
    int lcs;
    switch (type)
    {
    case LCS:
        lcs = lcsLength(text1, text2);
        break;
    case LCS_OPTIMIZED:
        lcs = lcsLengthOptimized(text1, text2);
        break;
    case LCS_OPTIMIZED_PLUS:
        lcs = lcsLengthOptimizedPlus(text1, text2);
        break;
    default:
        break;
    }
    
    return static_cast<double>(lcs) / text1.size();
}