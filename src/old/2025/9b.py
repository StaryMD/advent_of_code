from aocd import data, submit
from numba import jit
import numpy as np


def is_contained(row, min_x, max_x):
    for left, right in row:
        if left <= min_x and max_x <= right:
            return True

    return False


def is_good(rows, min_y, max_y, min_x, max_x):
    for y in range(min_y, max_y + 1):
        if not is_contained(rows[y], min_x, max_x):
            return False

    return True


def get_answer(points):
    rows = [0] * (max(p[1] for p in points) + 2)

    for i, row in enumerate(rows):
        rows[i] = set()

    for i in range(len(points)):
        a = points[i % len(points)]
        b = points[(i + 1) % len(points)]

        min_x = min(a[0], b[0])
        max_x = max(a[0], b[0])
        min_y = min(a[1], b[1])
        max_y = max(a[1], b[1])

        for y in range(min_y, max_y + 1):
            rows[y].add((min_x, max_x))

    for i, row in enumerate(rows):
        row = sorted(list(row))

        j = 0
        while j < len(row) - 1:
            if row[j][0] == row[j][1]:
                row[j] = (row[j][0], row[j + 1][1])
                del row[j + 1]
            else:
                j += 1

        j = 0
        while j < len(row) - 1:
            if row[j][1] == row[j + 1][0]:
                row[j] = (row[j][0], row[j + 1][1])
                del row[j + 1]
            else:
                j += 1

        rows[i] = row

    max_area = 0

    for i, a in enumerate(points):
        print(i)
        for b in points[i + 1 :]:
            area = (abs(b[0] - a[0]) + 1) * (abs(b[1] - a[1]) + 1)

            if area <= max_area:
                continue

            min_x = min(a[0], b[0])
            max_x = max(a[0], b[0])

            min_y = min(a[1], b[1])
            max_y = max(a[1], b[1])

            if is_good(rows, min_y, max_y, min_x, max_x):
                max_area = area

    return max_area


def get_ans(lines):
    points = [tuple(int(x) for x in line.split(",")) for line in lines]

    return get_answer(points)


with open("test_input.txt") as f:
    test_input = [line[:-1] for line in f.readlines()]

test_points = get_ans(test_input)
if test_points != 24:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = get_ans(data.split("\n"))
print(points)

# submit(points)

# 4655203908 too high
# 778734 too low
