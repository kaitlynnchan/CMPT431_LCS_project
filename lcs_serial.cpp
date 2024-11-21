#include "core/read_file.h"
#include <vector>
#include <ctime>

using namespace std;

// Returns length of LCS for s1[0..m-1], s2[0..n-1]
int lcs(string &s1, string &s2) {
    int m = s1.size();
    int n = s2.size();

    // Initializing a matrix of size (m+1)*(n+1)
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Building dp[m+1][n+1] in bottom-up fashion
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // dp[m][n] contains length of LCS for s1[0..m-1]
    // and s2[0..n-1]
    return dp[m][n];
}

void lcs_serial(string &s1, string &s2){
    // start timer
    std::clock_t start;
    double duration;
    start = std::clock();
    
    cout << "Calculating... " << endl;
    int lcs_length = lcs(s1, s2);

    // calculate the time taken
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    std::cout << "process, time_taken" << endl;
    std::cout << "0, " << duration << endl;

    std::cout << "Longest Common Subsequence : " << lcs_length << endl;
    std::cout << "Time Taken (in seconds) : " << duration << endl;
}

int main(int argc, char *argv[]) {
    // parse command line arguments
    string inputFile;
    parseInputs(argv[1], &inputFile);
    
    // read strings from inputFile
    string string1, string2;
    readFile(inputFile, string1, string2);
    std::cout << "String 1 : " << string1 << "\n";
    std::cout << "String 2 : " << string2 << "\n";

    lcs_serial(string1, string2);
    return 0; 
}
