#include <bits/stdc++.h>
using namespace std;

// Recorta espacios por la izquierda y derecha
string trim(const string &s)
{
    int n = (int)s.size();
    int i = 0;
    while (i < n && s[i] == ' ')
        ++i;
    int j = n - 1;
    while (j >= i && s[j] == ' ')
        --j;
    if (i > j)
        return "";
    return s.substr(i, j - i + 1);
}

int main()
{


    vector<string> lines;
    string line;
    int maxLen = 0;

    // 1) Leer todas las líneas
    while (getline(cin, line))
    {
        lines.push_back(line);
        maxLen = max(maxLen, (int)line.size());
    }

    if (lines.empty())
    {
        cout << 0 << "\n";
        return 0;
    }

    // Hacer la matriz rectangular rellenando con espacios
    for (string &row : lines)
    {
        if ((int)row.size() < maxLen)
        {
            row += string(maxLen - row.size(), ' ');
        }
    }

    int rows = (int)lines.size();
    int cols = maxLen;
    int fila_op = rows - 1; // última fila: operadores

    // 2) Marcar columnas separadoras (todas espacios)
    vector<bool> sep(cols, false);
    for (int c = 0; c < cols; ++c)
    {
        bool allSpace = true;
        for (int r = 0; r < rows; ++r)
        {
            if (lines[r][c] != ' ')
            {
                allSpace = false;
                break;
            }
        }
        sep[c] = allSpace;
    }

    long long grand_total = 0;

    int c = 0;
    while (c < cols)
    {

        while (c < cols && sep[c])
            ++c;
        if (c >= cols)
            break;

        int c_start = c;
        while (c < cols && !sep[c])
            ++c;
        int c_end = c - 1;

        int width = c_end - c_start + 1;

        char op = 0;
        for (int cc = c_start; cc <= c_end; ++cc)
        {
            if (lines[fila_op][cc] == '+' || lines[fila_op][cc] == '*')
            {
                op = lines[fila_op][cc];
                break;
            }
        }
        if (op == 0)
        {
            continue;
        }

        vector<long long> nums;
        for (int cc = c_start; cc <= c_end; ++cc)
        {
            string colDigits;
            for (int r = 0; r < fila_op; ++r)
            {
                char ch = lines[r][cc];
                if (isdigit(static_cast<unsigned char>(ch)))
                {
                    colDigits.push_back(ch);
                }
                else if (ch == ' ')
                {
                }
                else
                {
                }
            }
            string t = trim(colDigits);
            if (!t.empty())
            {
                long long val = stoll(t);
                nums.push_back(val);
            }
        }

        if (nums.empty())
            continue;

        long long value;
        if (op == '+')
        {
            value = 0;
            for (long long v : nums)
                value += v;
        }
        else
        { // op == '*'
            value = 1;
            for (long long v : nums)
                value *= v;
        }

        grand_total += value;
    }

    cout << grand_total << "\n";
    return 0;
}
