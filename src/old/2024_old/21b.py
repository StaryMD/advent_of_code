from aocd import data, submit
from itertools import permutations
from functools import cache


numpad_coords = {
    "7": (1, 1),
    "8": (1, 2),
    "9": (1, 3),
    "4": (2, 1),
    "5": (2, 2),
    "6": (2, 3),
    "1": (3, 1),
    "2": (3, 2),
    "3": (3, 3),
    "0": (4, 2),
    "A": (4, 3),
}

numpad = [
    "#####",
    "#789#",
    "#456#",
    "#123#",
    "##0A#",
    "#####",
]

dirpad_coords = {
    "^": (0, 1),
    "A": (0, 2),
    "<": (1, 0),
    "v": (1, 1),
    ">": (1, 2),
}


def GetAllPaths(start, end):
    if start == end:
        yield "A"
        return

    if start in "<>^v" or end in "<>^v":
        if start == "<":
            for path in GetAllPaths("v", end):
                yield ">" + path
        elif end == "<":
            for path in GetAllPaths(start, "v"):
                yield path[:-1] + "<A"
        else:
            diff = (
                dirpad_coords[end][0] - dirpad_coords[start][0],
                dirpad_coords[end][1] - dirpad_coords[start][1],
            )
            path = ""

            if diff[0] < 0:
                path += "^" * -diff[0]
            elif diff[0] > 0:
                path += "v" * diff[0]

            if diff[1] < 0:
                path += "<" * -diff[1]
            elif diff[1] > 0:
                path += ">" * diff[1]

            for perm in permutations(path):
                yield "".join(perm) + "A"
    else:
        start_coord = numpad_coords[start]
        end_coord = numpad_coords[end]

        diff = (
            end_coord[0] - start_coord[0],
            end_coord[1] - start_coord[1],
        )

        allowed_dirs = []

        if diff[0] > 0:
            allowed_dirs.append((1, 0, "v"))
        elif diff[0] < 0:
            allowed_dirs.append((-1, 0, "^"))

        if diff[1] > 0:
            allowed_dirs.append((0, 1, ">"))
        elif diff[1] < 0:
            allowed_dirs.append((0, -1, "<"))

        paths = []

        def DFS(coord, path):
            if numpad[coord[0]][coord[1]] == "#":
                return
            if coord == end_coord:
                paths.append(path)
                return

            for dir in allowed_dirs:
                DFS((coord[0] + dir[0], coord[1] + dir[1]), path + dir[2])

        DFS(start_coord, "")

        for path in paths:
            yield path + "A"


@cache
def GetCost(code, indirections):
    if indirections == 0:
        return len(code)

    total_cost = 0
    prev = "A"

    for key in code:
        best_cost = 10 ** (indirections * 2)

        for path in GetAllPaths(prev, key):
            best_cost = min(best_cost, GetCost(path, indirections - 1))

        prev = key
        total_cost += best_cost

    return total_cost


def GetAns(codes):
    points = 0

    for code in codes:
        points += int(code[:3]) * GetCost(code, 26)

    return points


points = GetAns(data.split("\n"))
print(points)

# submit(points)
