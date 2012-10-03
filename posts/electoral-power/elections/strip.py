#!/usr/bin/env python

import sys

def main():
    # We expect one argument, which is a file to process.
    # We echo the good data to stdout

    f = None
    if len(sys.argv) == 1:
        f = sys.stdin
    elif len(sys.argv) == 2:
        f = open(sys.argv[1])
    else:
        raise RuntimeError("Expected zero or one arguments.")


    dottedLineCount=0
    for l in f.readlines():
        #l = l.replace("NTH ", "NORTH ")
        #l = l.replace("STH ", "SOUTH ")
        if l.startswith("-"):
            dottedLineCount += 1
        elif dottedLineCount == 2:
            l = l.replace("D OF COLUMBIA", "WASHINGTON DC")
            l = l.replace("DIST OF COLUMBIA", "WASHINGTON DC")
            l = l.replace("Dist of Columbia", "WASHINGTON DC")
            l = l.replace("STH", "SOUTH")
            l = l.replace("NTH", "NORTH")
            l = l.replace("-", "0")
            fields=l.split()
            fields[0] = fields[0].capitalize()
            if fields[1].isalpha():
                if fields[1] != "DC":
                    fields[1]=fields[1].capitalize()
                tmp = [" ".join(fields[0:2])]
                tmp.extend(fields[2:])
                fields=tmp
            l = "\t".join(fields)
            sys.stdout.write(l+"\n")

    sys.stdout.flush()


if __name__ == "__main__":
    main()
