#include <bits/stdc++.h>
using namespace std;

int main()
{

    string linea;
    long long total = 0;

    while (getline(cin, linea))
    {

        if (linea.empty())
            continue;

        int n = (int)linea.size();
        if (n < 2)
            continue;

        vector<int> digitos(n);
        for (int i = 0; i < n; ++i)
        {
            digitos[i] = linea[i] - '0';
        }

        vector<int> sufijo_max(n, -1);
        int mejor = -1;
        for (int i = n - 1; i >= 0; --i)
        {
            sufijo_max[i] = mejor;
            mejor = max(mejor, digitos[i]);
        }

        int mejor_banco = 0;

        for (int i = 0; i < n - 1; ++i)
        {
            if (sufijo_max[i] == -1)
                continue;
            int valor = digitos[i] * 10 + sufijo_max[i];
            if (valor > mejor_banco)
            {
                mejor_banco = valor;
            }
        }

        total += mejor_banco;
    }

    cout << total << "\n";
    return 0;
}
