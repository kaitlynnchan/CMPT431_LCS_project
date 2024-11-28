#include "core/read_file.h"

int main(int argc, char *argv[]) {
    // parse command line arguments
    string inputFile;
    int numThreads;
    parseInputs(argv[1], &numThreads);
    parseInputs(argv[2], &inputFile);

    // read strings from inputFile
    string string1, string2;
    readFile(inputFile, string1, string2);

    // print arguments
    std::cout << "Number of Threads : " << numThreads << "\n";
    std::cout << "String 1 : " << string1 << "\n";
    std::cout << "String 2 : " << string2 << "\n";

    return 0; 
}
