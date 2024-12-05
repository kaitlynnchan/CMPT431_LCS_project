
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