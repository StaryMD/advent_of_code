from aocd import submit
from numpy import roll

with open("data/4.txt") as f:
    lines = f.readlines()

    for i, line in enumerate(lines):
        if line[-1] == "\n":
            lines[i] = line[:-1]


def GetPoints(lines):
    points = 0

    for y in range(1, len(lines) - 1):
        for x in range(1, len(lines[y]) - 1):
            if lines[y][x] == "A":
                lst = [
                    lines[y - 1][x - 1],
                    lines[y - 1][x + 1],
                    lines[y + 1][x + 1],
                    lines[y + 1][x - 1],
                ]
                for i in range(4):
                    if "".join(roll(lst, i + 1)) == "MMSS":
                        points += 1
                        break

    return points


test_lines = [
    ".M.S......",
    "..A..MSMS.",
    ".M.S.MAA..",
    "..A.ASMSM.",
    ".M.S.M....",
    "..........",
    "S.S.S.S.S.",
    ".A.A.A.A..",
    "M.M.M.M.M.",
    "..........",
]

test_points = GetPoints(test_lines)

if test_points != 9:
    print(f"Test failed with points = {test_points}")
    quit()

points = GetPoints(lines)
print(points)
# submit(points)
