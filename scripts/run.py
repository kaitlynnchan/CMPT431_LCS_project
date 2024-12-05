import os 
from subprocess import PIPE, run

path = os.getcwd()
directory = os.path.dirname(path)
output_dir = os.path.join(directory, "output_files")
input_dir = os.path.join(directory, "input_files")

if not os.path.exists(output_dir):
    os.mkdir(output_dir)

possible_threads = [2, 4, 8]

def run_serial():
    serial_dir = os.path.join(output_dir, "serial")
    if not os.path.exists(serial_dir):
        os.mkdir(serial_dir)

    for file in os.listdir(input_dir): 
        result =run([os.path.dirname(path) + '/' + "./lcs_serial"] + 
                                ["--inputFile=" + os.path.join(input_dir, file)], stdout=PIPE)
        f = open(os.path.join(serial_dir, "output_" + file[6:]) , "w")
        f.write(result.stdout.decode('utf-8')) 
        f.close()

run_serial()

def run_parallel():
    parallel_dir = os.path.join(output_dir, "parallel")
    if not os.path.exists(parallel_dir):
        os.mkdir(parallel_dir)
    for file in os.listdir(input_dir): 
        f = open(os.path.join(parallel_dir, "output_" + file[6:]) , "w")
        for threads in possible_threads: 
            result = run([os.path.dirname(path) + '/' + "./lcs_parallel"] + 
                                ["--numThreads=" + str(threads), "--inputFile=" + os.path.join(input_dir, file)], stdout=PIPE)
            f = open(os.path.join(parallel_dir, "output_" + file[6:]) , "a")
            f.write(result.stdout.decode('utf-8'))
            f.write("\n")
            f.close()

run_parallel()

def run_distributed():
    distributed_dir = os.path.join(output_dir, "distributed")
    if not os.path.exists(distributed_dir):
        os.mkdir(distributed_dir)
    for file in os.listdir(input_dir): 
        result = run([os.path.dirname(path) + '/' + "./lcs_distributed"] + 
                                ["--inputFile=" + os.path.join(input_dir, file)], stdout=PIPE) 
        f = open(os.path.join(distributed_dir, "output_" + file[6:]) , "w")
        f.write(result.stdout.decode('utf-8'))
        f.write("\n")
        f.close()

##run_distributed()
