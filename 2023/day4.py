with open("data/day4.in") as f:
    points = 0

    for line in f.readlines():
        matches = 0
        line = line[line.find(":") + 1 : -1]

        left = [int(x) for x in line[: line.find("|") - 1].split(" ") if x]
        right = [int(x) for x in line[line.find("|") + 1 :].split(" ") if x]

        for num in right:
            if num in left:
                matches += 1

        if matches != 0:
            points += 1 << (matches - 1)

    print(points)
