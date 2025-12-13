import sys
import re
import csv
from dataclasses import dataclass
from typing import List, Optional, Tuple
from ortools.sat.python import cp_model


# ----------------------------
# Parsing
# ----------------------------

@dataclass
class Machine:
    machine_id: int
    pattern: str
    n: int
    buttons: List[List[int]]   # list of affected indices per button
    target: List[int]          # b_i


LINE_RE_BRACKETS = re.compile(r"\[([#.]+)\]")
LINE_RE_TARGET = re.compile(r"\{([^}]*)\}")
LINE_RE_TUPLES = re.compile(r"\(([^)]*)\)")


def parse_line_to_machine(line: str, machine_id: int) -> Machine:
    m_br = LINE_RE_BRACKETS.search(line)
    m_tg = LINE_RE_TARGET.search(line)
    tuples = LINE_RE_TUPLES.findall(line)

    if not m_br or not m_tg:
        raise ValueError(f"Línea inválida (falta [] o {{}}): {line[:120]}...")

    pattern = m_br.group(1)
    n = len(pattern)

    target = [int(x.strip())
              for x in m_tg.group(1).split(",") if x.strip() != ""]
    if len(target) != n:
        raise ValueError(
            f"Machine {machine_id}: target len={len(target)} pero n={n}")

    buttons: List[List[int]] = []
    for t in tuples:
        t = t.strip()
        if t == "":
            buttons.append([])
            continue
        idxs = [int(x.strip()) for x in t.split(",") if x.strip() != ""]
        # Validación rápida
        for i in idxs:
            if i < 0 or i >= n:
                raise ValueError(
                    f"Machine {machine_id}: índice {i} fuera de rango 0..{n-1}")
        buttons.append(sorted(set(idxs)))

    return Machine(machine_id=machine_id, pattern=pattern, n=n, buttons=buttons, target=target)


def read_input(stdin) -> List[Machine]:
    machines = []
    machine_id = 1
    for raw in stdin:
        line = raw.strip()
        if not line:
            continue
        machines.append(parse_line_to_machine(line, machine_id))
        machine_id += 1
    return machines


# ----------------------------
# Solve (CP-SAT)
# ----------------------------

@dataclass
class Solution:
    machine_id: int
    status: str
    total_presses: Optional[int]
    x: Optional[List[int]]


def solve_machine(machine: Machine, time_limit: float = 8.0, workers: int = 8) -> Solution:
    n = machine.n
    buttons = machine.buttons
    target = machine.target
    m = len(buttons)

    model = cp_model.CpModel()

    # Upper bound razonable: no tiene sentido pulsar más que max(target) en un botón
    ub = max(target) if target else 0

    x = [model.NewIntVar(0, ub, f"x{j}") for j in range(m)]

    # Precompute S_i (botones que afectan al contador i)
    affects = [[] for _ in range(n)]
    for j, lst in enumerate(buttons):
        for i in lst:
            affects[i].append(j)

    # Restricciones: sum_{j in S_i} x_j = b_i
    for i in range(n):
        model.Add(sum(x[j] for j in affects[i]) == target[i])

    # Objetivo: minimizar total pulsaciones
    model.Minimize(sum(x))

    solver = cp_model.CpSolver()
    solver.parameters.max_time_in_seconds = time_limit
    solver.parameters.num_search_workers = workers

    st = solver.Solve(model)

    if st == cp_model.OPTIMAL:
        presses = [solver.Value(v) for v in x]
        return Solution(machine_id=machine.machine_id, status="OPTIMAL", total_presses=sum(presses), x=presses)
    if st == cp_model.FEASIBLE:
        presses = [solver.Value(v) for v in x]
        return Solution(machine_id=machine.machine_id, status="FEASIBLE", total_presses=sum(presses), x=presses)

    if st == cp_model.INFEASIBLE:
        return Solution(machine_id=machine.machine_id, status="INFEASIBLE", total_presses=None, x=None)
    if st == cp_model.MODEL_INVALID:
        return Solution(machine_id=machine.machine_id, status="MODEL_INVALID", total_presses=None, x=None)
    return Solution(machine_id=machine.machine_id, status="UNKNOWN", total_presses=None, x=None)


