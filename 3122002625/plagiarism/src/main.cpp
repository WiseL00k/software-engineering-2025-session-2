#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Similarity.h"

using namespace std;

// 读取文件内容为字符串
string readFile(const string &filePath) {
    ifstream in(filePath);
    if (!in.is_open()) {
        cerr << "Error: Cannot open file " << filePath << endl;
        exit(1);
    }
    stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] 
             << " <original_file> <plagiarized_file> <output_file>" << endl;
        return 1;
    }

    string originalPath = argv[1];
    string plagiarizedPath = argv[2];
    string outputPath = argv[3];

    string originalText = readFile(originalPath);
    string plagiarizedText = readFile(plagiarizedPath);

    double similarity = Similarity::calculate(originalText, plagiarizedText);

    ofstream out(outputPath);
    if (!out.is_open()) {
        cerr << "Error: Cannot open output file " << outputPath << endl;
        return 1;
    }
    out << fixed << setprecision(2) << similarity << endl;
    return 0;

    return 0;
}
