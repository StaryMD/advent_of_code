from aocd import data, submit


def GetAns(lines: list[str]):
    blank = lines.index("")

    ops = []

    for line in lines[blank + 1 :]:
        op = line.replace("-> ", "").split(" ")

        ops.append(tuple(op))

    lookup = set()
    swapped = set()

    for in1, instr, in2, out in ops:
        lookup.add((in1, instr))
        lookup.add((in2, instr))

    for in1, instr, in2, out in ops:
        match instr:
            case "AND":
                if in1 != "x00" and in2 != "x00" and (out, "OR") not in lookup:
                    swapped.add(out)
            case "OR":
                if out[0] == "z" and out != "z45":
                    swapped.add(out)

                if (out, "OR") in lookup:
                    swapped.add(out)
            case "XOR":
                if in1[0] == "x" or in2[0] == "x":
                    if in1 != "x00" and in2 != "x00" and (out, "XOR") not in lookup:
                        swapped.add(out)
                else:
                    if out[0] != "z":
                        swapped.add(out)

    return ",".join(sorted(swapped))


answer = GetAns(data.split("\n"))


print(f"Answer: {answer}")

# submit(answer)