# ----------------------------
# Pretty “calculator” + LaTeX
# ----------------------------

def compact_buttons_used(machine: Machine, x: List[int]) -> str:
    parts = []
    for j, pj in enumerate(x):
        if pj > 0:
            parts.append(f"({','.join(map(str, machine.buttons[j]))})*{pj}")
    return " + ".join(parts) if parts else "0"


def verify_counters(machine: Machine, x: List[int]) -> List[int]:
    n = machine.n
    m = len(machine.buttons)
    vals = [0] * n
    for j in range(m):
        pj = x[j]
        if pj == 0:
            continue
        for i in machine.buttons[j]:
            vals[i] += pj
    return vals


def latex_for_machine(machine: Machine, sol: Solution) -> str:
    n = machine.n
    m = len(machine.buttons)

    # S_i
    affects = [[] for _ in range(n)]
    for j, lst in enumerate(machine.buttons):
        for i in lst:
            affects[i].append(j)

    out = []
    out.append(f"% Machine {machine.machine_id}")
    out.append(r"\subsection*{Machine " + str(machine.machine_id) + r"}")
    out.append(r"\textbf{Pattern:} \texttt{[" + machine.pattern + r"]}\\")
    out.append(r"\textbf{Targets:} $" +
               r"\{" + ",".join(map(str, machine.target)) + r"\}$\\")
    out.append(r"\textbf{Buttons:}\\")
    out.append(r"\begin{itemize}")
    for j, lst in enumerate(machine.buttons):
        out.append(
            rf"\item $x_{{{j}}}$ affects $\{{{','.join(map(str, lst))}\}}$")
    out.append(r"\end{itemize}")

    out.append(r"\[")
    out.append(r"\begin{aligned}")
    out.append(r"\min \quad & \sum_{j=0}^{"+str(m-1)+r"} x_j \\")
    out.append(
        r"\text{s.t.}\quad & \sum_{j \in S_i} x_j = b_i \quad \forall i=0,\dots,"+str(n-1)+r" \\")
    out.append(r"& x_j \in \mathbb{Z}_{\ge 0}")
    out.append(r"\end{aligned}")
    out.append(r"\]")

    out.append(r"\[")
    out.append(r"\begin{aligned}")
    for i in range(n):
        if affects[i]:
            lhs = " + ".join([f"x_{{{j}}}" for j in affects[i]])
        else:
            lhs = "0"
        out.append(lhs + f" &= {machine.target[i]} \\\\")
    out.append(r"\end{aligned}")
    out.append(r"\]")

    if sol.x is None:
        out.append(r"\textbf{Status:} " + sol.status + r"\\")
        return "\n".join(out)

    x = sol.x
    out.append(r"\textbf{Solution:} \\")
    out.append(r"\[")
    out.append(r"\begin{aligned}")
    for j, pj in enumerate(x):
        if pj > 0:
            out.append(f"x_{{{j}}} &= {pj} \\\\")
    out.append(r"\end{aligned}")
    out.append(r"\]")

    out.append(r"\textbf{Total presses:} " + str(sol.total_presses) + r"\\")
    return "\n".join(out)


# ----------------------------
# CSV exports (human friendly)
# ----------------------------

