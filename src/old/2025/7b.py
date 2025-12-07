from collections import defaultdict

from aocd import data, submit


def GetAns(lines: list[str]):
    first_beam = lines[0].find("S")

    beams = defaultdict(int)
    beams[first_beam] = 1

    ans = 0

    for y, line in enumerate(lines[1:]):
        new_beams = defaultdict(int)

        for x, c in enumerate(line):
            if c == ".":
                if x in beams:
                    new_beams[x] += beams[x]
            elif c == "^":
                if x in beams:
                    ans += beams[x]
                    new_beams[x - 1] += beams[x]
                    new_beams[x + 1] += beams[x]
            else:
                raise RuntimeError(f"fuck : {c}")

        beams = new_beams

    return ans + 1


points = GetAns(data.split("\n"))
print(points)

# submit(points)
