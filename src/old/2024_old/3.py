import re

with open("data/3.txt") as f:
    text = f.read()

    regex = "mul\\(([0-9]+),([0-9]+)\\)"

    x = re.findall(regex, text)

    points = 0

    for match in x:
        a, b = int(match[0]), int(match[1])

        points += a * b

    print(points)
