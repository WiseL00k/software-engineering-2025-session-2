#include <iostream>
#include "Similarity.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] 
             << " <original_file> <plagiarized_file> <output_file>" << endl;
        return 1;
    }

    string originalPath = argv[1];
    string plagiarizedPath = argv[2];
    string outputPath = argv[3];


    return 0;
}
