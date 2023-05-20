#include <iostream>
#include <Windows.h>
using namespace std;


//Инициализация массива s
int* Init_S() {
    int* S = new int [256];
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
    return S; 
}

int* KeySchedulingAlgoritm(string key) {
    int* S = Init_S();
    int j = 0;
    for (int i = 0; i < 255; i++) {
        j = (j + S[i] + key[i % key.length()]) % 256; 
        swap(S[i], S[j]);
    }
    return S; 
}

char* PRGA(string key, int len_text) {
    int* S = KeySchedulingAlgoritm(key);
    int t= 0;
    int j = 0;
    int i = 0; 
    int counter = 0; 
    char* K =  new char [len_text]; 
    while (counter < len_text) {
        i = (i + 1)%256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        t = (S[i] + S[j]) % 256;
        K[counter] = S[t];
        counter++;
    }
    return K; 
}

string Encrypt(string text, string key) {
    char* K = PRGA(key, text.length()); 
    char* encrypt = new char[text.length()];
    for (int i = 0; i < text.length(); i++) {
        encrypt[i] = K[i] ^ text[i];
    }
    encrypt[text.length()] = '\0';
    return string(encrypt); 
}

string Decrypt(string encrypt_text, string key) {
    char* K = PRGA(key, encrypt_text.length());
    char* decrypt = new char[encrypt_text.length()];
    for (int i = 0; i < encrypt_text.length(); i++) {
        decrypt[i] = K[i] ^ encrypt_text[i];
    }
    decrypt[encrypt_text.length()] = '\0';
    return string(decrypt);
}

int main()
{
    string key = "adbcb";
    string text = "giifbihtfb 666 jgjttokblgjnokdb";
    cout << Encrypt(text, key) << endl; 
    cout << Decrypt(Encrypt(text, key), key) << endl;
}

