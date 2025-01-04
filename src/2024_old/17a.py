from aocd import data, submit


class ProgramState:
    reg_a: int
    reg_b: int
    reg_c: int

    program: list[int]

    IP = 0
    output = []

    def __init__(self, a, b, c, p):
        self.reg_a = a
        self.reg_b = b
        self.reg_c = c
        self.program = p

    def adv(self):
        combo_operands = [0, 2, 5, 6, 7]

        while self.IP < len(self.program):
            inst = int(self.program[self.IP])
            op = int(self.program[self.IP + 1])

            if inst in combo_operands:
                match op:
                    case 4:
                        op = self.reg_a
                    case 5:
                        op = self.reg_b
                    case 6:
                        op = self.reg_c

            match inst:
                case 0:
                    self.reg_a = self.reg_a // 2**op
                case 1:
                    self.reg_b = self.reg_b ^ op
                case 2:
                    self.reg_b = op % 8
                case 3:
                    if self.reg_a != 0:
                        self.IP = op - 2
                case 4:
                    self.reg_b = self.reg_b ^ self.reg_c
                case 5:
                    self.output.append(op % 8)
                case 6:
                    self.reg_b = self.reg_a // 2**op
                case 7:
                    self.reg_c = self.reg_a // 2**op
                case _:
                    pass

            self.IP += 2


def GetNextDigit(a, b, c):
    b = a % 8
    b = b ^ 5
    c = a >> b
    b = b ^ 6
    a = a >> 3
    b = b ^ c

    return a, b, c


def GetAns(text):
    reg_a = int(text[0][12:])
    reg_b = int(text[1][12:])
    reg_c = int(text[2][12:])

    program = text[4][9:]

    program = program.split(",")

    ans = []

    IP = 0
    ints_executed = 0

    combo_operands = [0, 2, 5, 6, 7]

    while IP < len(program):
        ints_executed += 1
        inst = int(program[IP])
        op = int(program[IP + 1])

        if inst in combo_operands:
            match op:
                case 4:
                    op = reg_a
                case 5:
                    op = reg_b
                case 6:
                    op = reg_c

        match inst:
            case 0:
                reg_a = reg_a // 2**op
            case 1:
                reg_b = reg_b ^ op
            case 2:
                reg_b = op % 8
            case 3:
                if reg_a != 0:
                    IP = op - 2
            case 4:
                reg_b = reg_b ^ reg_c
            case 5:
                ans.append(op % 8)
            case 6:
                reg_b = reg_a // 2**op
            case 7:
                reg_c = reg_a // 2**op
            case _:
                pass

        IP += 2
    print(f"Total instr executed: {ints_executed}")

    return ",".join([str(x) for x in ans])


test_input = [
    "Register A: 729",
    "Register B: 0",
    "Register C: 0",
    "",
    "Program: 0,1,5,4,3,0",
]

test_points = GetAns(test_input)
if test_points != "4,6,3,5,6,3,5,2,1,0":
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"))
print(f"Final answer: {points}")

# submit(points)
