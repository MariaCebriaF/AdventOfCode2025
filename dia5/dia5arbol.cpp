#include <bits/stdc++.h>
using namespace std;

struct Nodo
{
    long long inicio, fin;
    Nodo *izquierdo;
    Nodo *derecho;

    Nodo(long long i, long long f)
        : inicio(i), fin(f), izquierdo(nullptr), derecho(nullptr) {}
};

Nodo *construirArbol(const vector<pair<long long, long long>> &v, int izquierda, int derecha)
{
    if (izquierda > derecha)
        return nullptr;
    int medio = (izquierda + derecha) / 2;

    Nodo *raiz = new Nodo(v[medio].first, v[medio].second);
    raiz->izquierdo = construirArbol(v, izquierda, medio - 1);
    raiz->derecho = construirArbol(v, medio + 1, derecha);

    return raiz;
}

bool esFresco(Nodo *raiz, long long id)
{
    if (!raiz)
        return false;

    if (id < raiz->inicio)
        return esFresco(raiz->izquierdo, id);
    else if (id > raiz->fin)
        return esFresco(raiz->derecho, id);
    else
        return true;
}

int main()
{

    vector<pair<long long, long long>> rangos;
    string linea;

    while (getline(cin, linea))
    {
        if (linea.empty())
            break;
        long long a, b;
        char guion;
        stringstream ss(linea);
        ss >> a >> guion >> b;
        rangos.push_back({a, b});
    }

    sort(rangos.begin(), rangos.end());
    vector<pair<long long, long long>> fusionados;

    for (auto [ini, fin] : rangos)
    {
        if (fusionados.empty() || ini > fusionados.back().second)
        {
            fusionados.push_back({ini, fin});
        }
        else
        {
            fusionados.back().second = max(fusionados.back().second, fin);
        }
    }

    Nodo *raiz = nullptr;
    if (!fusionados.empty())
    {
        raiz = construirArbol(fusionados, 0, fusionados.size() - 1);
    }

    long long id;
    int frescos = 0;

    while (cin >> id)
    {
        if (esFresco(raiz, id))
        {
            frescos++;
        }
    }

    cout << frescos << "\n";
}
