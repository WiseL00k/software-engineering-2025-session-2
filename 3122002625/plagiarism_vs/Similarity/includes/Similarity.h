#ifndef SIMILARITY_H
#define SIMILARITY_H

#include <string>
#include <vector>


class Similarity {
public:

    typedef enum {
        LCS,                    // 最长公共子序列（Longest Common Subsequence），基础版
        LCS_OPTIMIZED,          // 最长公共子序列（优化版，降低内存占用）
        LCS_OPTIMIZED_PLUS,     // 增强版 LCS（分块 + 一维 DP，适合长文本）
    } algorithm_type;

    /**
     * @brief 计算两个文本的重复率（相似度）
     * @param text1 原文
     * @param text2 抄袭版
     * @return 相似度 [0,1]，保留小数两位
     */
    static double calculate(const std::string &text1, const std::string &text2, algorithm_type type = LCS);


private:
    /**
     * @brief 计算最长公共子序列 (LCS) 的长度
     * @param s1 字符串1
     * @param s2 字符串2
     * @return LCS 长度
     */
    static int lcsLength(const std::string &a, const std::string &b);

    /**
     * @brief 计算最长公共子序列 (LCS) 的长度(优化版)
     * @param s1 字符串1
     * @param s2 字符串2
     * @return LCS 长度
     */
    static int lcsLengthOptimized(const std::string& a, const std::string& b);

    /**
     * @brief 增强版 LCS（分块 + 一维 DP，适合长文本）
     * @param a 字符串1
     * @param b 字符串2
     * @return LCS 长度
     */
    static int lcsLengthOptimizedPlus(const std::string& a, const std::string& b);
};

#endif // SIMILARITY_H