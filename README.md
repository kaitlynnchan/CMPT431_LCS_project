
## Usage

Instructions for running the project. The serial and parallel versions should be run on a CSIL machine. The distributed version should be run using Slurm.

```bash
# Example command to run the project

# create the executable files
$ make

# run the serial version
$ ./lcs_serial --inputFile=input_files/text.txt

# run the parallel version
$ ./lcs_parallel --numThreads=2 --inputFile=input_files/text.txt

# run the distributed version
$ scp -P 24 -r <path> <username>@cs-cloud.cs.surrey.sfu.ca:<path> # copy the entire directory to slurm
$ sbatch scripts/lcs_job_1.sh # run the jobs located in the scripts folder
```

To generate the inputs and run the scripts

```bash
# create the executable files
$ make

# need to be in the scripts directory to run
$ cd scripts

# generate inputs (sample inputs are given)
$ python3 generate_inputs.py #generates inputs of sizes 50, 100, 1000, 5000, and 10000 

# to run the serial and parallel version for all inputs 
# writes output to output_files 
# only runs distributed with 1 process
$ python3 run.py #takes a little bit of time

# to run the distributed version for various processes
$ sbatch lcs_distributed.sh #saves output to slurm_output.txt in output_files 
```
