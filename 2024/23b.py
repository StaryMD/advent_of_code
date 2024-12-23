from aocd import data, submit
from collections import defaultdict
import time


def GetAns(connections):
    graph = defaultdict(list)

    for connection in connections:
        left, right = connection.split("-")

        graph[left].append(right)
        graph[right].append(left)
        graph[left].append(left)
        graph[right].append(right)

    GetAns.biggest_group = []

    def DFS(group, visited):
        node = group[-1]

        if node in visited:
            return
        visited[node] = True

        if len(group) > len(GetAns.biggest_group):
            for node2 in group[:-1]:
                if node not in graph[node2]:
                    return

            GetAns.biggest_group = group

        for other in graph[node]:
            DFS(group + [other], visited)

    for node in graph:
        DFS([node], {})

    return ",".join(sorted(GetAns.biggest_group))


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

if test_points != "co,de,ka,ta":
    raise RuntimeError(f"Example test not passed with ans = {test_points}")

start_s = time.time()
points = GetAns(data.split("\n"))
end_s = time.time()
print(f"Elapsed time: {(end_s - start_s) * 1e3:0.3f}ms")
print(points)

# submit(points)
