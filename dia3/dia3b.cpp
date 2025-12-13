#include <bits/stdc++.h>
using namespace std;

int main()
{

    const int K = 12;
    long long total = 0;

    string linea;
    while (getline(cin, linea))
    {
        if (linea.empty())
            continue;

        string s;
        for (char c : linea)
        {
            if (isdigit(static_cast<unsigned char>(c)))
            {
                s.push_back(c);
            }
        }
        if ((int)s.size() < K)
        {

            continue;
        }

        int n = (int)s.size();
        int borrar = n - K;

        string pila;
        pila.reserve(n);

        for (char c : s)
        {
            while (borrar > 0 && !pila.empty() && pila.back() < c)
            {
                pila.pop_back();
                --borrar;
            }
            pila.push_back(c);
        }

        while (borrar > 0)
        {
            pila.pop_back();
            --borrar;
        }

        long long valor_banco = 0;
        for (char c : pila)
        {
            valor_banco = valor_banco * 10 + (c - '0');
        }
        total += valor_banco;
    }

    cout << total << "\n";
    return 0;
}
