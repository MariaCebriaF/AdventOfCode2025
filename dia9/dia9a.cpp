#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<pair<long long, long long>> rojas;
    string linea;

    while (getline(cin, linea))
    {
        if (linea.empty())
            continue;

        long long x, y;
        char coma;
        stringstream ss(linea);

        if (!(ss >> x >> coma >> y))
        {
            continue;
        }

        rojas.push_back({x, y});
    }

    int n = (int)rojas.size();
    if (n < 2)
    {

        cout << 0 << "\n";
        return 0;
    }

    long long mejor_area = 0;

    for (int i = 0; i < n; i++)
    {
        long long x1 = rojas[i].first;
        long long y1 = rojas[i].second;

        for (int j = i + 1; j < n; j++)
        {
            long long x2 = rojas[j].first;
            long long y2 = rojas[j].second;

            long long anchura = llabs(x1 - x2) + 1;
            long long altura = llabs(y1 - y2) + 1;
            long long area = anchura * altura;

            if (area > mejor_area)
                mejor_area = area;
        }
    }

    cout << mejor_area << "\n";
    return 0;
}
