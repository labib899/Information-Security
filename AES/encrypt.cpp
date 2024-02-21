#include <bits/stdc++.h>
#include "struct.h"
using namespace std;

#define uchar   unsigned char
#define uint    unsigned int
// const int N=16;
// const int R=10;

void addRoundKey(uchar *state,uchar *roundKey)
{
    for(int i=0;i<N;i++) state[i]=state[i] xor roundKey[i];
}

void subBytes(uchar *state)
{
    for(int i=0;i<N;i++) state[i]=sbox[state[i]];
}

void shiftRows(uchar *state)
{
    uchar temp[N];
    //1st column
    temp[0]=state[0];
    temp[1]=state[5];
    temp[2]=state[10];
    temp[3]=state[15];
    //2nd column
    temp[4]=state[4];
    temp[5]=state[9];
    temp[6]=state[14];
    temp[7]=state[3];
    //3rd column
    temp[8]=state[8];
    temp[9]=state[13];
    temp[10]=state[2];
    temp[11]=state[7];
    //4th column
    temp[12]=state[12];
    temp[13]=state[1];
    temp[14]=state[6];
    temp[15]=state[11];

    for(int i=0;i<N;i++) state[i]=temp[i];
}

void mixColumns(uchar *state)
{
    uchar temp[N];
    for(int i=0;i<4;i++)
    {
        temp[4*i+0]=(uchar)mul2(state[4*i])^mul3(state[4*i+1])^state[4*i+2]^state[4*i+3];
        temp[4*i+1]=(uchar)state[4*i]^mul2(state[4*i+1])^mul3(state[4*i+2])^state[4*i+3];
        temp[4*i+2]=(uchar)state[4*i]^state[4*i+1]^mul2(state[4*i+2])^mul3(state[4*i+3]);
        temp[4*i+3]=(uchar)mul3(state[4*i])^state[4*i+1]^state[4*i+2]^mul2(state[4*i+3]);
    }

    for(int i=0;i<N;i++) state[i]=temp[i];
}

void round(uchar *state,uchar *key)
{
    subBytes(state);
    shiftRows(state);
    mixColumns(state);
    addRoundKey(state,key);
}

void encrypt(uchar *state,uchar *extendedKey)
{
    addRoundKey(state,extendedKey); // round 0
    for(int i=1;i<R;i++) round(state,extendedKey+16*i); // round 1 to 9
    // round 10
    subBytes(state); shiftRows(state); addRoundKey(state,extendedKey+16*R);
}


int main()
{
    uchar key_in[2*N+1],plain[2*N+1];
    cin>>key_in>>plain;
    
    uchar plaintext[N],key[N],extendedKey[N*(R+1)];
    for(int i=0;i<N;i++)
    {
        key[i]=ascii2hex(key_in[2*i])*16+key_in[2*i+1];
        plaintext[i]=ascii2hex(plain[2*i])*16+ascii2hex(plain[2*i+1]);
    }
    extendKey(key,extendedKey);
    encrypt(plaintext,extendedKey);
    for(int i=0;i<N;i++)
    {
        printf("%02x", plaintext[i]);
    }
    cout<<endl;
}
