with open("data/day5.in") as f:
    lines = f.readlines()
    if lines[-1][-1] != "\n":
        lines[-1] += "\n"

    lines = [line[:-1] for line in lines]
    lines = [line for line in lines if line]

    seeds = [int(x) for x in lines[0][7:].split(" ")]
    seeds = [(seeds[i], seeds[i + 1]) for i in range(0, len(seeds), 2)]

    new_seeds = list(seeds)

    for line in lines[1:]:
        if "map" in line:
            seeds = list(new_seeds)
        else:
            dest_start, src_start, length = (int(x) for x in line.split(" "))
            src_end = src_start + length

            split_seeds = []
            for seed in seeds:
                if seed[0] < src_start:
                    split_seeds.append((seed[0], src_start - seed))
                    split_seeds.append((src_start, seed[0] + seed[1] - src_start))

            for i, seed in enumerate(seeds):
                if src_start <= seed and seed < src_start + length:
                    new_seeds[i] = dest_start + seed - src_start

    seeds = list(new_seeds)
