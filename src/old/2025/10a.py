import sys
from aocd import data, submit

sys.setrecursionlimit(1500)


def backtrack(cache, buttons, lights, presses):
    if lights in cache and cache[lights] <= presses:
        return

    cache[lights] = presses

    for button in buttons:
        lights_copy = list(lights)
        for n in button:
            lights_copy[n] = not lights_copy[n]

        backtrack(cache, buttons, tuple(lights_copy), presses + 1)


def get_ans(lines):
    sum = 0

    for i, line in enumerate(lines):
        print(i, len(lines))
        cache = {}

        line = line.split(" ")

        lights = tuple(x == "#" for x in line[0][1:-1])
        buttons = tuple(tuple([int(x) for x in button[1:-1].split(",")]) for button in line[1:-1])

        backtrack(cache, buttons, lights, 0)
        sum += cache[tuple([False] * len(lights))]

    return sum


with open("test_input.txt") as f:
    test_input = [line[:-1] for line in f.readlines()]

test_points = get_ans(test_input)
if test_points != 7:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = get_ans(data.split("\n"))
print(points)
