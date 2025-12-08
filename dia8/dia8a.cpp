#include <bits/stdc++.h>
using namespace std;

struct UF
{
    int n;
    vector<int> padre, tam;

    UF(int n) : n(n), padre(n), tam(n, 1)
    {
        iota(padre.begin(), padre.end(), 0);
    }

    int encontrar(int x)
    {
        if (padre[x] == x)
            return x;
        return padre[x] = encontrar(padre[x]);
    }

    bool unir(int a, int b)
    {
        a = encontrar(a);
        b = encontrar(b);
        if (a == b)
            return false;

        if (tam[a] < tam[b])
            swap(a, b);

        padre[b] = a;
        tam[a] += tam[b];
        return true;
    }

    int tamano(int x)
    {
        return tam[encontrar(x)];
    }
};

struct Arista
{
    long long dist2;
    int a, b;
};

int main()
{
    vector<array<long long, 3>> puntos;
    string linea;

    while (getline(cin, linea))
    {
        if (linea.empty())
            continue;

        long long x, y, z;
        char c1, c2;
        stringstream ss(linea);
        if (!(ss >> x >> c1 >> y >> c2 >> z))
            continue;

        puntos.push_back({x, y, z});
    }

    int n = (int)puntos.size();
    if (n == 0)
    {
        cout << 0 << "\n";
        return 0;
    }

    vector<Arista> aristas;
    aristas.reserve(1LL * n * (n - 1) / 2);

    for (int i = 0; i < n; ++i)
    {
        long long xi = puntos[i][0];
        long long yi = puntos[i][1];
        long long zi = puntos[i][2];

        for (int j = i + 1; j < n; ++j)
        {
            long long xj = puntos[j][0];
            long long yj = puntos[j][1];
            long long zj = puntos[j][2];

            long long dx = xi - xj;
            long long dy = yi - yj;
            long long dz = zi - zj;
            long long dist2 = dx * dx + dy * dy + dz * dz;

            aristas.push_back({dist2, i, j});
        }
    }

    // Ordenar aristas por distancia
    sort(aristas.begin(), aristas.end(),
         [](const Arista &a1, const Arista &a2)
         {
             if (a1.dist2 != a2.dist2)
                 return a1.dist2 < a2.dist2;
             if (a1.a != a2.a)
                 return a1.a < a2.a;
             return a1.b < a2.b;
         });

    UF uf(n);

    const int LIMITE = 1000;
    int hasta = min((int)aristas.size(), LIMITE);

    for (int i = 0; i < hasta; ++i)
    {
        int a = aristas[i].a;
        int b = aristas[i].b;
        uf.unir(a, b);
    }

    vector<int> tamComp(n, 0);
    for (int i = 0; i < n; ++i)
    {
        int raiz = uf.encontrar(i);
        tamComp[raiz]++;
    }

    vector<int> tamanos;
    for (int i = 0; i < n; ++i)
    {
        if (tamComp[i] > 0)
            tamanos.push_back(tamComp[i]);
    }

    if ((int)tamanos.size() < 3)
    {
        long long res = 1;
        for (int i = 0; i < (int)tamanos.size(); i++)
            res *= tamanos[i];

        cout << res << "\n";
        return 0;
    }

    sort(tamanos.begin(), tamanos.end(), greater<int>());

    long long respuesta = 1LL * tamanos[0] * tamanos[1] * tamanos[2];

    cout << respuesta << "\n";
    return 0;
}
