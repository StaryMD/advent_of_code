from aocd import data, submit
from collections import defaultdict


def GetAns(connections):
    graph = defaultdict(list)

    for connection in connections:
        left, right = connection.split("-")

        graph[left].append(right)
        graph[right].append(left)

    groups = set()

    for node1 in graph:
        if node1[0] == "t":
            for node2 in graph[node1]:
                for node3 in graph[node2]:
                    if node3 in graph[node1]:
                        group = sorted((node1, node2, node3))
                        groups.add((group[0], group[1], group[2]))

    return len(groups)


test_input = [
    "kh-tc",
    "qp-kh",
    "de-cg",
    "ka-co",
    "yn-aq",
    "qp-ub",
    "cg-tb",
    "vc-aq",
    "tb-ka",
    "wh-tc",
    "yn-cg",
    "kh-ub",
    "ta-co",
    "de-co",
    "tc-td",
    "tb-wq",
    "wh-td",
    "ta-ka",
    "td-qp",
    "aq-cg",
    "wq-ub",
    "ub-vc",
    "de-ta",
    "wq-aq",
    "wq-vc",
    "wh-yn",
    "ka-de",
    "kh-ta",
    "co-tc",
    "wh-qp",
    "tb-vc",
    "td-yn",
]

test_points = GetAns(test_input)
if test_points != 7:
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

points = GetAns(data.split("\n"))
print(points)

# submit(points)
