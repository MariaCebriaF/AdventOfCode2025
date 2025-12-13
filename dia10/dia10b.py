import re
from ortools.sat.python import cp_model


def parse_line(line: str):
    line = line.strip()
    if not line:
        return None

    # n = longitud dentro de [...]
    m_br = re.search(r"\[([#.]+)\]", line)
    if not m_br:
        raise ValueError(f"No encuentro [....] en: {line}")
    n = len(m_br.group(1))

    # botones: todas las tuplas (...)
    tuples = re.findall(r"\(([^)]*)\)", line)
    buttons = []
    for t in tuples:
        t = t.strip()
        if t == "":
            buttons.append([])
        else:
            buttons.append([int(x.strip()) for x in t.split(",")])

    # objetivo: {...}
    m_obj = re.search(r"\{([^}]*)\}", line)
    if not m_obj:
        raise ValueError(f"No encuentro {{...}} en: {line}")
    target = [int(x.strip()) for x in m_obj.group(1).split(",")]

    if len(target) != n:
        raise ValueError(f"target len {len(target)} != n {n} en: {line}")

    return n, buttons, target


def solve_machine(n, buttons, target):
    model = cp_model.CpModel()
    m = len(buttons)

    # cota superior simple: cada botón no necesita pulsarse más que max(target)
    ub = max(target) if target else 0

    x = [model.NewIntVar(0, ub, f"x{j}") for j in range(m)]

    # restricciones por contador
    for i in range(n):
        model.Add(sum(x[j] for j in range(m) if i in buttons[j]) == target[i])

    # objetivo: minimizar total de pulsaciones
    model.Minimize(sum(x))

    solver = cp_model.CpSolver()
    solver.parameters.max_time_in_seconds = 10.0  # ajusta si quieres
    solver.parameters.num_search_workers = 8

    status = solver.Solve(model)
    if status not in (cp_model.OPTIMAL, cp_model.FEASIBLE):
        return None  # imposible

    return int(solver.ObjectiveValue())


def main():
    total = 0
    ok = 0
    bad = 0

    with open("input.txt", "r", encoding="utf-8") as f:
        for line in f:
            parsed = parse_line(line)
            if not parsed:
                continue
            n, buttons, target = parsed
            ans = solve_machine(n, buttons, target)
            if ans is None:
                bad += 1
            else:
                ok += 1
                total += ans

    print("machines solvable:", ok)
    print("machines impossible:", bad)
    print("TOTAL minimum presses:", total)


if __name__ == "__main__":
    main()
