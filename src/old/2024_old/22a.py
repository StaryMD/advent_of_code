from aocd import data, submit


def Next(n):
    m = 16777216

    n ^= n * 64
    n %= m

    n ^= n // 32
    n %= m

    n ^= n * 2048
    n %= m

    return n


def GetAns(text):
    points = 0

    for line in text:
        n = int(line)

        for i in range(2000):
            n = Next(n)

        points += n

    return points


test_input = [
    "1",
    "10",
    "100",
    "2024",
]

test_points = GetAns(test_input)
if test_points != 37327623:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"))
print(points)

# submit(points)
