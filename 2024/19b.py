from aocd import data, submit


points = 0
patt_map = {}


def Solve(towels, pattern):
    global points
    if len(pattern) == 0:
        points += 1
        return

    global patt_map
    if pattern in patt_map:
        points += patt_map[pattern]
        return

    curr_points = points

    for towel in towels:
        if pattern.startswith(towel):
            Solve(towels, pattern[len(towel) :])

    patt_map[pattern] = points - curr_points


def GetAns(text: list[str]):
    towels = text[0].replace(" ", "").split(",")
    patterns = text[2:]

    global points
    global patt_map
    patt_map = {}
    points = 0

    for pattern in patterns:
        curr_points = points

        Solve(towels, pattern)
        print(f"Pattern: {pattern} in {points - curr_points} ways")

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
