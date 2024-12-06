from aocd import data, submit


def GetAns(text: list):
    br = text.index("")

    map = {}

    for line in text[:br]:
        a, b = [int(x) for x in line.split("|")]

        if a not in map:
            map[a] = [b]
        else:
            map[a].append(b)

    points = 0

    for line in text[br + 1 :]:
        nums = [int(x) for x in line.split(",")]

        good = True
        for i, num in enumerate(nums):
            for j, num2 in enumerate(nums[i + 1 :]):
                if num2 in map and num in map[num2]:
                    good = False

        if not good:
            for i, num in enumerate(nums):
                for j, num2 in enumerate(nums[i + 1 :]):
                    if num2 in map and num in map[num2]:
                        nums[i], nums[j + i + 1] = nums[j + i + 1], nums[i]
                        num = nums[i]

            points += nums[len(nums) // 2]

    return points


test_input = [
    "47|53",
    "97|13",
    "97|61",
    "97|47",
    "75|29",
    "61|13",
    "75|53",
    "29|13",
    "97|29",
    "53|29",
    "61|53",
    "97|53",
    "61|29",
    "47|13",
    "75|47",
    "97|75",
    "47|61",
    "75|61",
    "47|29",
    "75|13",
    "53|13",
    "",
    "75,47,61,53,29",
    "97,61,53,29,13",
    "75,29,13",
    "75,97,47,61,53",
    "61,13,29",
    "97,13,75,29,47",
]

test_points = GetAns(test_input)
if test_points != 123:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"))
print(points)

# submit(points)
