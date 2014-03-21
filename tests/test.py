#! /usr/bin/python2.7

import sys, subprocess
import json

def main():
    argv = sys.argv
    argc = len(argv)
    treat("tests.txt")

def parse_file(f):
    content = ""
    with open(f) as f:
        for line in f:
            content += line
    return json.loads(content)

def treat(f):
    nbtests = 0
    nbsucc = 0
    for item in parse_file(f):
        nbtests += 1
        sub = subprocess.Popen(["sh", "-c", "../BPMDetector --display " + item[0]],
                               bufsize = 0, stdout = subprocess.PIPE, stdin = subprocess.PIPE)
        out, err = sub.communicate()
        i = 0
        while out[i] != '.':
            i+=1
        val = int(out[:i])
        success = False
        if (val > item[1] - 5 and val < item[1] + 5):
            success = True
        print("Song : " + item[0])
        print("Expected BPM : " + str(item[1]))
        if (success):
            nbsucc += 1
            print("\033[32m\033[1m[SUCCESS]\033[0m\033[0m\n")
        else:
            print("\033[31m\033[1m[FAILURE]\033[0m\033[0m\n")
    print("\033[33m\033[1mSuccess : " + str(nbsucc) + "/" + str(nbtests) + "\033[0m\033[0m")

main()
