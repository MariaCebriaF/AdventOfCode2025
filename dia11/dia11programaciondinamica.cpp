#include <bits/stdc++.h>
using namespace std;

long long caminos(int u, int objetivo, const vector<vector<int>> &ady, vector<long long> &memo)
{
    if (u < 0 || u >= (int)ady.size())
    return INT_MAX;

    if (memo[u] != -1)
        return memo[u];

    if (u == objetivo)
        return 1;

    long long total = 0;

    for (int v : ady[u])
    {
        total += caminos(v, objetivo, ady, memo);
    }

    memo[u] = total;
    return total;
}

int main()
{

    unordered_map<string, int> id;
    vector<vector<int>> ady;

    auto ID = [&](const string &nombre) -> int
    {
        auto it = id.find(nombre);
        if (it != id.end())
            return it->second;

        int nuevoID = id.size();
        id[nombre] = nuevoID;
        ady.push_back(vector<int>());
        return nuevoID;
    };

    string linea;
    while (getline(cin, linea))
    {
        if (linea.empty())
            continue;

        stringstream ss(linea);

        string origen;
        ss >> origen;

        if (!origen.empty() && origen.back() == ':')
            origen.pop_back();

        int id_origen = ID(origen);

        string destino;
        while (ss >> destino)
        {
            int id_destino = ID(destino);
            ady[id_origen].push_back(id_destino);
        }
    }

    int origen = id["you"];
    int objetivo = id["out"];

    vector<long long> memo(ady.size(), -1);

    long long resultado = caminos(origen, objetivo, ady, memo);

    cout << resultado << "\n";

    return 0;
}