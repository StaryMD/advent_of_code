with open("data/day4.in") as f:
    points = []

    for line in f.readlines():
        matches = 0
        line = line[line.find(":") + 1 : -1]

        left = [int(x) for x in line[: line.find("|") - 1].split(" ") if x]
        right = [int(x) for x in line[line.find("|") + 1 :].split(" ") if x]

        for num in right:
            if num in left:
                matches += 1

        points.append([matches, 1])

    for i, (matches, copies) in enumerate(points):
        for j in range(i + 1, i + matches + 1):
            points[j][1] += copies

    sum = sum([copies for _, copies in points])

    print(sum)
