from aocd import data, submit


def PrintProgram(program):
    combo_operands = [0, 2, 5, 6, 7]

    for inst, op in zip(program[::2], program[1::2]):
        if inst in combo_operands:
            match op:
                case 4:
                    op = "a"
                case 5:
                    op = "b"
                case 6:
                    op = "c"

        match inst:
            case 0:
                print(f"a = a >> {op}")
            case 1:
                print(f"b = b ^ {op}")
            case 2:
                print(f"b = {op} % 8")
            case 3:
                print(f"if a != 0: jump {op}")
            case 4:
                print("b = b ^ c")
            case 5:
                print(f"out {op} % 8")
            case 6:
                print(f"b = a >> {op}")
            case 7:
                print(f"c = a >> {op}")
            case _:
                pass


def GetNextDigit(a, b, c):
    b = a % 8
    b = b ^ 5
    c = a >> b
    b = b ^ 6
    a = a >> 3
    b = b ^ c

    return b, c


anses = []


def Solve(program, i, reg_a, reg_b, reg_c):
    if i == len(program):
        anses.append(reg_a)
    else:
        wanted = program[len(program) - i - 1]

        for a in range(0, 8):
            new_b, new_c = GetNextDigit(reg_a * 8 + a, reg_b, reg_c)
            digit = new_b % 8

            if digit == wanted:
                Solve(program, i + 1, reg_a * 8 + a, new_b, new_c)


def GetAns(text):
    program = text.split(",")
    program = [int(x) for x in program]

    # PrintProgram(program)

    Solve(program, 0, 0, 0, 0)

    return min(anses)


points = GetAns("2,4,1,5,7,5,1,6,0,3,4,0,5,5,3,0")
print(points)

# submit(points)
