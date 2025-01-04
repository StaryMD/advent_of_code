from aocd import data, submit
from math import sqrt, floor, ceil


def GetAns(text):
    # -x^2 + tx - r > 0

    t = int("".join([x for x in text[0][9:].split(" ") if x]))
    r = int("".join([x for x in text[1][9:].split(" ") if x]))

    delta = t * t - 4 * r

    x1 = ceil((-t + sqrt(delta)) / -2 + 1e-6)
    x2 = floor((-t - sqrt(delta)) / -2 - 1e-6)

    return x2 - x1 + 1


test_input = [
    "Time:      7  15   30",
    "Distance:  9  40  200",
]

test_points = GetAns(test_input)
if test_points != 71503:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"))
print(points)
# submit(points)
