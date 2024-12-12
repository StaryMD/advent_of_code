from aocd import data, submit

ITS = 25


def GetAns(text):
    nums = [int(x) for x in text.split(" ")]

    for it in range(ITS):
        for i, num in enumerate(nums[: len(nums)]):
            if num == 0:
                nums[i] = 1
            elif len(s := str(num)) % 2 == 0:
                nums[i] = int(s[: len(s) // 2])
                i += 1
                nums.append(int(s[len(s) // 2 :]))
            else:
                nums[i] *= 2024
            i += 1

    return len(nums)


test_input = "125 17"

print(GetAns(test_input))

# submit(points)
