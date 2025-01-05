from aocd import data, submit


def Solve(towels, pattern, curr):
    if pattern == curr:
        return True

    for towel in towels:
        att = curr + towel
        # print(att)

        if pattern.startswith(att) and Solve(towels, pattern, att):
            return True


def GetAns(text: list[str]):
    towels = text[0].replace(" ", "").split(",")
    patterns = text[2:]

    points = 0

    for pattern in patterns:
        if Solve(towels, pattern, ""):
            points += 1
            print(f"{pattern} is valid")
        print(f"{pattern} is NOT valid")

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
if test_points != 6:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"))
print(points)

# submit(points)
