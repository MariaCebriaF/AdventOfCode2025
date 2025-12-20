#include <bits/stdc++.h>
using namespace std;

class ConjuntoHash
{
private:
    vector<int> claves;
    vector<unsigned char> estado;
    int capacidad;
    int tamanio;
    unsigned long long semilla;

    int hashEntero(int x) const
    {
        unsigned long long z = (unsigned long long)(unsigned int)x;
        z ^= semilla;
        z *= 0xBF58476D1CE4E5B9ULL;
        z ^= z >> 27;
        z *= 0x94D049BB133111EBULL;
        z ^= z >> 31;
        return (int)(z & (capacidad - 1));
    }

    void rehash(int nuevaCapacidad)
    {
        vector<int> viejasClaves = claves;
        vector<unsigned char> viejosEstado = estado;

        capacidad = 1;
        while (capacidad < nuevaCapacidad)
            capacidad <<= 1;

        claves.assign(capacidad, 0);
        estado.assign(capacidad, 0);
        tamanio = 0;

        for (int i = 0; i < (int)viejasClaves.size(); ++i)
        {
            if (viejosEstado[i] == 1)
                insertar(viejasClaves[i]);
        }
    }

    void asegurarCapacidad()
    {
        if ((tamanio + 1) * 10 >= capacidad * 7)
            rehash(capacidad << 1);
    }

public:
    ConjuntoHash(int cap = 8)
    {
        capacidad = 1;
        while (capacidad < cap)
            capacidad <<= 1;

        claves.assign(capacidad, 0);
        estado.assign(capacidad, 0);
        tamanio = 0;
        semilla = 0x9E3779B97F4A7C15ULL;
    }

    void insertar(int x)
    {
        asegurarCapacidad();

        int i = hashEntero(x);
        while (estado[i] == 1)
        {
            if (claves[i] == x)
                return;
            i = (i + 1) & (capacidad - 1);
        }

        claves[i] = x;
        estado[i] = 1;
        tamanio++;
    }

    bool contiene(int x) const
    {
        int i = hashEntero(x);
        while (estado[i] != 0)
        {
            if (estado[i] == 1 && claves[i] == x)
                return true;
            i = (i + 1) & (capacidad - 1);
        }
        return false;
    }

    void limpiar()
    {
        fill(estado.begin(), estado.end(), 0);
        tamanio = 0;
    }

    bool vacio() const
    {
        return tamanio == 0;
    }

    void intercambiar(ConjuntoHash &otro)
    {
        swap(claves, otro.claves);
        swap(estado, otro.estado);
        swap(capacidad, otro.capacidad);
        swap(tamanio, otro.tamanio);
        swap(semilla, otro.semilla);
    }

    int obtenerCapacidad() const
    {
        return capacidad;
    }

    int obtenerClaveEn(int i) const
    {
        return claves[i];
    }

    unsigned char obtenerEstadoEn(int i) const
    {
        return estado[i];
    }
};

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
    for (int f = 0; f < filas && filaInicio == -1; ++f)
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
    }

    if (filaInicio == -1)
    {
        cout << 0 << "\n";
        return 0;
    }

    ConjuntoHash actual(16), siguiente(16);
    actual.insertar(colInicio);

    long long divisiones = 0;

    for (int f = filaInicio; f < filas; ++f)
    {
        siguiente.limpiar();

        for (int i = 0; i < actual.obtenerCapacidad(); ++i)
        {
            if (actual.obtenerEstadoEn(i) != 1)
                continue;

            int c = actual.obtenerClaveEn(i);
            char celda = mapa[f][c];

            if (celda == '^')
            {
                divisiones++;
                if (f + 1 < filas)
                {
                    if (c - 1 >= 0)
                        siguiente.insertar(c - 1);
                    if (c + 1 < columnas)
                        siguiente.insertar(c + 1);
                }
            }
            else
            {
                if (f + 1 < filas)
                    siguiente.insertar(c);
            }
        }

        actual.intercambiar(siguiente);

        if (actual.vacio())
            break;
    }

    cout << divisiones << "\n";
    return 0;
}
