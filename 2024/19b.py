from aocd import data, submit
from functools import cache


def GetAns(text: list[str]):
    towels = text[0].replace(" ", "").split(",")
    patterns = text[2:]

    points = 0

    @cache
    def Solve(pattern):
        if not pattern:
            return 1

        curr_points = 0

        for towel in towels:
            if pattern.startswith(towel):
                curr_points += Solve(pattern[len(towel) :])

        return curr_points

    for pattern in patterns:
        points += Solve(pattern)

    return points


test_input = [
    "r, wr, b, g, bwu, rb, gb, br",
    "",
    "brwrr",
    "bggr",
    "gbbr",
    "rrbgbr",
    "ubwu",
    "bwurrg",
    "brgr",
    "bbrgwb",
]

test_points = GetAns(test_input)
if test_points != 16:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")
print("Test passed!")

points = GetAns(data.split("\n"))
print(points)

# submit(points)
