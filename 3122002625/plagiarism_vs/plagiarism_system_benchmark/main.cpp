#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../Similarity/includes/Similarity.h"

using namespace std;

// 读取文件内容为字符串
string readFile(const string& filePath) {
    ifstream in(filePath);
    if (!in.is_open()) {
        cerr << "Error: Cannot open file " << filePath << endl;
        exit(1);
    }
    stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) {

    string originalPath = "../plagiarism_system/samples/orig.txt";
    string plagiarizedPath = "../plagiarism_system/samples/orig_0.8_dis_15.txt";

    string originalText = readFile(originalPath);
    string plagiarizedText = readFile(plagiarizedPath);

    double similarity = Similarity::calculate(originalText, plagiarizedText, Similarity::LCS_OPTIMIZED_PLUS);

    std::cout << fixed << setprecision(2) << similarity << std::endl;

    return 0;

}
