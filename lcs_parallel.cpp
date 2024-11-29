#include "core/read_file.h"
#include <barrier>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>
#include <tuple>

using namespace std;

void lcs(std::barrier<> &b, vector<vector<int>> &dp, string &s1, string &s2, int startx, int endx, vector<tuple<int, int>> &diagonalIndices){
    
    for (int x = startx; x < endx; x++) {
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

    b.arrive_and_wait();
}

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

    // Declare a list to hold pairs (i, j)
    vector<tuple<int, int>> diagonalIndices;

    int number_of_diagnals = m + n - 1;
    for (int d = 1; d <= number_of_diagnals; d++){
        for (int i = 1; i <= m; i++){
            for (int j = 1; j <= n; j++){
                if( j + i == d + 1){
                    diagonalIndices.push_back(make_tuple(i, j));
                }
            }
        }

        /* Purpose: TEST and PRINT */
        // std::cout << "Row and column entered: ";
        // for (const auto& tup : diagonalIndices) {
        //     // Access the elements of the tuple
        //     int i = std::get<0>(tup);
        //     int j = std::get<1>(tup);
        //     std::cout << "(" << i << ", " << j << ") ";
        // }
        // std::cout << "\n";
        /* Purpose: TEST and PRINT */

        double split = diagonalIndices.size() / n_threads;
        if(split < 1){
            // there are less values to calculate than threads, run lcs without threads
            std::barrier b(1);
            lcs(b, dp, s1, s2, 0, diagonalIndices.size(), diagonalIndices);
            
            /* Purpose: TEST and PRINT */
            // std::cout << "Thread " << 0 
            // << " - startx: " << 0 
            // << ", endx: " << diagonalIndices.size()
            // << "\n";
             /* Purpose: TEST and PRINT */
                
        } else {
            std::barrier b(n_threads);
            std::thread row_threads[n_threads];
            for(int i = 0; i < n_threads; i++){
                int startx = i * split;
                
                if(i == n_threads - 1){
                    split += diagonalIndices.size() % n_threads;
                }
                int endx = startx + split;

                /* Purpose: TEST and PRINT */
                // std::cout << "Thread " << i 
                // << " - startx: " << startx 
                // << ", endx: " << endx 
                // << ", split: " << split 
                // << ", diagonalIndices size: " << diagonalIndices.size() 
                // << "\n";
                /* Purpose: TEST and PRINT */
                
                // compute vertex decomposition
                row_threads[i] = std::thread(lcs, std::ref(b), std::ref(dp), std::ref(s1), std::ref(s2), startx, endx, std::ref(diagonalIndices));
            }

            // join new page rank threads
            for(int i = 0; i < n_threads; i++){
                row_threads[i].join();
            }
        }
        
        diagonalIndices.clear();
    }

    int lcs_length = dp[m][n];

    /* Purpose: TEST and PRINT */
    // std::cout << "Diagonal Matrix Results:\n";
    // for (int i = 1; i <= m; i++){
    //     for (int j = 1; j <= n; j++){
    //         std::cout << dp[i][j]<< " ";
    //     }
    //     std::cout << "\n";
    // }
    /* Purpose: TEST and PRINT */

    // calculate the time taken
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    std::cout << "Longest Common Subsequence : " << lcs_length << endl;
    std::cout << "Time Taken (in seconds) : " << duration << endl;
}

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
    
    lcs_parallel(numThreads, string1, string2);
    return 0; 
}
