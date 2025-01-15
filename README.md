# Storage for all my Advent of Code solutions

__[Advent of Code](https://adventofcode.com/)__ is a series of programming challenges.<br>
I choose to first solve the problems using either Python or C++ focusing on development time to get a grasp of the problem statement, but after solving the problem I focus on optimizing the runtime using C++.

## Prerequisites:
1. A Python 3 installation, project was tested on Python 3.12.
    * The python package [aocd](https://pypi.org/project/advent-of-code-data/) is used to download the input to the problems.
2. A cmake package.
3. A C++ compiler.

## Preparing the python virtual environment:
```bash
python -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```

## Building the project:
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Running the report:
Running all the solutions with a certain number of repetitions, will average the runtime over all the runs.
```bash
./bin/report <repetitions>
```

Running all the solutions for a single year.
```bash
./bin/report <repetitions> <year>
```

Running all the solutions for a single day of a single year.
```bash
./bin/report <repetitions> <year> <day>
```

Running all the solutions for a single part of a single day of a single year.
```bash
./bin/report <repetitions> <year> <day> <a | b>
```

__Example__: running both parts of day 17 of year 2024, 1000 times.
```bash
./bin/report 100 2024 17
```
