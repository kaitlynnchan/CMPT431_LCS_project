#include "core/read_file.h"
#include <vector>
#include <tuple>
#include <ctime>


// Get the dynamic programming table for the strings to find the length 
void longestCommonSubsequence(string &s1, string &s2, vector<tuple<int, int>> &diagonalIndices, int startIndex, int endIndex, vector<vector<int>> &dp) 
{
    for (int x = startIndex; x < endIndex; x++)
    {
        // Unpack the tuple containing (i, j) indices
        int i = get<0>(diagonalIndices[x]);
        int j = get<1>(diagonalIndices[x]);

        // Update the dp table based on character comparison
        if (s1[i - 1] == s2[j - 1]) {
            dp[i][j] = dp[i - 1][j - 1] + 1;
        } 
        else {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
}

// Find the longest common sequence by backtracking in the dp table 
string lcs_sequence(int length, string &s1, string &s2, vector<vector<int>> &dp) {
    // initialize sequence of given length
    char sequence[length+1];
    sequence[length] = '\0';

    int i = s1.size(); 
    int j = s2.size(); 
    int index = length -1; 

    // backtrack through the dp table, and update 
    // sequence when the characters in the string match
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            sequence[index] = s1[i-1];
            i-=1; 
            j-=1;
            index-=1;
        }
        // Move up or left depending on the values in dp table 
        else if (dp[i-1][j] > dp[i][j-1])
            i--; 
        else 
            j--; 
    }
    return sequence;
}

// Returns length of LCS for s1[0..m-1], s2[0..n-1]
tuple<string, int> lcs_serial(string &s1, string &s2) 
{
    
    // m and n represent the lengths of s1 and s2
    int m = s1.size();
    int n = s2.size();

    // Initializing a matrix of size (m+1)*(n+1)
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Declare a list to hold pairs (i, j)
    vector<tuple<int, int>> diagonalIndices;

    int number_of_diagnals = m +n -1;
    for (int d = 1; d <= number_of_diagnals; d++)
    {
        // get start and end row for diagonals
        int start_row = std::max(1, d-n+1);
        int end_row = std::min(m,d); 
        for (int i = start_row; i <= end_row; i++)
        {
            //get column indices
            int j = d + 1 - i;
            // Ensure we are only processing elements along the diagonal
            if(j>=1 && j <= n){ 
                diagonalIndices.push_back(make_tuple(i, j));
            }
        }
    }

    // Define start and end positions for processing
    int startx = 0;
    int endx = diagonalIndices.size();

    longestCommonSubsequence(s1, s2, diagonalIndices, startx, endx, dp);
    
    // dp[m][n] contains length of LCS for s1[0..m-1]
    // and s2[0..n-1]
    string seq = lcs_sequence(dp[m][n], s1, s2, dp);
    return make_tuple(seq, dp[m][n]);
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
    // start timer
    std::clock_t start_timer;
    double duration;
    start_timer = std::clock();
    cout << "Calculating... " << endl;

    tuple<string, int> output = lcs_serial(string1, string2);

     // calculate the time taken
    duration = (std::clock() - start_timer) / (double) CLOCKS_PER_SEC;

    std::cout << "process, time_taken" << endl;
    std::cout << "0, " << duration << endl;
    std:: cout << "The Longest Common Subsequence is: " << std::get<0>(output) << endl;
    std:: cout << "The Length of the Longest Common Subsequence is: " << std::get<1>(output) << endl;

    std::cout << "Time Taken (in seconds) : " << duration << endl;

    return 0; 
}
