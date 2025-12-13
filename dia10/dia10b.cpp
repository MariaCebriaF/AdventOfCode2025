#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <numeric>

#include "ortools/sat/cp_model.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

using namespace operations_research;
using namespace operations_research::sat;

struct Machine {
    vector<vector<int>> buttons;  // buttons[j] = índices de contadores que incrementa el botón j
    vector<int> target;           // target[i]   = joltios objetivo del contador i
};

// --- Parser de una línea del input ---
Machine ParseLine(const string& line_raw) {
    string line = line_raw;
    Machine M;

    if (line.empty()) return M;

    // Buscamos el primer ']' para saltarnos el diagrama de luces
    std::size_t pos = line.find(']');
    if (pos == string::npos) {
        return M; // línea rara; volverá con target vacío
    }
    string rest = line.substr(pos + 1);

    // 1) Botones: todas las apariciones de "(...)"
    {
        std::regex re_btn(R"(\(([^)]*)\))");
        auto it  = std::sregex_iterator(rest.begin(), rest.end(), re_btn);
        auto end = std::sregex_iterator();
        for (; it != end; ++it) {
            string inside = (*it)[1].str();
            std::stringstream ss(inside);
            string tok;
            vector<int> indices;
            while (std::getline(ss, tok, ',')) {
                if (!tok.empty()) {
                    indices.push_back(std::stoi(tok));
                }
            }
            // IMPORTANTE: los últimos paréntesis son los de los joltios? No, van en llaves.
            // Así que todos los () encontrados son botones.
            M.buttons.push_back(std::move(indices));
        }
    }

    // 2) Target: último bloque "{...}"
    {
        std::regex re_curly(R"(\{([^}]*)\})");
        auto it  = std::sregex_iterator(rest.begin(), rest.end(), re_curly);
        auto end = std::sregex_iterator();
        if (it == end) {
            return M; // sin joltios
        }
        auto last = it;
        for (; it != end; ++it) last = it; // nos quedamos con el último { }

        string inside = (*last)[1].str();
        std::stringstream ss(inside);
        string tok;
        while (std::getline(ss, tok, ',')) {
            if (!tok.empty()) {
                M.target.push_back(std::stoi(tok));
            }
        }
    }

    return M;
}

// --- Resuelve una máquina con CP-SAT ---
long long SolveMachine(const Machine& M) {
    const int m = static_cast<int>(M.target.size());
    const int k = static_cast<int>(M.buttons.size());

    if (m == 0 || k == 0) return 0;

    // Comprobación rápida: si algún contador tiene target>0 y ningún botón lo toca → imposible
    vector<bool> touches(m, false);
    for (int j = 0; j < k; ++j) {
        for (int idx : M.buttons[j]) {
            if (idx >= 0 && idx < m) touches[idx] = true;
        }
    }
    for (int i = 0; i < m; ++i) {
        if (M.target[i] > 0 && !touches[i]) {
            cerr << "Contador " << i << " inalcanzable en una máquina.\n";
            throw std::runtime_error("Máquina sin solución");
        }
    }

    // Modelo CP-SAT
    CpModelBuilder cp_model;

    long long sum_targets = 0;
    for (int v : M.target) sum_targets += v;
    if (sum_targets < 0) sum_targets = 0;

    // Variables x_j: nº de veces que pulsamos el botón j
    vector<IntVar> x;
    x.reserve(k);
    for (int j = 0; j < k; ++j) {
        Domain dom(0, sum_targets); // cota superior muy holgada
        x.push_back(cp_model.NewIntVar(dom).WithName("x_" + std::to_string(j)));
    }

    // Restricciones: para cada contador i, sum(x_j) = target[i] sobre los botones que lo tocan
    for (int i = 0; i < m; ++i) {
        vector<IntVar> vars;
        for (int j = 0; j < k; ++j) {
            // ¿el botón j incrementa el contador i?
            const auto& btn = M.buttons[j];
            if (std::find(btn.begin(), btn.end(), i) != btn.end()) {
                vars.push_back(x[j]);
            }
        }
        if (!vars.empty()) {
            LinearExpr expr;
            for (const auto& v : vars) expr += v;
            cp_model.AddEquality(expr, M.target[i]);
        } else {
            // si ningún botón toca este contador, ya hemos comprobado arriba que target[i] == 0
        }
    }

    // Objetivo: minimizar total de pulsaciones
    {
        LinearExpr total;
        for (const auto& v : x) total += v;
        cp_model.Minimize(total);
    }

    // Resolver
    Model model;
    const CpSolverResponse response = Solve(cp_model.Build(), &model);

    if (response.status() != CpSolverStatus::OPTIMAL &&
        response.status() != CpSolverStatus::FEASIBLE) {
        cerr << "CP-SAT no encontró solución para una máquina.\n";
        throw std::runtime_error("Solver sin solución");
    }

    long long presses = 0;
    for (const auto& v : x) {
        presses += SolutionIntegerValue(response, v);
    }
    return presses;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    long long total = 0;

    while (std::getline(cin, line)) {
        if (line.empty()) continue;
        Machine M = ParseLine(line);
        if (M.target.empty()) continue; // línea rara / vacía

        long long best = SolveMachine(M);
        total += best;
    }

    cout << total << '\n';
    return 0;
}
