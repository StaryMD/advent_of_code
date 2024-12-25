from aocd import data, submit


def GetAns(lines):
    y, x = 0, 0

    while "^" not in lines[y]:
        y += 1

    while lines[y][x] != "^":
        x += 1

    s = set((y, x))

    dirs = (
        (-1, 0),
        (0, 1),
        (1, 0),
        (0, -1),
    )
    dir = 0

    while y > 0 and y < (len(lines) - 1) and x > 0 and x < (len(lines[0]) - 1):
        new_y = y + dirs[dir][0]
        new_x = x + dirs[dir][1]

        if lines[new_y][new_x] == "#":
            dir = (dir + 1) % 4
        else:
            s.add((y, x))
            y, x = new_y, new_x

    return len(s) - 1


test_input = [
    "....#.....",
    ".........#",
    "..........",
    "..#.......",
    ".......#..",
    "..........",
    ".#..^.....",
    "........#.",
    "#.........",
    "......#...",
]

test_points = GetAns(test_input)
if test_points != 41:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"))
print(points)

# submit(points)
