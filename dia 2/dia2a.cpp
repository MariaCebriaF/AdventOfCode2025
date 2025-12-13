#include <bits/stdc++.h>
using namespace std;

long long redondear_arriba(long long a, long long b)
{
    return (a + b - 1) / b;
}

int main()
{
    string todo;
    string linea;

    while (getline(cin, linea))
    {
        for (int i = 0; i < (int)linea.size(); i++)
        {
            char c = linea[i];
            if (!isspace(static_cast<unsigned char>(c)))
            {
                todo.push_back(c);
            }
        }
    }

    if (todo.empty())
    {
        cout << 0 << "\n";
        return 0;
    }

    vector<pair<long long, long long>> rangos;
    long long maximo_global = 0;

    {
        size_t inicio = 0;
        while (inicio < todo.size())
        {
            size_t pos_coma = todo.find(',', inicio);
            if (pos_coma == string::npos)
                pos_coma = todo.size();

            string segmento = todo.substr(inicio, pos_coma - inicio);

            if (!segmento.empty())
            {
                size_t pos_guion = segmento.find('-');
                if (pos_guion != string::npos)
                {
                    long long bajo = stoll(segmento.substr(0, pos_guion));
                    long long alto = stoll(segmento.substr(pos_guion + 1));
                    if (bajo > alto)
                        swap(bajo, alto);

                    rangos.push_back({bajo, alto});
                    if (alto > maximo_global)
                        maximo_global = alto;
                }
            }

            inicio = pos_coma + 1;
        }
    }

    if (rangos.empty())
    {
        cout << 0 << "\n";
        return 0;
    }

    const int MAX_POT = 18;
    long long pot10[MAX_POT + 1];
    pot10[0] = 1;
    for (int i = 1; i <= MAX_POT; i++)
    {
        pot10[i] = pot10[i - 1] * 10LL;
    }

    long long solucion = 0;

    for (int idx = 0; idx < (int)rangos.size(); idx++)
    {
        long long lo = rangos[idx].first;
        long long hi = rangos[idx].second;

        if (hi <= 0)
            continue;

        long long suma_local = 0;
        int max_digitos = (int)to_string(hi).size();

        for (int L = 2; L <= max_digitos; L += 2)
        {
            int mitad = L / 2;

            if (mitad >= MAX_POT)
                break;

            long long B = pot10[mitad];
            long long minA = (mitad == 1) ? 1 : pot10[mitad - 1];
            long long maxA = B - 1;

            __int128 minN128 = (__int128)minA * (__int128)(B + 1);
            long long minN;

            if (minN128 > (__int128)LLONG_MAX)
            {
                break;
            }
            else
            {
                minN = (long long)minN128;
            }

            if (minN > hi)
            {
                break;
            }

            long long denom = B + 1;

            long long loA1 = redondear_arriba(lo, denom);
            long long hiA1 = hi / denom;

            long long A_bajo = max(minA, loA1);
            long long A_alto = min(maxA, hiA1);

            if (A_bajo > A_alto)
                continue;

            long long cantidadA = A_alto - A_bajo + 1;

            __int128 sumaA = (__int128)(A_bajo + A_alto) * (__int128)cantidadA;
            sumaA /= 2;

            __int128 sumaN = sumaA * (__int128)denom;

            suma_local += (long long)sumaN;
        }

        solucion += suma_local;
    }

    cout << solucion << "\n";
    return 0;
}
