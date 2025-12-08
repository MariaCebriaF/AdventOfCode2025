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

    // Leer puntos con formato: x,y,z
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

    // Generar todas las aristas posibles (completo)
    vector<Arista> aristas;
    aristas.reserve(1LL * n * (n - 1) / 2);

    for (int i = 0; i < n; ++i)
    {
        auto [xi, yi, zi] = puntos[i];
        for (int j = i + 1; j < n; ++j)
        {
            auto [xj, yj, zj] = puntos[j];

            long long dx = xi - xj;
            long long dy = yi - yj;
            long long dz = zi - zj;
            long long dist2 = dx * dx + dy * dy + dz * dz;

            aristas.push_back({dist2, i, j});
        }
    }

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
    int componentes = n;
    long long respuesta = 0;

    for (int i = 0; i < (int)aristas.size(); i++)
    {
        const Arista &ar = aristas[i];

        int a = ar.a;
        int b = ar.b;

        int ra = uf.encontrar(a);
        int rb = uf.encontrar(b);

        if (ra == rb)
            continue;

        if (componentes == 2)
        {
            long long xa = puntos[a][0];
            long long xb = puntos[b][0];
            respuesta = xa * xb;
            uf.unir(a, b);
            componentes--;
            break;
        }
        else
        {
            uf.unir(a, b);
            componentes--;
        }
    }

    cout << respuesta << "\n";
    return 0;
}
