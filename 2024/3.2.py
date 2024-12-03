import re

with open("data/3.txt") as f:
    text = f.read()

    points = 0

    for i, line in enumerate(text.split("do()")):
        index = line.find("don't()")

        if index != -1:
            line = line[:index]

        regex = "mul\\(([0-9]+),([0-9]+)\\)"

        for match in re.findall(regex, line):
            a, b = int(match[0]), int(match[1])

            points += a * b

    print(points)
    print(85508223 == points)
