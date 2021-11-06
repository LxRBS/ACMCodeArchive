from sys import argv
from os import system, listdir

binary = argv[1]
path = argv[2]

for filepath in listdir(path):
    if filepath.endswith(".in"):
        outfile = filepath.replace(".in", ".ans")
        print("===")
        cmd = "time ./{0} < {1} | tee {2}".format(binary, path+"/"+filepath, path+"/"+outfile)
        print(cmd)
        system(cmd)
