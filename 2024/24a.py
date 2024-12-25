from aocd import data, submit


def GetAns(lines: list[str]):
    vars = {}

    blank = lines.index("")

    for line in lines[:blank]:
        var, val = line.replace(" ", "").split(":")
        vars[var] = int(val)

    ops = []

    for line in lines[blank + 1 :]:
        ops.append(tuple(line.replace("-> ", "").split(" ")))

    while ops:
        changed = False
        i = 0

        while i < len(ops):
            try:
                var1, instr, var2, var3 = ops[i]

                match instr:
                    case "AND":
                        vars[var3] = vars[var1] & vars[var2]
                    case "OR":
                        vars[var3] = vars[var1] | vars[var2]
                    case "XOR":
                        vars[var3] = vars[var1] ^ vars[var2]

                ops[i], ops[-1] = ops[-1], ops[i]
                ops.pop()

                changed = True
            except:
                i += 1

        if not changed:
            break

    b_points = ""

    for var, val in sorted(vars.items()):
        if var[0] == "z":
            b_points = str(val) + b_points

    return int(b_points, base=2)


test_input = [
    "x00: 1",
    "x01: 0",
    "x02: 1",
    "x03: 1",
    "x04: 0",
    "y00: 1",
    "y01: 1",
    "y02: 1",
    "y03: 1",
    "y04: 1",
    "",
    "ntg XOR fgs -> mjb",
    "y02 OR x01 -> tnw",
    "kwq OR kpj -> z05",
    "x00 OR x03 -> fst",
    "tgd XOR rvg -> z01",
    "vdt OR tnw -> bfw",
    "bfw AND frj -> z10",
    "ffh OR nrd -> bqk",
    "y00 AND y03 -> djm",
    "y03 OR y00 -> psh",
    "bqk OR frj -> z08",
    "tnw OR fst -> frj",
    "gnj AND tgd -> z11",
    "bfw XOR mjb -> z00",
    "x03 OR x00 -> vdt",
    "gnj AND wpb -> z02",
    "x04 AND y00 -> kjc",
    "djm OR pbm -> qhw",
    "nrd AND vdt -> hwm",
    "kjc AND fst -> rvg",
    "y04 OR y02 -> fgs",
    "y01 AND x02 -> pbm",
    "ntg OR kjc -> kwq",
    "psh XOR fgs -> tgd",
    "qhw XOR tgd -> z09",
    "pbm OR djm -> kpj",
    "x03 XOR y03 -> ffh",
    "x00 XOR y04 -> ntg",
    "bfw OR bqk -> z06",
    "nrd XOR fgs -> wpb",
    "frj XOR qhw -> z04",
    "bqk OR frj -> z07",
    "y03 OR x01 -> nrd",
    "hwm AND bqk -> z03",
    "tgd XOR rvg -> z12",
    "tnw OR pbm -> gnj",
]

test_points = GetAns(test_input)
if test_points != 2024:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"))
print(points)

# submit(points)
