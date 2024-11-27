#include "core/read_file.h"
#include <iostream>
#include <vector>

using namespace std;

// Returns length of LCS for s1[0..m-1], s2[0..n-1]
int lcs_serial(string &s1, string &s2) 
{
    // m and n represent the lengths of s1 and s2
    int m = s1.size();
    int n = s2.size();

    // Initializing a matrix of size (m+1)*(n+1)
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    int number_of_diagnals = m +n -1;
    for (int d = 1; d <= number_of_diagnals; d++)
    {
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                // Ensure we are only processing elements along the diagonal
                if( j + i == d + 1)
                {
                    // Update the dp table based on character comparison
                    if (s1[i - 1] == s2[j - 1]) {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    } 
                    else {
                        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    }
                }
            }
        }
    }

    // dp[m][n] contains length of LCS for s1[0..m-1]
    // and s2[0..n-1]
    return dp[m][n];
}

int main(int argc, char *argv[]) 
{
    string string1, string2;
    readFile(argv[1], string1, string2);
    std::cout << "String 1 : " << string1 << "\n";
    std::cout << "String 2 : " << string2 << "\n";

    int length = lcs_serial(string1, string2);

    cout << "The Length of the Longest Common Subsequence is: " << length << endl;

    return 0; 
}
