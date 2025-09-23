#include "pch.h" // 预编译头 (VS 自动生成)
#include "CppUnitTest.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <windows.h> // GetModuleFileNameA
#include "../Similarity/includes/Similarity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSimilarity
{
    static std::string wstr_to_string(const std::wstring& ws) {
        return std::string(ws.begin(), ws.end());
    }

    static void logMsg(const std::string& s) {
        // Logger expects wide string
        std::wstring ws(s.begin(), s.end());
        Logger::WriteMessage(ws.c_str());
    }

    std::string readFile(const std::string& path) {
        namespace fs = std::filesystem;
        // Print current working directory for debug
        try {
            auto cwd = fs::current_path().wstring();
            logMsg("Current working dir: " + wstr_to_string(cwd));
        }
        catch (...) {
            logMsg("Unable to get current path");
        }
        std::ifstream fin(path);
        std::ostringstream ss;
        ss << fin.rdbuf();
        return ss.str();
    }


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

        TEST_METHOD(Sample_Orig_Add)
        {
            std::string orig = readFile("../../../plagiarism_system_test/samples/orig.txt");
            std::string plag = readFile("../../../plagiarism_system_test/samples/orig_0.8_add.txt");

            Assert::IsTrue(!orig.empty(), L"orig.txt not found or empty");
            Assert::IsTrue(!plag.empty(), L"orig_add.txt not found or empty");

            double sim = Similarity::calculate(orig, plag);

            std::wstring msg = L"Orig vs Orig_Add similarity = " + std::to_wstring(sim);
            Logger::WriteMessage(msg.c_str());

            // 这里只要断言相似度合理（0 ~ 1），可根据实际情况加范围
            Assert::IsTrue(sim > 0.0 && sim <= 1.0, L"Sample_Orig_Add failed");
        }

        TEST_METHOD(Sample_Orig_Del)
        {
            std::string orig = readFile("../../../plagiarism_system_test/samples/orig.txt");
            std::string plag = readFile("../../../plagiarism_system_test/samples/orig_0.8_del.txt");

            Assert::IsTrue(!orig.empty(), L"orig.txt not found or empty");
            Assert::IsTrue(!plag.empty(), L"orig_del.txt not found or empty");

            double sim = Similarity::calculate(orig, plag);

            std::wstring msg = L"Orig vs Orig_Del similarity = " + std::to_wstring(sim);
            Logger::WriteMessage(msg.c_str());

            Assert::IsTrue(sim > 0.0 && sim <= 1.0, L"Sample_Orig_Del failed");
        }

        TEST_METHOD(Sample_Orig_Rep)
        {
            std::string orig = readFile("../../../plagiarism_system_test/samples/orig.txt");
            std::string plag = readFile("../../../plagiarism_system_test/samples/orig_0.8_dis_15.txt");

            Assert::IsTrue(!orig.empty(), L"orig.txt not found or empty");
            Assert::IsTrue(!plag.empty(), L"orig_dis.txt not found or empty");

            double sim = Similarity::calculate(orig, plag);

            std::wstring msg = L"Orig vs Orig_Rep similarity = " + std::to_wstring(sim);
            Logger::WriteMessage(msg.c_str());

            Assert::IsTrue(sim > 0.0 && sim <= 1.0, L"Sample_Orig_dis failed");
        }
    };
}
