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

bool es_fresco(long long id, const vector<pair<long long, long long>> &rangos)
{
    if (rangos.empty())
        return false;

    auto it = upper_bound(
        rangos.begin(), rangos.end(),
        make_pair(id, LLONG_MAX),
        [](const pair<long long, long long> &val, const pair<long long, long long> &elem)
        {
            return val.first < elem.first;
        });

    if (it == rangos.begin())
    {

        return false;
    }

    --it;
    long long start = it->first;
    long long end = it->second;
    return (start <= id && id <= end);
}

int main()
{

    vector<pair<long long, long long>> rangos;
    vector<long long> ids;

    string linea;
    bool leyendo_ids = false;

    while (getline(cin, linea))
    {
        if (linea.empty())
        {

            leyendo_ids = true;
            continue;
        }

        if (!leyendo_ids)
        {

            size_t guion = linea.find('-');
            if (guion == string::npos)
                continue;

            long long a = stoll(linea.substr(0, guion));
            long long b = stoll(linea.substr(guion + 1));
            if (a > b)
                swap(a, b);
            rangos.emplace_back(a, b);
        }
        else
        {

            long long id = stoll(linea);
            ids.push_back(id);
        }
    }

    auto rangos_fusionados = fusionar_rangos(rangos);

    long long contador_frescos = 0;
    for (long long id : ids)
    {
        if (es_fresco(id, rangos_fusionados))
        {
            contador_frescos++;
        }
    }

    cout << contador_frescos << "\n";
    return 0;
}
