import os
import random 
import sys
import string


path = os.getcwd()
input_dir = os.path.join(os.path.dirname(path), "input_files")

if not os.path.exists(input_dir): 
    os.mkdir(input_dir)

possible_sizes = [50, 100, 1000, 5000, 10000, 20000] 
# generates 50 string pairs randomly of a smalller size 
def generate_inputs():
    for size in possible_sizes: 
        filename = "input_size" + str(size) + ".txt" 
        file = os.path.join(input_dir, filename)
        f = open(file, "w")
        
        string1 = ""
        string2 = ""
        for i in range(size): 
            string1 += random.choice(string.ascii_letters)
            string2 += random.choice(string.ascii_letters)

        f.write(string1)
        f.write("\n")
        f.write(string2)

        f.close()


generate_inputs()

