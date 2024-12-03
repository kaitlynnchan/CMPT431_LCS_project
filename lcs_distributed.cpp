#include "core/read_file.h"
#include <ctime>
#include <iostream>
#include <vector>
#include <tuple>
#include <mpi.h>

void longestCommonSubsequence(string &s1, string &s2, 
                              vector<tuple<int, int>> &diagonalIndices, 
                              int startIndex, int endIndex, 
                              vector<vector<int>> &dp, 
                              vector<int> &send_items) 
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

        // Store the computed dp value for sending
        send_items.push_back(dp[i][j]);
    }
}

// Returns length of LCS for s1[0..m-1], s2[0..n-1]
int lcs_distributed(string &s1, string &s2, int world_size, int world_rank) 
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
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                // Ensure we are only processing elements along the diagonal
                if( j + i == d + 1){ 
                    diagonalIndices.push_back(make_tuple(i, j));
                }
            }
        }

        int num_elements = diagonalIndices.size();
        int elements_per_process = num_elements / world_size;
        int start, end;

        if (num_elements <= world_size) {
            // Each rank processes at most one element
            start = world_rank;
            end = (world_rank < num_elements) ? world_rank + 1 : world_rank;
        } 
        else {
            // Regular division of work
            start = elements_per_process * world_rank;
            end = (world_rank == world_size - 1) ? num_elements : elements_per_process * (world_rank + 1);
        }

        // Vector to store the local results of each process
        vector<int> send_items;

        // calculate the dignal d elements
        longestCommonSubsequence(s1, s2, diagonalIndices, start, end, dp, send_items);


        /*** Gather the diagonal results from each process ***/
        vector<int> send_counts(world_size, 0);
        int local_send_size = send_items.size();

        MPI_Allgather(
            /* send_data          = */ &local_send_size,
            /* send_count         = */ 1,
            /* send_datatype      = */ MPI_INT,
            /* recv_data          = */ send_counts.data(),
            /* recv_count         = */ 1,
            /* recv_datatype      = */ MPI_INT,
            /* status             = */ MPI_COMM_WORLD
        ); 

        vector<int> displacements(world_size, 0);
        
        // Compute displacements based on _counts
        for (int i = 1; i < world_size; i++) {
            displacements[i] = displacements[i - 1] + send_counts[i - 1];
        }

        // Allocate space to gather all the computed values
        vector<int> all_recv_items(diagonalIndices.size(),0);

        MPI_Allgatherv(
            /* send_data          = */ send_items.data(),
            /* send_count         = */ local_send_size,
            /* send_datatype      = */ MPI_INT,
            /* recv_data          = */ all_recv_items.data(),
            /* recv_count         = */ send_counts.data(),
            /* displacements      = */ displacements.data(),
            /* recv_datatype      = */ MPI_INT,
            /* status             = */ MPI_COMM_WORLD
        );

        for (int x = 0; x < diagonalIndices.size(); x++) 
        {
            // Unpack the tuple containing (i, j) indices
            int i = get<0>(diagonalIndices[x]);
            int j = get<1>(diagonalIndices[x]);

            dp[i][j] = all_recv_items[x];
        }

        // Remove all the elements after processing the current diagonal
        diagonalIndices.clear();
    }

    // dp[m][n] contains length of LCS for s1[0..m-1]
    // and s2[0..n-1]
    return dp[m][n];
}

int main(int argc, char *argv[]) 
{
    // must be without snull parameter
    // to process command-line arguments
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    string string1, string2; 
    int string1_size = 0;
    int string2_size = 0;

    // Rank 0 reads the text file and broadcasts the strings to all ranks
    if (world_rank == 0) 
    {
        // parse command line arguments
        string inputFile;
        parseInputs(argv[1], &inputFile);
    
        // read strings from inputFile
        readFile(inputFile, string1, string2);
        
        string1_size = string1.size();
        string2_size = string2.size();
        std::cout << "Number of Processes : " << world_size << "\n";
        std::cout << "String 1 : " << string1 << "\n";
        std::cout << "String 2 : " << string2 << "\n";
    }

    // start timer
    std::clock_t start;
    double duration;
    start = std::clock();
    
    // Broadcast the sizes of the strings to all processes
    MPI_Bcast(&string1_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&string2_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Resize strings based on the received sizes
    string1.resize(string1_size);
    string2.resize(string2_size);

    // Broadcast the actual strings to all processes
    MPI_Bcast(&string1[0], string1_size, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(&string2[0], string2_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    int length = lcs_distributed(string1, string2, world_size, world_rank);

    // calculate the time taken
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    if (world_rank == 0) {
        std::cout << "The Length of the Longest Common Subsequence is: " << length << "\n";
        std::cout << "Time Taken (in seconds) : " << duration << endl;
    }

    // Finalize the MPI environment.
    MPI_Finalize();

    return 0; 
}
