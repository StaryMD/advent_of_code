from aocd import data, submit
import re


def chunker(seq, size):
    return (seq[pos : pos + size] for pos in range(0, len(seq), size))


def GetPoints(prize):
    regex_x = "X[+=]([0-9]+)"
    regex_y = "Y[+=]([0-9]+)"

    a_x = int(re.findall(regex_x, prize[0])[0])
    a_y = int(re.findall(regex_y, prize[0])[0])

    b_x = int(re.findall(regex_x, prize[1])[0])
    b_y = int(re.findall(regex_y, prize[1])[0])

    p_x = int(re.findall(regex_x, prize[2])[0])
    p_y = int(re.findall(regex_y, prize[2])[0])

    best = None

    x_sus = b_x * p_y - b_y * p_x
    x_jos = b_x * a_y - b_y * a_x

    if x_sus % x_jos == 0:
        x = x_sus // x_jos

        y1 = (p_x - x * a_x) // b_x
        y2 = (p_y - x * a_y) // b_y

        if y1 == y2 and x * a_x + y1 * b_x == p_x and x * a_y + y1 * b_y == p_y:
            if not best:
                best = x * 3 + y1
            else:
                best = min(best, x * 3 + y1)

    return best


def GetAns(text):
    points = 0

    for prize in chunker(text, 4):
        prize = prize[:3]

        l_points = GetPoints(prize)
        if l_points:
            points += l_points

    return points


test_input = [
    "Button A: X+94, Y+34",
    "Button B: X+22, Y+67",
    "Prize: X=8400, Y=5400",
    "",
    "Button A: X+26, Y+66",
    "Button B: X+67, Y+21",
    "Prize: X=12748, Y=12176",
    "",
    "Button A: X+17, Y+86",
    "Button B: X+84, Y+37",
    "Prize: X=7870, Y=6450",
    "",
    "Button A: X+69, Y+23",
    "Button B: X+27, Y+71",
    "Prize: X=18641, Y=10279",
]

test_points = GetAns(test_input)
if test_points != 480:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"))
print(points)

# submit(points)
