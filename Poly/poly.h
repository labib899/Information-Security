#ifndef POLY_H_INCLUDED
#define POLY_H_INCLUDED

#include<bits/stdc++.h>
using namespace std;

string message,mappedKey;

void generateKey()
{   
    cout<<"Enter message: ";
    getline(cin,message); cin.ignore();
    for(int i=0;i<message.size();i++) message[i]=toupper(message[i]);

    cout<<"Enter key: ";
    string key; getline(cin,key); cin.ignore();

    int spaces=count(key.begin(),key.end(),' ');
    remove(key.begin(),key.end(),' '); 
    key.resize(key.size()-spaces);
    for(int i=0;i<key.size();i++) key[i]=toupper(key[i]);

    for(int i=0,j=0;i<message.size();i++)
    {
        if(message[i]==' ') mappedKey+=' ';
        else mappedKey+=key[j%key.size()],j++;
    }
    cout<<"Mapped Key: "<<mappedKey<<endl;
}

void encrypt(string message,string mappedKey)
{
    string encrypted;
    for(int i=0;i<message.size();i++)
    {
        if(message[i]!=' ') encrypted+=(message[i]-'A'+mappedKey[i]-'A')%26+'A';
        else encrypted+=' ';
    }
    cout<<"Encrypted message: "<<encrypted<<endl;
}

void decrypt(string message,string mappedKey)
{
    string decrypted;
    for(int i=0;i<message.size();i++)
    {
        if(message[i]!=' ') decrypted+=(message[i]-mappedKey[i]+26)%26+'A';
        else decrypted+=' ';
    }
    cout<<"Decrypted message: "<<decrypted<<endl;
}


void mainFunc()
{
    cout<<"Enter choice: (1 or 2)"<<endl;
    cout<<"1. Encryption"<<endl;
    cout<<"2. Decryption"<<endl<<endl;;
    int choice; cin>>choice; cin.ignore();
    if(choice==1)
    {   
        cout<<"ENCRYPTION: "<<endl;
        generateKey();
        encrypt(message,mappedKey);
    }
    else if(choice==2)
    {   
        cout<<"DECRYPTION: "<<endl;
        generateKey();
        decrypt(message,mappedKey);
    }
    else cout<<"Wrong input!"<<endl;
}


#endif