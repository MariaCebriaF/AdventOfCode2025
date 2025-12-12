#include <bits/stdc++.h>
using namespace std;

long long caminos(int u, int estado, int objetivo, int id_dac, int id_fft, const vector<vector<int>> &ady, vector<array<long long, 4>> &memo)
{

    if (u == objetivo)
    {
        return (estado == 3) ? 1LL : 0LL;
    }

    long long &res = memo[u][estado];
    if (res != -1)
        return res;

    res = 0;

    for (int v : ady[u])
    {
        int nuevo_estado = estado;

        if (v == id_dac)
            nuevo_estado |= 1;
        if (v == id_fft)
            nuevo_estado |= 2;

        res += caminos(v, nuevo_estado, objetivo, id_dac, id_fft, ady, memo);
    }

    return res;
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
        int nuevoID = (int)id.size();
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

    int id_svr = id["svr"];
    int id_out = id["out"];
    int id_dac = id["dac"];
    int id_fft = id["fft"];

    vector<array<long long, 4>> memo(ady.size());
    for (auto &arr : memo)
        arr.fill(-1);

    int estado_inicial = 0;
    if (id_svr == id_dac)
        estado_inicial |= 1;
    if (id_svr == id_fft)
        estado_inicial |= 2;

    long long resultado = caminos(id_svr, estado_inicial, id_out, id_dac, id_fft, ady, memo);

    cout << resultado << "\n";
    return 0;
}