def write_csvs(machines: List[Machine], sols: List[Solution]) -> None:
    # Summary per machine
    with open("machines_summary.csv", "w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow([
            "machine_id", "pattern", "n", "num_buttons",
            "status", "total_presses",
            "targets_braced", "solution_compact", "solution_vector"
        ])
        for machine, sol in zip(machines, sols):
            if sol.x is None:
                w.writerow([
                    machine.machine_id, f"[{machine.pattern}]", machine.n, len(
                        machine.buttons),
                    sol.status, "",
                    "{" + ",".join(map(str, machine.target)) + "}", "", ""
                ])
            else:
                w.writerow([
                    machine.machine_id, f"[{machine.pattern}]", machine.n, len(
                        machine.buttons),
                    sol.status, sol.total_presses,
                    "{" + ",".join(map(str, machine.target)) + "}",
                    compact_buttons_used(machine, sol.x),
                    "[" + ",".join(map(str, sol.x)) + "]"
                ])

    # Detail per used button (one row per x_j > 0)
    with open("buttons_detail.csv", "w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow([
            "machine_id", "button_index", "affects_tuple", "presses",
            "contribution_vector", "num_affected"
        ])
        for machine, sol in zip(machines, sols):
            if sol.x is None:
                continue
            x = sol.x
            n = machine.n
            for j, pj in enumerate(x):
                if pj <= 0:
                    continue
                contrib = [0] * n
                for i in machine.buttons[j]:
                    contrib[i] = pj
                w.writerow([
                    machine.machine_id,
                    j,
                    "(" + ",".join(map(str, machine.buttons[j])) + ")",
                    pj,
                    "[" + ",".join(map(str, contrib)) + "]",
                    len(machine.buttons[j])
                ])


# ----------------------------
# Main
# ----------------------------

def main():
    machines = read_input(sys.stdin)
    if not machines:
        print("No hay máquinas en la entrada.")
        return

    sols: List[Solution] = []
    total_global = 0
    infeasible_count = 0

    # Resolver
    for machine in machines:
        sol = solve_machine(machine, time_limit=8.0, workers=8)
        sols.append(sol)
        if sol.total_presses is not None:
            total_global += sol.total_presses
        else:
            if sol.status in ("INFEASIBLE", "UNKNOWN", "MODEL_INVALID"):
                infeasible_count += 1

    # Export CSV
    write_csvs(machines, sols)
    print("✅ CSV exportados: machines_summary.csv, buttons_detail.csv")

    # Export LaTeX
    with open("model.tex", "w", encoding="utf-8") as f:
        f.write(r"\documentclass{article}" + "\n")
        f.write(r"\usepackage[a4paper,margin=1.7cm]{geometry}" + "\n")
        f.write(r"\usepackage{amsmath,amssymb}" + "\n")
        f.write(r"\usepackage[T1]{fontenc}" + "\n")
        f.write(r"\usepackage{lmodern}" + "\n")
        f.write(r"\begin{document}" + "\n")
        f.write(
            r"\section*{Joltage machines — ILP/CP-SAT model + solutions}" + "\n")
        for machine, sol in zip(machines, sols):
            f.write(latex_for_machine(machine, sol) + "\n\n")
        f.write(r"\end{document}" + "\n")
    print("✅ LaTeX exportado: model.tex")

    # Consola: calculadora
    print("\n" + "=" * 60)
    print("CALCULADORA / VERIFICACIÓN")
    print("=" * 60)

    for machine, sol in zip(machines, sols):
        print("\n" + "-" * 60)
        print(
            f"Machine {machine.machine_id}  pattern=[{machine.pattern}]  n={machine.n}  m={len(machine.buttons)}")
        print(f"Targets: {machine.target}")

        if sol.x is None:
            print(
                f"Status: {sol.status} (sin solución encontrada en el tiempo / infeasible)")
            continue

        x = sol.x
        got = verify_counters(machine, x)
        ok_all = all(got[i] == machine.target[i] for i in range(machine.n))

        print(f"Status: {sol.status}")
        print(f"Total presses: {sol.total_presses}")
        print("Solution compact:", compact_buttons_used(machine, x))

        print("\nCheck por contador:")
        for i in range(machine.n):
            mark = "✓" if got[i] == machine.target[i] else "✗"
            print(f"  i={i}: {got[i]} = {machine.target[i]} {mark}")

        print("\nBotones usados (x_j>0):")
        for j, pj in enumerate(x):
            if pj > 0:
                print(f"  x{j}={pj}  afecta {tuple(machine.buttons[j])}")

        if not ok_all:
            print("⚠️  Atención: verificación NO cuadra (esto no debería pasar).")

    print("\n" + "=" * 60)
    print(f"TOTAL GLOBAL (sum presses de máquinas resueltas): {total_global}")
    if infeasible_count:
        print(f"Máquinas sin solución/unknown: {infeasible_count}")
    print("=" * 60)


if __name__ == "__main__":
    main()
