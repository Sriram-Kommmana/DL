#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

int modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

string formatText(string text)
{
    string result="";
    for(char c : text)
    {
        if(isalpha(c))
            result += toupper(c);
    }
    return result;
}

vector<vector<int>> inverseKeyMatrix(vector<vector<int>> &K)
{
    vector<vector<int>> adj(3, vector<int>(3));

    int det =
        K[0][0]*(K[1][1]*K[2][2] - K[1][2]*K[2][1]) -
        K[0][1]*(K[1][0]*K[2][2] - K[1][2]*K[2][0]) +
        K[0][2]*(K[1][0]*K[2][1] - K[1][1]*K[2][0]);

    det = (det % 26 + 26) % 26;
    int invDet = modInverse(det, 26);

    adj[0][0] =  (K[1][1]*K[2][2] - K[1][2]*K[2][1]);
    adj[0][1] = -(K[1][0]*K[2][2] - K[1][2]*K[2][0]);
    adj[0][2] =  (K[1][0]*K[2][1] - K[1][1]*K[2][0]);

    adj[1][0] = -(K[0][1]*K[2][2] - K[0][2]*K[2][1]);
    adj[1][1] =  (K[0][0]*K[2][2] - K[0][2]*K[2][0]);
    adj[1][2] = -(K[0][0]*K[2][1] - K[0][1]*K[2][0]);

    adj[2][0] =  (K[0][1]*K[1][2] - K[0][2]*K[1][1]);
    adj[2][1] = -(K[0][0]*K[1][2] - K[0][2]*K[1][0]);
    adj[2][2] =  (K[0][0]*K[1][1] - K[0][1]*K[1][0]);

    vector<vector<int>> inv(3, vector<int>(3));

    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            inv[i][j] = ((adj[j][i] * invDet) % 26 + 26) % 26;

    return inv;
}

string process(string text, vector<vector<int>> &K)
{
    while(text.length() % 3 != 0)
        text += 'X';

    string result = "";

    for(int i=0;i<text.length();i+=3)
    {
        vector<int> P(3);
        for(int j=0;j<3;j++)
            P[j] = text[i+j] - 'A';

        vector<int> C(3,0);

        for(int j=0;j<3;j++)
            for(int k=0;k<3;k++)
                C[j] += K[j][k] * P[k];

        for(int j=0;j<3;j++)
            result += char((C[j] % 26) + 'A');
    }
    return result;
}

int main()
{
    vector<vector<int>> K = {
        {6,24,1},
        {13,16,10},
        {20,17,15}
    };

    string plain;
    cout<<"Enter Plaintext: ";
    getline(cin, plain);

    plain = formatText(plain);

    string cipher = process(plain, K);
    cout<<"Encrypted Text: "<<cipher<<endl;

    vector<vector<int>> invK = inverseKeyMatrix(K);
    string decrypted = process(cipher, invK);

    cout<<"Decrypted Text: "<<decrypted<<endl;

    return 0;
}
