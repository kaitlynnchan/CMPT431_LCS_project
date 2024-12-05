# Longest Common Subsequence
The Longest Common Subsequence (LCS) problem attempts to find the longest sequence that can be derived as a subsequence from two given sequences. A subsequence is defined as a sequence that maintains the order of characters from the original but may exclude some characters. The goal of solving the LCS problem is to determine the maximum length of such a sequence common to both inputs.

This project contains serial, parallel, and distributed solutions to the LCS problem.

## Usage

Instructions for running the project. The serial and parallel versions should be run on a CSIL machine. The distributed version should be run using Slurm in the cs-cloud server.

Below includes example commands to run the versions individually:

```bash
# create the executable files
$ make

# run the serial version
$ ./lcs_serial --inputFile=input_files/text.txt

# run the parallel version
$ ./lcs_parallel --numThreads=2 --inputFile=input_files/text.txt

# run the distributed version in cs-cloud
$ scp -P 24 -r <path> <username>@cs-cloud.cs.surrey.sfu.ca:<path> # copy the entire proj to cs-cloud
$ sbatch scripts/lcs_job_1.sh # run the job located in the scripts folder 
```

We have also created scripts to generate inputs and run all implementations, exporting the outputs to the output files for easier readability. These commands should be run in cs-cloud. To generate the inputs and run the scripts:

```bash
# create the executable files
$ make

# navigate to the scripts directory
$ cd scripts

# generate inputs (sample inputs are given)
# input files located in /input_files
$ python3 generate_inputs.py #generates inputs of sizes 50, 100, 1000, 5000, and 10000 

# runs the serial and parallel version for all inputs 
# writes output to /output_files 
# only runs distributed with 1 process
$ python3 run.py #takes a little bit of time

# runs the distributed version for various processes
# the slurm job should be run from the home directory for this project
$ cd ../
$ sbatch scripts/lcs_distributed.sh #saves output to slurm_output_distributed.txt in output_files 
```

## Citations
Some portions of our code were developed with assistance from the following website:
https://www.geeksforgeeks.org/printing-longest-common-subsequence/