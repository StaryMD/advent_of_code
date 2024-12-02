with open("data/day5.in") as f:
    lines = f.readlines()
    if lines[-1][-1] != "\n":
        lines[-1] += "\n"

    lines = [line[:-1] for line in lines]
    lines = [line for line in lines if line]

    seeds = [int(x) for x in lines[0][7:].split(" ")]

    new_seeds = list(seeds)

    for line in lines[1:]:
        if "map" in line:
            seeds = list(new_seeds)
        else:
            dest, src, length = (int(x) for x in line.split(" "))

            for i, seed in enumerate(seeds):
                if src <= seed and seed < src + length:
                    new_seeds[i] = dest + seed - src

    seeds = list(new_seeds)

    print(min(seeds))
