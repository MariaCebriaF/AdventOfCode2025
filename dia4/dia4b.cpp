#include <bits/stdc++.h>
using namespace std;

int main()
{

    vector<string> grid;
    string linea;

    while (getline(cin, linea))
    {
        if (!linea.empty())
        {
            grid.push_back(linea);
        }
    }

    if (grid.empty())
    {
        cout << 0 << "\n";
        return 0;
    }

    int filas = (int)grid.size();
    int columnas = (int)grid[0].size();

    const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    long long total_eliminados = 0;

    while (true)
    {
        vector<pair<int, int>> a_eliminar;

        for (int i = 0; i < filas; ++i)
        {
            for (int j = 0; j < columnas; ++j)
            {
                if (grid[i][j] != '@')
                    continue;

                int vecinos = 0;

                for (int k = 0; k < 8; ++k)
                {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (ni < 0 || ni >= filas || nj < 0 || nj >= columnas)
                        continue;
                    if (grid[ni][nj] == '@')
                    {
                        vecinos++;
                    }
                }

                if (vecinos < 4)
                {
                    a_eliminar.emplace_back(i, j);
                }
            }
        }

        if (a_eliminar.empty())
        {
            break;
        }

        for (auto [i, j] : a_eliminar)
        {
            grid[i][j] = '.';
        }

        total_eliminados += (long long)a_eliminar.size();
    }

    cout << total_eliminados << "\n";
    return 0;
}
