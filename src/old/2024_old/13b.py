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

    p_x = int(re.findall(regex_x, prize[2])[0]) + 10000000000000
    p_y = int(re.findall(regex_y, prize[2])[0]) + 10000000000000

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


points = GetAns(data.split("\n"))
print(points)

# submit(points)
