import os
import random 
import sys
import string


path = os.getcwd()
input_dir = os.path.dirname(path) + "/input_files"

if not os.path.exists(input_dir): 
    os.mkdir(input_dir)

# generates 50 string pairs randomly of a smalller size 
def generate_small_inputs(): 
    directory = os.path.join(input_dir, "small_inputs")
    for i in range(25): 
        filename = "input" + str(i) + ".txt" 
        file = os.path.join(directory, filename)
        f = open(file, "w")

        size1 = random.randint(3, 50)
        size2 = random.randint(3, 30)

        string1 = "".join(random.choices(string.ascii_letters, k=size1))
        string2 = "".join(random.choices(string.ascii_letters, k=size2))

        f.write(string1)
        f.write("\n")
        f.write(string2)

        f.close()


def generate_medium_inputs(): 
    directory = os.path.join(input_dir, "medium_inputs")
    for i in range(25): 
        filename = "input" + str(i) + ".txt" 
        file = os.path.join(directory, filename)
        f = open(file, "w")

        size1 = random.randint(100, 1000)
        size2 = random.randint(100, 1000)

        string1 = "".join(random.choices(string.ascii_letters, k=size1))
        string2 = "".join(random.choices(string.ascii_letters, k=size2))

        f.write(string1)
        f.write("\n")
        f.write(string2)

        f.close()


def generate_large_inputs(): 
    directory = os.path.join(input_dir, "large_inputs")
    for i in range(25): 
        filename = "input" + str(i) + ".txt" 
        file = os.path.join(directory, filename)
        f = open(file, "w")

        size1 = random.randint(5000, 10000)
        size2 = random.randint(5000, 10000)

        string1 = "".join(random.choices(string.ascii_letters, k=size1))
        string2 = "".join(random.choices(string.ascii_letters, k=size2))

        f.write(string1)
        f.write("\n")
        f.write(string2)

        f.close()


inputType = 0
if len(sys.argv) > 1:
    # generates inputs where strings are of sizes between 3 to 30
    if sys.argv[1] == "S": 
        if not os.path.exists(input_dir + "/small_inputs"): 
            os.mkdir(input_dir + "/small_inputs")
        generate_small_inputs()
        print("generate small size inputs")
    # generates inputs where strings are of sizes between 100 to 1000 
    elif sys.argv[1] == "M": 
        if not os.path.exists(input_dir + "/medium_inputs"): 
            os.mkdir(input_dir + "/medium_inputs")
        generate_medium_inputs()
        print("generate medium inputs")
    # generates inputs where strings are of sizes between 5000 to 10000 
    elif sys.argv[1] == "L": 
        if not os.path.exists(input_dir + "/large_inputs"): 
            os.mkdir(input_dir + "/large_inputs")
        generate_large_inputs()
        print("generate large inputs")
else:
    if not os.path.exists(input_dir + "/small_inputs"):
        os.mkdir(input_dir + "/small_inputs")
    if not os.path.exists(input_dir + "/medium_inputs"): 
        os.mkdir(input_dir + "/medium_inputs")
    if not os.path.exists(input_dir + "/large_inputs"): 
        os.mkdir(input_dir + "/large_inputs")
    generate_small_inputs()
    generate_medium_inputs()
    generate_large_inputs()
    ## generates all 3 inputs 
    print("generate all inputs")
