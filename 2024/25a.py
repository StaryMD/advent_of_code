from aocd import data, submit
from itertools import product


def chunker(seq, size):
    return (seq[pos : pos + size] for pos in range(0, len(seq), size))


def GetAns(lines):
    lock_length = len(lines) // (lines.count("") + 1)
    lines = list(filter(lambda x: x, lines))

    keys = []
    locks = []

    for chunk in chunker(lines, lock_length):
        counters = [-1] * 5

        for x in range(0, 5):
            for y in range(lock_length):
                if chunk[y][x] == "#":
                    counters[x] += 1
        if chunk[0][0] == ".":
            keys.append(tuple(counters))
        else:
            locks.append(tuple(counters))

    points = 0

    for key, lock in product(keys, locks):
        good = True

        for i in range(5):
            if key[i] + lock[i] > 5:
                good = False

        if good:
            points += 1

    return points


test_input = [
    "#####",
    ".####",
    ".####",
    ".####",
    ".#.#.",
    ".#...",
    ".....",
    "",
    "#####",
    "##.##",
    ".#.##",
    "...##",
    "...#.",
    "...#.",
    ".....",
    "",
    ".....",
    "#....",
    "#....",
    "#...#",
    "#.#.#",
    "#.###",
    "#####",
    "",
    ".....",
    ".....",
    "#.#..",
    "###..",
    "###.#",
    "###.#",
    "#####",
    "",
    ".....",
    ".....",
    ".....",
    "#....",
    "#.#..",
    "#.#.#",
    "#####",
]

test_points = GetAns(test_input)
if test_points != 3:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"))
print(points)

# submit(points)
