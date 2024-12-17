from aocd import data, submit
import random
import sys


def difference(seq1, seq2):
    if len(seq1) != len(seq2):
        return 100

    count = 0
    for i in range(len(seq1)):
        if seq1[i] != seq2[i]:
            count += 1
    return count


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


class ProgramState:
    reg_a: int
    reg_b: int
    reg_c: int

    program: list[int]
    combo_operands = [0, 2, 5, 6, 7]

    def __init__(self, a, b, c, p):
        self.IP = 0

        self.reg_a = a
        self.reg_b = b
        self.reg_c = c
        self.program = p

        self.cache = {}

    def halted(self):
        return self.IP >= len(self.program)

    def id(self):
        return (self.reg_a, self.reg_b, self.reg_c, self.IP)

    def adv(self, output):
        inst = self.program[self.IP]
        op = self.program[self.IP + 1]

        if inst in self.combo_operands:
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
                output.append(op % 8)
            case 6:
                self.reg_b = self.reg_a // 2**op
            case 7:
                self.reg_c = self.reg_a // 2**op
            case _:
                pass

        self.IP += 2

        return output

    def run(self):
        output = []

        while self.IP < len(self.program):
            output = self.adv(output)

        return output


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
