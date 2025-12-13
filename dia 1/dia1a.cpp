#include <bits/stdc++.h>
using namespace std;

int main()
{

    int pos = 50;
    int cnt = 0;

    string line;
    while (cin >> line)
    {
        char dir = line[0];
        int dist = stoi(line.substr(1));

        if (dir == 'R')
        {
            pos = (pos + dist) % 100;
        }
        else if (dir == 'L')
        {
            pos = (pos - dist) % 100;
            if (pos < 0)
                pos += 100;
        }

        if (pos == 0)
        {
            cnt++;
        }
    }

    cout << cnt << "\n";
    return 0;
}
