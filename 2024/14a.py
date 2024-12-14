from aocd import data, submit
import re
import numpy


def GetAns(text, size, ITS):
    q = [0] * 4
    for line in text:
        match = re.findall("p=([-0-9]+),([-0-9]+)", line)
        px, py = int(match[0][0]), int(match[0][1])
        vx, vy = [int(x) for x in re.findall("v=([-0-9]+),([-0-9]+)", line)[0]]

        px = (px + ITS * vx + ITS * size[1]) % size[1]
        py = (py + ITS * vy + ITS * size[0]) % size[0]

        if px <= (size[1]) // 2 - 1:
            if py <= (size[0]) // 2 - 1:
                q[0] += 1
            elif py > (size[0]) // 2:
                q[1] += 1
        elif px > (size[1]) // 2:
            if py <= (size[0]) // 2 - 1:
                q[2] += 1
            elif py > (size[0]) // 2:
                q[3] += 1
    print(q)

    return numpy.prod(q)


test_input = [
    "p=0,4 v=3,-3",
    "p=6,3 v=-1,-3",
    "p=10,3 v=-1,2",
    "p=2,0 v=2,-1",
    "p=0,0 v=1,3",
    "p=3,0 v=-2,-2",
    "p=7,6 v=-1,-3",
    "p=3,0 v=-1,-2",
    "p=9,3 v=2,3",
    "p=7,3 v=-1,2",
    "p=2,4 v=2,-3",
    "p=9,5 v=-3,-3",
]

test_points = GetAns(test_input, (7, 11), 100)
if test_points != 12:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"), (103, 101), 100)
print(points)

submit(points)
