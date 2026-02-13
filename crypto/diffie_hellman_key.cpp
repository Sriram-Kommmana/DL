#include <iostream>
using namespace std;

int modExp(int base, int exp, int mod)
{
    int res = 1;
    base %= mod;

    while (exp > 0)
    {
        if (exp % 2)
            res = (res * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

string prep(string t)
{
    string r = "";

    for (char c : t)
        if (c != ' ')
            r += toupper(c);

    for (char &c : r)
        if (c == 'J')
            c = 'I';

    return r;
}

void matrixGen(string key, char m[5][5])
{
    bool used[26] = {0};
    key = prep(key);

    string s = key + "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    int k = 0;

    for (char c : s)
    {
        if (!used[c - 'A'])
        {
            m[k / 5][k % 5] = c;
            used[c - 'A'] = 1;
            k++;
        }
        if (k == 25)
            break;
    }
}

void find(char m[5][5], char a, char b,
          int &r1, int &c1, int &r2, int &c2)
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
        {
            if (m[i][j] == a)
            {
                r1 = i;
                c1 = j;
            }
            if (m[i][j] == b)
            {
                r2 = i;
                c2 = j;
            }
        }
}

string enc(string t, char m[5][5])
{
    t = prep(t);
    string r = "";

    for (int i = 0; i < t.length(); i += 2)
    {
        char a = t[i];
        char b = (i + 1 < t.length()) ? t[i + 1] : 'X';

        if (a == b)
            b = 'X';

        int r1, c1, r2, c2;
        find(m, a, b, r1, c1, r2, c2);

        if (r1 == r2)
        {
            r += m[r1][(c1 + 1) % 5];
            r += m[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2)
        {
            r += m[(r1 + 1) % 5][c1];
            r += m[(r2 + 1) % 5][c2];
        }
        else
        {
            r += m[r1][c2];
            r += m[r2][c1];
        }
    }
    return r;
}

string dec(string t, char m[5][5])
{
    string r = "";

    for (int i = 0; i < t.length(); i += 2)
    {
        char a = t[i], b = t[i + 1];
        int r1, c1, r2, c2;

        find(m, a, b, r1, c1, r2, c2);

        if (r1 == r2)
        {
            r += m[r1][(c1 + 4) % 5];
            r += m[r2][(c2 + 4) % 5];
        }
        else if (c1 == c2)
        {
            r += m[(r1 + 4) % 5][c1];
            r += m[(r2 + 4) % 5][c2];
        }
        else
        {
            r += m[r1][c2];
            r += m[r2][c1];
        }
    }
    return r;
}

int main()
{
    int p = 11, g = 2, a = 5, b = 7, k1 = 8, k2 = 3;

    int A = modExp(g, a, p);
    int B = modExp(g, b, p);

    int KA = modExp(k1, a, p);
    int KB = modExp(k2, b, p);

    cout << "Alice thinks key = " << KA << endl;
    cout << "Bob thinks key = " << KB << endl;

    char mA[5][5], mB[5][5];
    matrixGen("KEYTEN", mA);
    matrixGen("KEYNINE", mB);

    string msg = "HELLO";

    string cA = enc(msg, mA);
    cout << "\nAlice sends: " << cA << endl;

    string read = dec(cA, mA);
    cout << "Darth reads: " << read << endl;

    string cB = enc(read, mB);
    cout << "Darth sends to Bob: " << cB << endl;

    string final = dec(cB, mB);
    cout << "Bob receives: " << final << endl;

    return 0;
}
