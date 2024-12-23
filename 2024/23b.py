from aocd import data, submit
from collections import defaultdict


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
            good = True

            for node in group:
                if not good:
                    break
                for node2 in group:
                    if node2 not in graph[node]:
                        good = False
                        break

            if good:
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

points = GetAns(data.split("\n"))
print(points)

# submit(points)
