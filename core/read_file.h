#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readFile(string inputFile, string &s1, string &s2){

    // Open the text file named "input.txt"
    ifstream f(inputFile);

    // Check if the file is successfully opened
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return;
    }

    // String variable to store the read data
    string s;

    // Read each line of the file and print it to the
    // standard output stream till the whole file is
  	// completely read
    while(getline(f, s)){
        if (s1.empty()){
            s1 = s;
        } else if (s2.empty()){
            s2 = s;
        }
    }

    // Close the file
    f.close();
}