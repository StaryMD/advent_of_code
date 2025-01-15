from re import findall as re_findall, search as re_search
from os import makedirs
from pathlib import Path
from collections import defaultdict
from argparse import ArgumentParser

from aocd import get_data


def DownloadInput(year: int, day: int, output_dir: str):
    input_str = get_data(day=day, year=year)
    makedirs(output_dir, exist_ok=True)

    with open(output_dir / f"{year}_{day}_input.txt", "w") as f:
        f.write(input_str)


def Main():
    parser = ArgumentParser(prog="AoC setup script")
    parser.add_argument("--srcs", required=True)
    parser.add_argument("--indir", required=True)
    parser.add_argument("--sols", required=True)

    args = parser.parse_args()

    SOURCE_FILES_DIR = Path(args.srcs)
    AOCD_INPUT_DIR = Path(args.indir)
    SOLUTION_FILES_FILE = Path(args.sols)

    solution_files = sorted(
        [
            str(f)
            for f in SOURCE_FILES_DIR.rglob("*.cpp")
            if re_search("([0-9]+)/([0-9]+)/((a|b|both))[.]cpp", str(f))
        ]
    )

    solutions = defaultdict(lambda: defaultdict(list))

    for solution_file in solution_files:
        match = re_findall("([0-9]+)/([0-9]+)/((a|b|both))[.]cpp", solution_file)
        year, day, part = int(match[0][0]), int(match[0][1]), match[0][2].upper()

        if part == "BOTH":
            solutions[year][day].append("A")
            solutions[year][day].append("B")
        else:
            solutions[year][day].append(part)

    if not solutions:
        return

    makedirs(SOLUTION_FILES_FILE.parent, exist_ok=True)

    with open(SOLUTION_FILES_FILE, "w") as file:
        for year, days in solutions.items():
            file.write("{\n")
            file.write(f"  {year}, {{\n")

            for day, parts in days.items():
                DownloadInput(year, day, AOCD_INPUT_DIR)

                file.write("  {\n")
                file.write(f"    {day}, {{\n")

                for part in parts:
                    solve_function = f"Solve<{year}, {day}, '{part}'>"
                    file.write(f"      {{'{part}', {solve_function}}},\n")

                file.write("    },\n")
                file.write("  },\n")

            file.write("  },\n")
            file.write("},\n")


if __name__ == "__main__":
    Main()
