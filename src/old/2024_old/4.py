from aocd import submit

with open("data/4.txt") as f:
    lines = f.readlines()

    for i, line in enumerate(lines):
        if line[-1] == "\n":
            lines[i] = line[:-1]


def GetPoints(lines):
    points = 0

    deltas = (
        (0, 1),
        (1, 1),
        (1, 0),
        (1, -1),
        (0, -1),
        (-1, -1),
        (-1, 0),
        (-1, 1),
    )

    for y in range(len(lines)):
        for x in range(len(lines[y])):
            for d in deltas:
                if (0 <= y + 3 * d[0] < len(lines)) and (
                    0 <= x + 3 * d[1] < len(lines[y])
                ):
                    s = ""
                    for i in range(4):
                        try:
                            s += lines[y + i * d[0]][x + i * d[1]]
                        except IndexError:
                            s = ""
                            break

                    if s == "XMAS":
                        points += 1
                        print(points, (y + 1, x + 1), d)

    return points


test_lines = [
    "MMMSXXMASM",
    "MSAMXMSMSA",
    "AMXSXMAAMM",
    "MSAMASMSMX",
    "XMASAMXAMM",
    "XXAMMXXAMA",
    "SMSMSASXSS",
    "SAXAMASAAA",
    "MAMMMXMMMM",
    "MXMXAXMASX",
]

test_points = GetPoints(test_lines)

if test_points != 18:
    print(f"Test failed with points = {test_points}")
    quit()

points = GetPoints(lines)
print(points)
