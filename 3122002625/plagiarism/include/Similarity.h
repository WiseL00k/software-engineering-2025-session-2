#ifndef SIMILARITY_H
#define SIMILARITY_H

#include <string>

class Similarity {
public:
    // 计算两个字符串的重复率
    static double calculate(const std::string &text1, const std::string &text2);

private:
    // 求两个字符串的最长公共子序列长度
    static int lcsLength(const std::string &a, const std::string &b);
};

#endif // SIMILARITY_H