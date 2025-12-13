#include <bits/stdc++.h>
using namespace std;

long long cerosderecha(int pos, long long d)
{
    int k0;
    if (pos == 0)
        k0 = 100;
    else
        k0 = 100 - pos;

    if (d < k0)
        return 0;
    return 1 + ((d - k0) / 100);
}

long long cerosizquierda(int pos, long long d)
{
    int k0;
    if (pos == 0)
        k0 = 100;
    else
        k0 = pos;

    if (d < k0)
        return 0;
    return 1 + ((d - k0) / 100);
}

int main()
{
    cin.tie(nullptr);

    int pos = 50;
    long long total = 0;

    string line;
    while (cin >> line)
    {
        char dir = line[0];
        long long dist = stoll(line.substr(1));

        if (dir == 'R')
        {
            total += cerosderecha(pos, dist);

            long long d_mod = dist % 100;
            pos = (pos + d_mod) % 100;
        }
        else if (dir == 'L')
        {
            total += cerosizquierda(pos, dist);

            long long d_mod = dist % 100;
            pos = (pos - d_mod) % 100;
            if (pos < 0)
                pos += 100;
        }
    }

    cout << total << "\n";
    return 0;
}
