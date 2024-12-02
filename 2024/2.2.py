with open("data/2.txt") as f:
    lines = f.readlines()

    points = 0

    for line in lines:
        nums = [int(x) for x in line.split(" ")]

        nr_to_remove = 0

        while nr_to_remove < len(nums):
            increasing = True
            decreasing = True
            good = True

            copy = list(nums)

            if nr_to_remove >= 0:
                del copy[nr_to_remove]

            for i in range(1, len(copy)):
                diff = copy[i] - copy[i - 1]
                abs_diff = abs(diff)

                if abs_diff < 1 or abs_diff > 3:
                    good = False

                if copy[i] > copy[i - 1]:
                    decreasing = False
                if copy[i] < copy[i - 1]:
                    increasing = False

            if (increasing or decreasing) and good:
                points += 1
                break
            nr_to_remove += 1

    print(points)
