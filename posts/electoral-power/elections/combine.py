#!/usr/bin/env python

import sys

def main():

    f = None
    if len(sys.argv) == 1:
        f = sys.stdin
    elif len(sys.argv) == 2:
        f = open(sys.argv[1])
    else:
        raise RuntimeError("Expected zero or one arguments.")

    for l in f.readlines():
        fields = l.split(",")
        c = "D" if int(fields[1]) > int(fields[2]) else "R"
        #sys.stdout.write(",".join([fields[0], c]) + "\n")
        sys.stdout.write(c + "\n")


    sys.stdout.flush()

if __name__ == "__main__":
    main()
 
