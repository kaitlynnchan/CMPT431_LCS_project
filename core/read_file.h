#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string readFile(string inputFile){

    // Open the text file named "input.txt"
    ifstream f(inputFile);

    // Check if the file is successfully opened
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return NULL;
    }

    // String variable to store the read data
    string s;

    // Read each line of the file and print it to the
    // standard output stream till the whole file is
  	// completely read
    if(getline(f, s)){
        f.close();
        return s;
    }

    // Close the file
    f.close();
    return NULL;
}