#include "core/read_file.h"
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>
#include <tuple>

using namespace std;

class ThreadInfo{
public:
    int n_elements;
    double time_taken;

    ThreadInfo()
        : n_elements(0), time_taken(0.0) {}
};

void lcs(vector<vector<int>> &dp, string &s1, string &s2, int startx, int endx, vector<tuple<int, int>> &diagonalIndices, double *time_taken){
    // start timer
    std::clock_t start;
    double duration;
    start = std::clock();

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
    
    // calculate the time taken
    *time_taken += (std::clock() - start) / (double) CLOCKS_PER_SEC;
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
    
    // Initialize array of thread info
    ThreadInfo *thread_info = new ThreadInfo[n_threads];

    // Declare a list to hold pairs (i, j)
    vector<tuple<int, int>> diagonalIndices;

    int number_of_diagnals = m + n - 1;
    for (int d = 1; d <= number_of_diagnals; d++){
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

        double split = diagonalIndices.size() / n_threads;
        if(split < 1){
            // there are less values to calculate than threads, run lcs without threads
            thread_info[0].n_elements += diagonalIndices.size();
            lcs(dp, s1, s2, 0, diagonalIndices.size(), diagonalIndices, &thread_info[0].time_taken);
        } else {
            std::thread row_threads[n_threads];
            for(int i = 0; i < n_threads; i++){
                int startx = i * split;
                
                if(i == n_threads - 1){
                    split += diagonalIndices.size() % n_threads;
                }
                int endx = startx + split;
                thread_info[i].n_elements += endx - startx;
                
                // compute vertex decomposition
                row_threads[i] = std::thread(lcs, ref(dp), ref(s1), ref(s2), startx, endx, ref(diagonalIndices), &thread_info[i].time_taken);
            }

            // join new page rank threads
            for(int i = 0; i < n_threads; i++){
                row_threads[i].join();
            }
        }
        
        diagonalIndices.clear();
    }

    int lcs_length = dp[m][n];

    // calculate the time taken
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    std::cout << "thread_id, num_elements_processed, time_taken" << endl;
    for(int i = 0; i < n_threads; i++){
        std::cout << i << ", " << thread_info[i].n_elements << ", " << thread_info[i].time_taken << std::endl;
    }

    std::cout << "Longest Common Subsequence : " << lcs_length << endl;
    std::cout << "Time Taken (in seconds) : " << duration << endl;

    delete[] thread_info;
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
