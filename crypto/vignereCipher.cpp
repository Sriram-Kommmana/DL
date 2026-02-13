#include <iostream>
#include <cctype>
using namespace std;

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

string generateKey(string text, string key)
{
    int x = text.size();
    for(int i=0; key.size() < x; i++)
        key += key[i];
    return key;
}

string encrypt(string text, string key)
{
    string cipher="";
    for(int i=0;i<text.size();i++)
    {
        int val = ((text[i]-'A') + (key[i]-'A')) % 26;
        cipher += char(val + 'A');
    }
    return cipher;
}

string decrypt(string cipher, string key)
{
    string plain="";
    for(int i=0;i<cipher.size();i++)
    {
        int val = ((cipher[i]-'A') - (key[i]-'A') + 26) % 26;
        plain += char(val + 'A');
    }
    return plain;
}

int main()
{
    string text, key;

    cout<<"Enter Plaintext: ";
    getline(cin,text);

    cout<<"Enter Key: ";
    getline(cin,key);

    text = formatText(text);
    key = formatText(key);

    key = generateKey(text,key);

    string cipher = encrypt(text,key);
    cout<<"Encrypted Text: "<<cipher<<endl;

    string decrypted = decrypt(cipher,key);
    cout<<"Decrypted Text: "<<decrypted<<endl;

    return 0;
}
