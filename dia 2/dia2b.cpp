#include <bits/stdc++.h>
using namespace std;

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
    long long maximoGlobal = 0;

    {
        size_t inicio = 0;
        while (inicio < todo.size())
        {

            size_t posComa = todo.find(',', inicio);
            if (posComa == string::npos)
                posComa = todo.size();

            string segmento = todo.substr(inicio, posComa - inicio);

            if (!segmento.empty())
            {
                size_t posGuion = segmento.find('-');
                if (posGuion != string::npos)
                {
                    long long bajo = stoll(segmento.substr(0, posGuion));
                    long long alto = stoll(segmento.substr(posGuion + 1));

                    if (bajo > alto)
                        swap(bajo, alto);

                    rangos.push_back({bajo, alto});
                    if (alto > maximoGlobal)
                        maximoGlobal = alto;
                }
            }

            inicio = posComa + 1;
        }
    }

    if (rangos.empty())
    {
        cout << 0 << "\n";
        return 0;
    }

    int maxDigitos = (int)to_string(maximoGlobal).size();

    set<long long> noValidosSet;

    for (int b = 1; b <= maxDigitos / 2; b++)
    {
        long long minA = (b == 1) ? 1 : (long long)pow(10, b - 1);
        long long maxA = (long long)pow(10, b) - 1;

        for (int r = 2; r <= maxDigitos / b; r++)
        {
            int longitudTotal = b * r;
            if (longitudTotal > maxDigitos)
                break;

            for (long long A = minA; A <= maxA; A++)
            {
                string bloque = to_string(A);
                string s;
                s.reserve(longitudTotal);

                for (int k = 0; k < r; k++)
                    s += bloque;

                if ((int)s.size() > maxDigitos)
                    break;

                long long N = stoll(s);
                if (N > maximoGlobal)
                    break;

                noValidosSet.insert(N);
            }
        }
    }

    vector<long long> noValidos(noValidosSet.begin(), noValidosSet.end());
    sort(noValidos.begin(), noValidos.end());

    long long respuesta = 0;

    for (int i = 0; i < (int)rangos.size(); i++)
    {
        long long bajo = rangos[i].first;
        long long alto = rangos[i].second;

        auto it = lower_bound(noValidos.begin(), noValidos.end(), bajo);
        while (it != noValidos.end() && *it <= alto)
        {
            respuesta += *it;
            ++it;
        }
    }

    cout << respuesta << "\n";
    return 0;
}
