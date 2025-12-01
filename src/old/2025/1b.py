from aocd import data, submit


def GetAns(lines):
    points = 0
    dial = 50

    for line in lines:
        left = line[0] == "L"
        num = int(line[1:])

        if left:
            for i in range(num):
                dial -= 1

                dial %= 100
                if dial == 0:
                    points += 1

        else:
            for i in range(num):
                dial += 1

                dial %= 100
                if dial == 0:
                    points += 1

    return points


test_input = [
    "L68",
    "L30",
    "R48",
    "L5",
    "R60",
    "L55",
    "L1",
    "L99",
    "R14",
    "L82",
]

test_points = GetAns(test_input)
if test_points != 6:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"))
print(points)

# submit(points)
