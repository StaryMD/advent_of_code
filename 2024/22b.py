from aocd import data, submit


def Next(n):
    m = 16777216

    n ^= n * 64
    n %= m

    n ^= n // 32
    n %= m

    n ^= n * 2048
    n %= m

    return n


def GetAns(text):
    prices = []

    for line in text:
        price = {}
        n = int(line)

        nums = [n % 10]

        for i in range(2000):
            n = Next(n)
            nums.append(n % 10)

        for i in range(1, len(nums) - 3):
            diff = (
                nums[i + 0] - nums[i - 1],
                nums[i + 1] - nums[i + 0],
                nums[i + 2] - nums[i + 1],
                nums[i + 3] - nums[i + 2],
            )

            if diff not in price:
                price[diff] = nums[i + 3]
        prices.append(price)

    def GetValue(diff):
        return sum(price[diff] for price in prices if diff in price)

    diffs_to_check = set()
    for price in prices:
        diffs_to_check.update(diff for diff in price)

    best_price = 0

    for diff in diffs_to_check:
        val = GetValue(diff)

        if val > best_price:
            best_price = val

    return best_price


test_input = [
    "1",
    "2",
    "3",
    "2024",
]

test_points = GetAns(test_input)
if test_points != 23:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"))
print(points)

# submit(points)
