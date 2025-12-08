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

    vector<bool> actual(columnas, false), siguiente(columnas, false);
    actual[colInicio] = true;

    long long divisiones = 0;

    for (int f = filaInicio; f < filas; ++f)
    {
        fill(siguiente.begin(), siguiente.end(), false);

        for (int c = 0; c < columnas; ++c)
        {
            if (!actual[c])
                continue;

            char celda = mapa[f][c];

            if (celda == '^')
            {
                divisiones++;

                if (c - 1 >= 0 && f + 1 < filas)
                    siguiente[c - 1] = true;

                if (c + 1 < columnas && f + 1 < filas)
                    siguiente[c + 1] = true;
            }
            else
            {
                if (f + 1 < filas)
                    siguiente[c] = true;
            }
        }

        actual.swap(siguiente);
    }

    cout << divisiones << "\n";
    return 0;
}
