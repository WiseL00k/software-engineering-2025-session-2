#ifndef SIMILARITY_H
#define SIMILARITY_H

#include <string>

class Similarity {
public:
    /**
     * @brief 计算两个文本的重复率（相似度）
     * @param text1 原文
     * @param text2 抄袭版
     * @return 相似度 [0,1]，保留小数两位
     */
    static double calculate(const std::string &text1, const std::string &text2);

private:
    /**
     * @brief 计算最长公共子序列 (LCS) 的长度
     * @param s1 字符串1
     * @param s2 字符串2
     * @return LCS 长度
     */
    static int lcsLength(const std::string &a, const std::string &b);
};

#endif // SIMILARITY_H