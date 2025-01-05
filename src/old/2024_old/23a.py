from aocd import data, submit
from collections import defaultdict


def GetAns(connections):
    graph = defaultdict(list)

    for connection in connections:
        left, right = connection.split("-")

        graph[left].append(right)
        graph[right].append(left)

    for left in graph:
        print(f"{left}: {graph[left]}")

    groups = set()

    def DFS(group):
        if len(group) == 3:
            a, b, c = group

            if a[0] == "t" or b[0] == "t" or c[0] == "t":
                group = sorted(group)
                groups.add((group[0], group[1], group[2]))
            return

        for other in graph[group[-1]]:
            DFS(group + [other])

    for node in graph:
        DFS([node])

    groups2 = set()

    for group in groups:
        a, b, c = group

        if a in graph[b] and a in graph[c] and b in graph[c]:
            groups2.add(group)

    # for group in groups2:
    #     print(",".join(group))
    # print("fuck ", len(groups2))

    return len(groups2)


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
