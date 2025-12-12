#include <bits/stdc++.h>
using namespace std;

bool esLineaRegion(const string &s)
{
    int posDosPuntos = -1;
    for (int i = 0; i < (int)s.size(); i++)
    {
        if (s[i] == ':')
        {
            posDosPuntos = i;
            break;
        }
    }
    if (posDosPuntos == -1)
        return false;

    string left = s.substr(0, posDosPuntos);

    int posX = -1;
    for (int i = 0; i < (int)left.size(); i++)
    {
        if (left[i] == 'x')
        {
            posX = i;
            break;
        }
    }
    if (posX == -1)
        return false;
    if (posX == 0)
        return false;
    if (posX == (int)left.size() - 1)
        return false;

    for (int i = 0; i < (int)left.size(); i++)
    {
        char ch = left[i];
        if (ch == 'x')
            continue;
        if (!isdigit((unsigned char)ch))
            return false;
    }

    return true;
}

int main()
{

    vector<string> lineas;
    string s;
    while (getline(cin, s))
    {
        lineas.push_back(s);
    }

    vector<int> indices;
    vector<int> areasForma;

    int i = 0;
    while (i < (int)lineas.size() && !esLineaRegion(lineas[i]))
    {
        if (lineas[i].empty())
        {
            i++;
            continue;
        }

        string ln = lineas[i];

        int posDosPuntos = -1;
        for (int j = 0; j < (int)ln.size(); j++)
        {
            if (ln[j] == ':')
            {
                posDosPuntos = j;
                break;
            }
        }
        if (posDosPuntos == -1)
        {
            i++;
            continue;
        }

        string left = ln.substr(0, posDosPuntos);

        bool esNumero = !left.empty();
        for (int j = 0; j < (int)left.size(); j++)
        {
            if (!isdigit((unsigned char)left[j]))
                esNumero = false;
        }
        if (!esNumero)
        {
            i++;
            continue;
        }

        int idx = stoi(left);
        i++;

        int area = 0;
        while (i < (int)lineas.size() && !lineas[i].empty() && !esLineaRegion(lineas[i]))
        {
            for (int j = 0; j < (int)lineas[i].size(); j++)
            {
                if (lineas[i][j] == '#')
                    area++;
            }
            i++;
        }

        indices.push_back(idx);
        areasForma.push_back(area);

        if (i < (int)lineas.size() && lineas[i].empty())
            i++;
    }

    int maxIdx = -1;
    for (int j = 0; j < (int)indices.size(); j++)
    {
        if (indices[j] > maxIdx)
            maxIdx = indices[j];
    }

    int S = maxIdx + 1;
    vector<long long> area(S);

    for (int j = 0; j < (int)indices.size(); j++)
    {
        area[indices[j]] = areasForma[j];
    }

    int regionesOK = 0;

    for (; i < (int)lineas.size(); i++)
    {
        string ln = lineas[i];
        if (ln.empty())
            continue;
        if (!esLineaRegion(ln))
            continue;

        int posDosPuntos = -1;
        for (int j = 0; j < (int)ln.size(); j++)
        {
            if (ln[j] == ':')
            {
                posDosPuntos = j;
                break;
            }
        }

        string left = ln.substr(0, posDosPuntos);
        string right = ln.substr(posDosPuntos + 1);

        int posX = -1;
        for (int j = 0; j < (int)left.size(); j++)
        {
            if (left[j] == 'x')
            {
                posX = j;
                break;
            }
        }

        long long W = stoll(left.substr(0, posX));
        long long H = stoll(left.substr(posX + 1));
        long long areaTablero = W * H;

        stringstream ss(right);
        vector<long long> cnt;
        long long val;
        while (ss >> val)
        {
            cnt.push_back(val);
        }

        while ((int)cnt.size() < S)
        {
            cnt.push_back(0);
        }

        long long areaTotal = 0;
        for (int k = 0; k < S; k++)
        {
            areaTotal += cnt[k] * area[k];
            if (areaTotal > areaTablero)
                break;
        }

        if (areaTotal <= areaTablero)
            regionesOK++;
    }

    cout << regionesOK << "\n";
    return 0;
}
