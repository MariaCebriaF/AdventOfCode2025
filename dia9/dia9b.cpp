#include <bits/stdc++.h>
using namespace std;

struct Punto
{
    long long x, y;
};

bool puntoEnSegmento(double px, double py,
                     long long x1, long long y1,
                     long long x2, long long y2)
{
    const double EPS = 1e-9;

    double vx = x2 - x1;
    double vy = y2 - y1;
    double wx = px - x1;
    double wy = py - y1;

    double cruz = vx * wy - vy * wx;
    if (fabs(cruz) > EPS)
        return false;

    double minx = min(x1, x2) - EPS;
    double maxx = max(x1, x2) + EPS;
    double miny = min(y1, y2) - EPS;
    double maxy = max(y1, y2) + EPS;

    return (px >= minx && px <= maxx && py >= miny && py <= maxy);
}

bool puntoDentroOPerimetro(double px, double py, const vector<Punto> &poligono)
{
    int n = (int)poligono.size();

    for (int i = 0; i < n; ++i)
    {
        long long x1 = poligono[i].x;
        long long y1 = poligono[i].y;
        long long x2 = poligono[(i + 1) % n].x;
        long long y2 = poligono[(i + 1) % n].y;
        if (puntoEnSegmento(px, py, x1, y1, x2, y2))
            return true;
    }

    bool dentro = false;
    for (int i = 0, j = n - 1; i < n; j = i++)
    {
        double xi = (double)poligono[i].x;
        double yi = (double)poligono[i].y;
        double xj = (double)poligono[j].x;
        double yj = (double)poligono[j].y;

        bool intersecta = ((yi > py) != (yj > py));
        if (intersecta)
        {
            double x_inter = xj + (xi - xj) * (py - yj) / (yi - yj);
            if (x_inter > px)
                dentro = !dentro;
        }
    }

    return dentro;
}

int main()
{

    vector<Punto> poligono;
    string linea;

    while (getline(cin, linea))
    {
        if (linea.empty())
            continue;
        long long x, y;
        char coma;
        stringstream ss(linea);
        if (!(ss >> x >> coma >> y))
            continue;
        poligono.push_back({x, y});
    }

    int n = (int)poligono.size();
    if (n < 4)
    {
        cout << 0 << "\n";
        return 0;
    }

    long long mejorArea = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            long long x1 = poligono[i].x;
            long long y1 = poligono[i].y;
            long long x2 = poligono[j].x;
            long long y2 = poligono[j].y;

            if (x1 == x2 || y1 == y2)
                continue;

            long long xIzq = min(x1, x2);
            long long xDer = max(x1, x2);
            long long yAbajo = min(y1, y2);
            long long yArriba = max(y1, y2);

            long long ancho = xDer - xIzq + 1;
            long long alto = yArriba - yAbajo + 1;
            long long area = ancho * alto;

            if (area <= mejorArea)
                continue;

            double esquinasX[4] = {(double)xIzq, (double)xIzq, (double)xDer, (double)xDer};
            double esquinasY[4] = {(double)yAbajo, (double)yArriba, (double)yAbajo, (double)yArriba};

            bool valido = true;
            for (int k = 0; k < 4; ++k)
            {
                if (!puntoDentroOPerimetro(esquinasX[k], esquinasY[k], poligono))
                {
                    valido = false;
                    break;
                }
            }
            if (!valido)
                continue;

            for (int k = 0; k < n && valido; ++k)
            {
                long long xA = poligono[k].x;
                long long yA = poligono[k].y;
                long long xB = poligono[(k + 1) % n].x;
                long long yB2 = poligono[(k + 1) % n].y;

                if (yA == yB2)
                {
                    long long y = yA;
                    if (y > yAbajo && y < yArriba)
                    {
                        long long ax = min(xA, xB);
                        long long bx = max(xA, xB);
                        if (max(ax, xIzq) < min(bx, xDer))
                            valido = false;
                    }
                }

                else if (xA == xB)
                {
                    long long x = xA;
                    if (x > xIzq && x < xDer)
                    {
                        long long ay = min(yA, yB2);
                        long long by = max(yA, yB2);
                        if (max(ay, yAbajo) < min(by, yArriba))
                            valido = false;
                    }
                }
            }

            if (!valido)
                continue;

            mejorArea = area;
        }
    }

    cout << mejorArea << "\n";
    return 0;
}
