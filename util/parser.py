#!/usr/bin/python
"""Parse Sokoban problems into Professor Kask's format"""
import sys
import os

folder_in = sys.argv[1]
folder_out = sys.argv[2]


def parse(filename):
    # Read lines from file
    with open(filename, 'r') as f:
        lines = f.readlines()

    # Storage
    walls = []
    goals = []
    boxes = []
    player = []

    height = 0
    width = 0
    for line in lines[2:]:
        height += 1
        width = max(len(line), width)

        y = height
        for x, char in enumerate(line):
            x += 1
            if char == "#":
                walls += [y, x]
            if char == "@":
                player = [y, x]
            if char == "+":
                player = [y, x]
                goals += [y, x]
            if char == "$":
                boxes += [y, x]
            if char == "*":
                boxes += [y, x]
                goals += [y, x]
            if char == ".":
                goals += [y, x]

    walls = [len(walls)/2] + walls
    boxes = [len(boxes)/2] + boxes
    goals = [len(goals)/2] + goals

    out = "%s %s\n" % (width-1, height-1)
    out += " ".join([str(wall) for wall in walls]) + "\n"
    out += " ".join([str(box) for box in boxes]) + "\n"
    out += " ".join([str(goal) for goal in goals]) + "\n"
    out += " ".join([str(coord) for coord in player])

    return out

if __name__ == '__main__':
    filenames = os.listdir(folder_in)
    for filename in filenames:
        in_path = '%s/%s' % (folder_in, filename)
        out_path = '%s/%s' % (folder_out, filename)
        with open(out_path, 'w') as f:
            f.writelines(parse(in_path))
