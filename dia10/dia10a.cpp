#include <bits/stdc++.h>
using namespace std;

int solve_machine(const string &line)
{
    // 1) Extraer patrón entre [ ]
    size_t lbr = line.find('[');
    size_t rbr = line.find(']', lbr);
    if (lbr == string::npos || rbr == string::npos)
        return 0; // por seguridad

    string pattern = line.substr(lbr + 1, rbr - lbr - 1);
    int n = (int)pattern.size();

    // Construir bitmask objetivo
    // bit 0 = primera luz (posición 0 del patrón)
    unsigned int target = 0;
    for (int i = 0; i < n; ++i)
    {
        if (pattern[i] == '#')
        {
            target |= (1u << i);
        }
    }

    // 2) Extraer botones ( ... ) hasta llegar a '{'
    vector<unsigned int> buttons;
    size_t i = rbr + 1;
    while (i < line.size() && line[i] != '{')
    {
        if (line[i] == '(')
        {
            size_t j = i + 1;
            unsigned int mask = 0;
            int cur = 0;
            bool inNum = false;

            while (j < line.size() && line[j] != ')')
            {
                if (isdigit((unsigned char)line[j]))
                {
                    inNum = true;
                    cur = cur * 10 + (line[j] - '0');
                }
                else if (line[j] == ',' || isspace((unsigned char)line[j]))
                {
                    if (inNum)
                    {
                        mask |= (1u << cur);
                        cur = 0;
                        inNum = false;
                    }
                }
                ++j;
            }
            // último número antes del ')'
            if (inNum)
            {
                mask |= (1u << cur);
            }

            buttons.push_back(mask);
            i = (j == string::npos ? line.size() : j + 1);
        }
        else
        {
            ++i;
        }
    }

    // 3) BFS en el espacio de estados de tamaño 2^n
    // (suponemos n <= 20-24 aprox para que sea manejable en AoC)
    int maxStates = 1 << n;
    vector<int> dist(maxStates, -1);
    queue<unsigned int> q;

    dist[0] = 0;
    q.push(0u);

    while (!q.empty())
    {
        unsigned int s = q.front();
        q.pop();

        if (s == target)
        {
            return dist[s];
        }

        for (unsigned int bmask : buttons)
        {
            unsigned int ns = s ^ bmask;
            if (dist[ns] == -1)
            {
                dist[ns] = dist[s] + 1;
                q.push(ns);
            }
        }
    }

    // Si no hay solución, podrías devolver -1 o lanzar error.
    // En el puzzle real normalmente siempre hay solución.
    return -1;
}

int main()
{

    string line;
    long long total_presses = 0;

    while (getline(cin, line))
    {
        if (line.empty())
            continue;
        int presses = solve_machine(line);
        if (presses == -1)
        {
            cerr << "No se ha encontrado solución para esta máquina:\n"
                 << line << "\n";
            return 1;
        }
        total_presses += presses;
    }

    cout << total_presses << "\n";
    return 0;
}
