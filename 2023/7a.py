from aocd import data, submit
from numpy import prod


def GetAns(text):
    card_power = {
        "A": 12,
        "K": 11,
        "Q": 10,
        "J": 9,
        "T": 8,
        "9": 7,
        "8": 6,
        "7": 5,
        "6": 4,
        "5": 3,
        "4": 2,
        "3": 1,
        "2": 0,
    }

    def Power(hand: str):
        map = {i: hand.count(i) for i in set(hand)}

        score = 0
        for i, c in enumerate(reversed(hand)):
            score += card_power[c] * 12**i

        if len(map) == 1:
            return 5 * 12**5 + score
        elif len(map) == 2:
            return 4 * 12**5 + score
        elif 3 in [f[1] for f in map.items()]:
            return 3 * 12**5 + score
        elif len(map) == 3:
            return 2 * 12**5 + score
        elif len(map) == 4:
            return 1 * 12**5 + score
        return score

    stuff = [line.split(" ") for line in text]

    stuff = sorted(stuff, key=lambda x: Power(x[0]))

    return sum((i + 1) * int(a[1]) for i, a in enumerate(stuff))


test_input = [
    "32T3K 765",
    "T55J5 684",
    "KK677 28",
    "KTJJT 220",
    "QQQJA 483",
]

test_points = GetAns(test_input)
if test_points != 6440:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"))
print(points)

# submit(points)
