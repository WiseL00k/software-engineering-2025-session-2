#include "Similarity.h"
#include <vector>
#include <algorithm>

int Similarity::lcsLength(const std::string &a, const std::string &b) {
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

double Similarity::calculate(const std::string &text1, const std::string &text2) {
    if (text1.empty()) return 0.0;
    int lcs = lcsLength(text1, text2);
    return static_cast<double>(lcs) / text1.size();
}