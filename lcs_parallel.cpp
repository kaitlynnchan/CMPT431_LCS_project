#include "core/read_file.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
#include <barrier>

using namespace std;

void lcs(vector<vector<int>> &dp, string &s1, string &s2, int startx, int endx){
    int j = endx;
    for (int i = startx; i <= endx; i++) {
        if (s1[i - 1] == s2[j - 1])
            dp[i][j] = dp[i - 1][j - 1] + 1;
        else
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << endl;
        j--;
    }
    return NULL;
}

/* ONLY WORKS FOR HEIGHT AND WIDTH THAT ARE THE SAME SIZE */

// Returns length of LCS for s1[0..m-1], s2[0..n-1]
void lcs_parallel(int n_threads, string &s1, string &s2) {
    // start timer
    std::clock_t start;
    double duration;
    start = std::clock();
    
    std::cout << "Calculating... " << endl;

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
        
        std::thread row_threads[n_threads];
        double split = rowArray.size() / n_threads;
        if(split < 1){
            // row_threads[0] = std::thread(lcs, dp, s1, s2, rowArray.front(), rowArray.back());
        } else {
            for(int i = 0; i < n_threads; i++){
                int startx = i * split;
                
                if(i == n_threads - 1){
                    split += rowArray.size() % n_threads;
                }
                int endx = startx + split;
                
                // compute vertex decomposition
                row_threads[i] = std::thread(lcs, dp, s1, s2, rowArray[startx], rowArray[endx]);
            }
        }
        
        // join new page rank threads
        // for(int i = 0; i < n_threads; i++){
        //     row_threads[i].join();
        // }
        // lcs(dp, s1, s2, rowArray.front(), rowArray.back());

        rowArray.clear();

    }
    int lcs_length = dp[m][n];

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

    // calculate the time taken
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    std::cout << "process, time_taken" << endl;
    std::cout << "0, " << duration << endl;

    std::cout << "Longest Common Subsequence : " << lcs_length << endl;
    std::cout << "Time Taken (in seconds) : " << duration << endl;
    // return dp[m][n];
}

int main(int argc, char *argv[]) {

    string string1, string2;
    readFile(argv[1], string1, string2);
    int numThreads = atoi(argv[2]);
    std::cout << "String 1 : " << string1 << "\n";
    std::cout << "String 2 : " << string2 << "\n";
    
    lcs_parallel(numThreads, string1, string2);
    // cout << lcs_parallel(string1, string2) << endl;
    return 0; 
}
