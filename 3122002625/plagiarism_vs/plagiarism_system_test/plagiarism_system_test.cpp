#include "pch.h" // 预编译头 (VS 自动生成)
#include "CppUnitTest.h"
#include "../Similarity/includes/Similarity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSimilarity
{
    TEST_CLASS(SimilarityTests)
    {
    public:

        TEST_METHOD(BothEmpty)
        {
            Assert::AreEqual(0.0, Similarity::calculate("", ""), 1e-9, L"BothEmpty failed");
        }

        TEST_METHOD(PlagiarizedEmpty)
        {
            Assert::AreEqual(0.0, Similarity::calculate("今天是星期天，天气晴。", ""), 1e-9, L"PlagiarizedEmpty failed");
        }

        TEST_METHOD(Identical)
        {
            Assert::AreEqual(1.0, Similarity::calculate("Hello world!", "Hello world!"), 1e-9, L"Identical failed");
        }

        TEST_METHOD(ChineseSynonym)
        {
            double sim = Similarity::calculate("今天是星期天，天气晴。", "今天是周天，天气晴朗。");
            Assert::IsTrue(sim >= 0.3 && sim <= 1.0, L"ChineseSynonym failed");
        }

        TEST_METHOD(Insertions)
        {
            Assert::AreEqual(1.0, Similarity::calculate("abcdefg", "axbyczdefg"), 1e-9, L"Insertions failed");
        }

        TEST_METHOD(Deletions)
        {
            double sim = Similarity::calculate("The quick brown fox jumps over the lazy dog", "quick fox over lazy");
            Assert::IsTrue(sim > 0.1 && sim < 1.0, L"Deletions failed");
        }

        TEST_METHOD(RepeatedChars)
        {
            std::string a(1000, 'a');
            std::string b(1000, 'a');
            Assert::AreEqual(1.0, Similarity::calculate(a, b), 1e-9, L"RepeatedChars failed");
        }

        TEST_METHOD(SingleChar)
        {
            Assert::AreEqual(0.0, Similarity::calculate("x", "y"), 1e-9, L"SingleChar failed");
        }

        TEST_METHOD(Multiline)
        {
            double sim = Similarity::calculate("Line1\nLine2\nLine3", "Line1\nLineX\nLine3");
            Assert::IsTrue(sim > 0.3 && sim < 1.0, L"Multiline failed");
        }

        TEST_METHOD(MixedLang)
        {
            double sim = Similarity::calculate("今天 is sunny.", "今日 is sunny.");
            Assert::IsTrue(sim > 0.2 && sim <= 1.0, L"MixedLang failed");
        }

        TEST_METHOD(LongTextDoesNotCrash)
        {
            std::string a(20000, 'A');
            std::string b(20000, 'A');
            double sim = Similarity::calculate(a, b);
            Assert::IsTrue(sim >= 0.0 && sim <= 1.0, L"LongTextDoesNotCrash failed");
        }

        TEST_METHOD(OriginalEmpty)
        {
            Assert::AreEqual(0.0, Similarity::calculate("", "non-empty"), 1e-9, L"OriginalEmpty failed");
        }
    };
}
