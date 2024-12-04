from aocd import data
from math import sqrt, floor, ceil


def GetAns(text):
    # -x^2 + tx - r > 0

    times = [int(x) for x in text[0][9:].split(" ") if x]
    records = [int(x) for x in text[1][9:].split(" ") if x]

    ans = 1

    for t, r in zip(times, records):
        delta = t * t - 4 * r

        x1 = ceil((-t + sqrt(delta)) / -2 + 1e-6)
        x2 = floor((-t - sqrt(delta)) / -2 - 1e-6)

        ans *= x2 - x1 + 1

    return ans


test_input = [
    "Time:      7  15   30",
    "Distance:  9  40  200",
]

test_points = GetAns(test_input)
if test_points != 288:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"))
print(points)
