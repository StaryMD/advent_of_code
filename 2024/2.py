import math

with open("data/2.txt") as f:
    lines = f.readlines()

    points = 0

    for line in lines:
        nums = [int(x) for x in line.split(" ")]

        increasing = True
        decreasing = True
        good = True

        for i in range(1, len(nums)):
            diff = nums[i] - nums[i - 1]
            abs_diff = abs(diff)

            if abs_diff < 1 or abs_diff > 3:
                good = False

            if nums[i] > nums[i - 1]:
                decreasing = False
            if nums[i] < nums[i - 1]:
                increasing = False

        if (increasing or decreasing) and good:
            points += 1

    print(points)
