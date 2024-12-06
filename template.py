from aocd import data, submit


def GetAns(text):
    return 0


test_input = [
]

test_points = GetAns(test_input)
if test_points != 0:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"))
print(points)

# submit(points)
