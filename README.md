
## Usage

Instructions for running the project. The project should be run on a CSIL machine.

```bash
# Example command to run the project
$ make

$ ./lcs_serial --inputFile=input_files/text.txt

$ ./lcs_parallel --numThreads=2 --inputFile=input_files/text.txt

$ ./lcs_distributed --inputFile=input_files/text.txt
```

# To generate inputs of various sizes
python3 scripts/generate_inputs.py (S, M or L)

# To run generated inputs
python3 scripts/run.py executable
