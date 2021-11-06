from sys import argv
from os import system, listdir

path = argv[1]

for filepath in listdir(path):
    if filepath.endswith(".in"):
        outfile = filepath.replace(".in", ".ans")
        with open(path+"/"+filepath, "a+") as f:
            lines = f.readlines()
            if lines == []:
                f.write("\n")
            else:
                for i in range(len(lines)):
                    if i == len(lines) - 1 and lines[i] != ['\n']:
                        print(filepath)
                        f.write("\n")
                        break
        with open(path+"/"+outfile, "a+") as f:
            lines = f.readlines()
            if lines == []:
                f.write("\n")
            else:
                for i in range(len(lines)):
                    if i == len(lines) - 1 and lines[i] != ['\n']:
                        print(filepath)
                        f.write("\n")
                        break
