import os 
import subprocess 

path = os.getcwd()
directory = os.path.dirname(path)
output_dir = os.path.join(directory, "output_files")

if not os.path.exists(output_dir):
    os.mkdir(output_dir)

def run_executable(executable, args, filename):
    result = subprocess.run([os.path.dirname(path) + '/' + executable] + args, capture_output=True, text=True)
    file = os.path.join(output_dir, filename)
    f = open(file, "a")
    f.write(result.stdout)
    f.write("\n")
    f.close()

small_inputs = os.path.join(os.path.dirname(path), "input_files", "small_inputs")
medium_inputs = os.path.join(os.path.dirname(path), "input_files", "medium_inputs")
large_inputs = os.path.join(os.path.dirname(path), "input_files", "large_inputs")

nthreads = 4

if os.path.exists(small_inputs): 
    f = open(os.path.join(output_dir, "small_output_serial"), "w")
    f = open(os.path.join(output_dir, "small_output_parallel"), "w")
    for file in os.listdir(small_inputs): 
        run_executable('./lcs_serial', [os.path.join(small_inputs, file)], "small_output_serial")
        run_executable('./lcs_parallel', [str(nthreads), os.path.join(small_inputs, file)], "small_output_parallel")

if os.path.exists(medium_inputs): 
    f = open(os.path.join(output_dir, "medium_output_serial"), "w")
    f = open(os.path.join(output_dir, "medium_output_parallel"), "w")
    for file in os.listdir(medium_inputs): 
        run_executable('./lcs_serial', [os.path.join(medium_inputs, file)], "medium_output_serial")
        run_executable('./lcs_parallel', [str(nthreads), os.path.join(small_inputs, file)], "medium_output_parallel")


if os.path.exists(large_inputs): 
    f = open(os.path.join(output_dir, "large_output_serial"), "w")
    f = open(os.path.join(output_dir, "large_output_parallel"), "w")
    for file in os.listdir(large_inputs): 
        run_executable('./lcs_serial', [os.path.join(large_inputs, file)], "large_output_serial")
        run_executable('./lcs_parallel', [str(nthreads), os.path.join(small_inputs, file)], "large_output_parallel")
