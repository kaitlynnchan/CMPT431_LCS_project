#include "core/read_file.h"

int main(int argc, char *argv[]) {
    
    string string1 = readFile(argv[1]);
    string string2 = readFile(argv[2]);
    std::cout << "String 1 : " << string1 << "\n";
    std::cout << "String 2 : " << string2 << "\n";

    return 0; 
}
