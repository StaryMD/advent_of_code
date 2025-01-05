from aocd import data, submit

ITS = 75

map = [{} for i in range(ITS + 1)]


def GetLength(num, it):
    if it >= ITS:
        return 1

    if num in map[it]:
        return map[it][num]

    if num == 0:
        ans = GetLength(1, it + 1)
    elif len(s := str(num)) % 2 == 0:
        ans = GetLength(int(s[: len(s) // 2]), it + 1) + GetLength(int(s[len(s) // 2 :]), it + 1)
    else:
        ans = GetLength(num * 2024, it + 1)

    map[it][num] = ans

    return ans


def GetAns(text):
    nums = [int(x) for x in text.split(" ")]

    return sum(GetLength(num, 0) for num in nums)


test_input = "125 17"

print(GetAns(test_input))

test_points = GetAns(test_input)

points = GetAns(data)
print(points)

# submit(points)
