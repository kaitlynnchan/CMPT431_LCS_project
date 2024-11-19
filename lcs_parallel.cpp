#include "core/read_file.h"
#include <iostream>
#include <vector>
using namespace std;

/* ONLY WORKS FOR HEIGHT AND WIDTH THAT ARE THE SAME SIZE */

// Returns length of LCS for s1[0..m-1], s2[0..n-1]
int lcs(string &s1, string &s2) {
    int m = s1.size();
    int n = s2.size();

    // Initializing a matrix of size (m+1)*(n+1)
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    std::vector<int> rowArray;

    int number_of_diagnals = m +n -1;
    for (int d = 1; d <= number_of_diagnals; d++){
        for (int i = 1; i <= m; i++){
            for (int j = 1; j <= n; j++){
                if( j + i == d + 1){
                    rowArray.push_back(i);
                }
            }
        }
        /* Purpose: TEST and PRINT */
        std::cout << "Row entered: ";
        for (int i : rowArray) {
            std::cout << i << " ";
        }
        std::cout << "\n";
        /* Purpose: TEST and PRINT */

        rowArray.clear();

    }

    // /* Purpose: TEST and PRINT */
    //  for (int i = 1; i <= m; i++){
    //         for (int j = 1; j <= n; j++){
    //             std::cout << dp[i][j]<< " ";
    //     }
    //     std::cout << "\n";
    // }
    // /* Purpose: TEST and PRINT */


    // dp[m][n] contains length of LCS for s1[0..m-1]
    // and s2[0..n-1]
    return dp[m][n];
}

int main(int argc, char *argv[]) {

    string string1 = readFile(argv[1]);
    string string2 = readFile(argv[2]);
    std::cout << "String 1 : " << string1 << "\n";
    std::cout << "String 2 : " << string2 << "\n";

    cout << lcs(string1, string2) << endl;
    return 0; 
}
