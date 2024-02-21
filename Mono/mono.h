#ifndef MONO_H_INCLUDED
#define MONO_H_INCLUDED

#include<bits/stdc++.h>
using namespace std;

string message;
map<char,char> enc,decr;
vector<bool> used(26,false);

void generateMapping()
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

    char ch='A';
    for(int i=0;i<key.size() and ch<='Z';i++)
    {
        if(!used[key[i]-'A'])
        {
            enc[ch]=key[i];
            decr[key[i]]=ch;
            used[key[i]-'A']=true;
            ch++;
        }
    }
    for(;ch<='Z';ch++)
    {
        for(int i=0;i<26;i++)
        {
            if(!used[i])
            {
                enc[ch]=i+'A';
                decr[i+'A']=ch;
                used[i]=true;
                break;
            }
        }
    }
    //for(auto c:enc) cout<<c.first<<" "<<c.second<<endl;
}

void encrypt(string message)
{
    string encrypted;
    for(int i=0;i<message.size();i++)
    {
        if(message[i]!=' ') encrypted+=enc[message[i]];
        else encrypted+=' ';
    }
    cout<<"Encrypted message: "<<encrypted<<endl;
}

void decrypt(string message)
{
    string decrypted;
    for(int i=0;i<message.size();i++)
    {
        if(message[i]!=' ') decrypted+=decr[message[i]];
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
        generateMapping();
        encrypt(message);
    }
    else if(choice==2)
    {   
        cout<<"DECRYPTION: "<<endl;
        generateMapping();
        decrypt(message);
    }
    else cout<<"Wrong input!"<<endl;
}


#endif