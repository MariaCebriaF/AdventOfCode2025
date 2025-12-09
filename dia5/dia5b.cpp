#include <bits/stdc++.h>
using namespace std;

vector<pair<long long, long long>> fusionar_rangos(vector<pair<long long, long long>> rangos)
{
    if (rangos.empty())
        return {};

    sort(rangos.begin(), rangos.end());

    vector<pair<long long, long long>> res;
    long long cur_start = rangos[0].first;
    long long cur_end = rangos[0].second;

    for (size_t i = 1; i < rangos.size(); ++i)
    {
        auto [s, e] = rangos[i];
        if (s <= cur_end + 1)
        {

            cur_end = max(cur_end, e);
        }
        else
        {

            res.emplace_back(cur_start, cur_end);
            cur_start = s;
            cur_end = e;
        }
    }

    res.emplace_back(cur_start, cur_end);
    return res;
}

int main()
{

    vector<pair<long long, long long>> rangos;

    string linea;
    bool fin_rangos = false;

    while (getline(cin, linea))
    {
        if (linea.empty())
        {
            fin_rangos = true;
            break;
        }
        size_t guion = linea.find('-');
        if (guion == string::npos)
            continue;

        long long a = stoll(linea.substr(0, guion));
        long long b = stoll(linea.substr(guion + 1));
        if (a > b)
            swap(a, b);
        rangos.emplace_back(a, b);
    }

    auto fusionados = fusionar_rangos(rangos);

    long long total_frescos = 0;
    for (auto [L, R] : fusionados)
    {
        total_frescos += (R - L + 1);
    }

    cout << total_frescos << "\n";
    return 0;
}
