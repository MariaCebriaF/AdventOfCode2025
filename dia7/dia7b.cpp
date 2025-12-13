#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<string> mapa;
    string linea;

    while (getline(cin, linea))
    {
        if (!linea.empty())
            mapa.push_back(linea);
    }

    if (mapa.empty())
    {
        cout << 0 << "\n";
        return 0;
    }

    int filas = (int)mapa.size();
    int columnas = (int)mapa[0].size();

    int filaInicio = -1, colInicio = -1;
    for (int f = 0; f < filas; ++f)
    {
        for (int c = 0; c < columnas; ++c)
        {
            if (mapa[f][c] == 'S')
            {
                filaInicio = f;
                colInicio = c;
                break;
            }
        }
        if (filaInicio != -1)
            break;
    }

    if (filaInicio == -1)
    {
        cout << 0 << "\n";
        return 0;
    }

    vector<long long> formas(columnas, 0), siguientes(columnas, 0);
    formas[colInicio] = 1;

    long long total_lineas_temporales = 0;

    for (int f = filaInicio; f < filas; ++f)
    {
        fill(siguientes.begin(), siguientes.end(), 0);

        for (int c = 0; c < columnas; ++c)
        {
            long long w = formas[c];
            if (w == 0)
                continue;

            char celda = mapa[f][c];

            if (celda == '^')
            {

                int nc = c - 1;
                if (nc < 0)
                {
                    total_lineas_temporales += w;
                }
                else
                {
                    if (f + 1 < filas)
                        siguientes[nc] += w;
                    else
                        total_lineas_temporales += w;
                }

                nc = c + 1;
                if (nc >= columnas)
                {
                    total_lineas_temporales += w;
                }
                else
                {
                    if (f + 1 < filas)
                        siguientes[nc] += w;
                    else
                        total_lineas_temporales += w;
                }
            }
            else
            {
                if (f + 1 < filas)
                {
                    siguientes[c] += w;
                }
                else
                {
                    total_lineas_temporales += w;
                }
            }
        }

        formas.swap(siguientes);
    }

    cout << total_lineas_temporales << "\n";
    return 0;
}
