import sys
import re
import csv
from ortools.sat.python import cp_model


def parse_line(line: str):
    m_br = re.search(r"\[([#.]+)\]", line)
    m_obj = re.search(r"\{([^}]*)\}", line)
    tuples = re.findall(r"\(([^)]*)\)", line)

    if not (m_br and m_obj):
        raise ValueError("Línea inválida: falta [] o {}")

    n = len(m_br.group(1))
    target = [int(x.strip())
              for x in m_obj.group(1).split(",") if x.strip() != ""]

    buttons = []
    for t in tuples:
        t = t.strip()
        if t == "":
            buttons.append([])
        else:
            buttons.append([int(x.strip())
                           for x in t.split(",") if x.strip() != ""])

    if len(target) != n:
        raise ValueError(f"Objetivo tiene longitud {len(target)} pero n={n}")

    return n, buttons, target


def solve_machine(n, buttons, target, time_limit=5.0, workers=8):
    model = cp_model.CpModel()
    m = len(buttons)
    ub = max(target) if target else 0

    x = [model.NewIntVar(0, ub, f"x{j}") for j in range(m)]

    # Restricciones: para cada contador i, suma de botones que lo afectan = target[i]
    for i in range(n):
        model.Add(sum(x[j] for j in range(m) if i in buttons[j]) == target[i])

    # Objetivo: minimizar el total de pulsaciones
    model.Minimize(sum(x))

    solver = cp_model.CpSolver()
    solver.parameters.num_search_workers = workers
    solver.parameters.max_time_in_seconds = time_limit

    status = solver.Solve(model)
    if status not in (cp_model.OPTIMAL, cp_model.FEASIBLE):
        return None

    presses = [solver.Value(v) for v in x]
    return presses


def latex_model(machine_id, n, buttons, target):
    m = len(buttons)

    # Construimos S_i = {j | i in buttons[j]}
    S = []
    for i in range(n):
        S_i = [j for j in range(m) if i in buttons[j]]
        S.append(S_i)

    lines = []
    lines.append(f"% Máquina {machine_id}")
    lines.append(r"\[")
    lines.append(r"\begin{aligned}")
    lines.append(r"\min \quad & \sum_{j=0}^{m-1} x_j \\")
    lines.append(
        r"\text{s.a.}\quad & \sum_{j \in S_i} x_j = b_i \quad \forall i=0,\dots,n-1 \\")
    lines.append(r"& x_j \in \mathbb{Z}_{\ge 0} \quad \forall j=0,\dots,m-1")
    lines.append(r"\end{aligned}")
    lines.append(r"\]")

    # Sustitución explícita de restricciones
    lines.append(r"\[")
    lines.append(r"\begin{aligned}")
    for i in range(n):
        if S[i]:
            lhs = " + ".join([f"x_{j}" for j in S[i]])
        else:
            lhs = "0"
        lines.append(f"{lhs} &= {target[i]} \\\\")
    lines.append(r"\end{aligned}")
    lines.append(r"\]")

    return "\n".join(lines)


def main():
    # Lee todo para poder crear CSV con columnas x0..x(max_m-1) uniforme
    machines = []
    for raw in sys.stdin:
        line = raw.strip()
        if not line:
            continue
        n, buttons, target = parse_line(line)
        machines.append((n, buttons, target))

    if not machines:
        print("No hay máquinas en la entrada.")
        return

    # Resolver y guardar soluciones
    solutions = []
    max_m = 0
    for idx, (n, buttons, target) in enumerate(machines, start=1):
        presses = solve_machine(n, buttons, target)
        m = len(buttons)
        max_m = max(max_m, m)
        solutions.append((idx, n, m, buttons, target, presses))

    # ---- CSV ----
    csv_path = "resultados.csv"
    header = ["machine_id", "n", "m", "total_presses"]
    header += [f"b{i}" for i in range(max(len(t)
                                      for _, _, _, _, t, _ in solutions))]
    header += [f"x{j}" for j in range(max_m)]

    with open(csv_path, "w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(header)

        for machine_id, n, m, buttons, target, presses in solutions:
            if presses is None:
                total = ""
                # (no fiable así)
                bcols = target + [""] * (header.count("b0") - len(target))
                # Mejor: rellenar según max_n real:
                pass

    # Arreglamos el relleno de b correctamente:
    max_n = max(len(target) for _, _, _, _, target, _ in solutions)
    header = ["machine_id", "n", "m", "total_presses"] + \
        [f"b{i}" for i in range(max_n)] + [f"x{j}" for j in range(max_m)]

    with open(csv_path, "w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(header)
        for machine_id, n, m, buttons, target, presses in solutions:
            if presses is None:
                total = ""
                bcols = target + [""] * (max_n - len(target))
                xcols = [""] * max_m
            else:
                total = sum(presses)
                bcols = target + [""] * (max_n - len(target))
                xcols = presses + [""] * (max_m - len(presses))

            w.writerow([machine_id, n, m, total] + bcols + xcols)

    print(f"\n✅ CSV exportado: {csv_path}")

    # ---- Formato matemático + "calculadora" ----
    total_global = 0
    for machine_id, n, m, buttons, target, presses in solutions:
        print("\n" + "=" * 40)
        print(f"Máquina {machine_id}")
        print("=" * 40)

        # Modelo en LaTeX
        print(latex_model(machine_id, n, buttons, target))

        if presses is None:
            print("IMPOSSIBLE (sin solución entera no negativa dentro del límite)")
            continue

        total = sum(presses)
        total_global += total

        print("\nSolución:")
        print("Objetivo b:", target)
        print("Pulsaciones x:", presses)
        print(f"Total pulsaciones: {total}")

        print("\nCalculadora (verificación):")
        for i in range(n):
            s = sum(presses[j] for j in range(m) if i in buttons[j])
            ok = "✓" if s == target[i] else "✗"
            print(f"  Contador {i}: {s} = {target[i]} {ok}")

        print("\nBotones usados (x_j > 0):")
        for j, p in enumerate(presses):
            if p > 0:
                print(f"  x{j} = {p}  (botón {j} afecta {tuple(buttons[j])})")

    print("\n" + "=" * 40)
    print("TOTAL GLOBAL:", total_global)


if __name__ == "__main__":
    main()
