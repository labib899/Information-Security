#include <bits/stdc++.h>
#include "struct.h"
using namespace std;

#define uchar   unsigned char
#define uint    unsigned int
// const int N=16;
// const int R=10;

void subRoundKey(uchar *state,uchar *roundKey)
{
    for(int i=0;i<N;i++) state[i]=state[i] xor roundKey[i];
}

void invMixColumns(uchar *state)
{
    uchar temp[N];
    for(int i=0;i<4;i++)
    {   
        int a=4*i;
        temp[a+0]=(uchar) mul14[state[a]]^mul11[state[a+1]]^mul13[state[a+2]]^mul9[state[a+3]];
        temp[a+1]=(uchar) mul9[state[a]]^mul14[state[a+1]]^mul11[state[a+2]]^mul13[state[a+3]];
        temp[a+2]=(uchar) mul13[state[a]]^mul9[state[a+1]]^mul14[state[a+2]]^mul11[state[a+3]];
        temp[a+3]=(uchar) mul11[state[a]]^mul13[state[a+1]]^mul9[state[a+2]]^mul14[state[a+3]];
    }
    for(int i=0;i<N;i++) state[i]=temp[i];
}

void invShiftRows(uchar *state)
{
    uchar temp[N];
    //1st column
    temp[0]=state[0];
    temp[1]=state[13];
    temp[2]=state[10];
    temp[3]=state[7];
    //2nd column
    temp[4]=state[4];
    temp[5]=state[1];
    temp[6]=state[14];
    temp[7]=state[11];
    //3rd column
    temp[8]=state[8];
    temp[9]=state[5];
    temp[10]=state[2];
    temp[11]=state[15];
    //4th column
    temp[12]=state[12];
    temp[13]=state[9];
    temp[14]=state[6];
    temp[15]=state[3];

    for(int i=0;i<N;i++) state[i]=temp[i];
}

void subBytes(uchar *state)
{
    for(int i=0;i<N;i++) state[i]=invSbox[state[i]];
}

void round(uchar *state,uchar *key)
{
    subRoundKey(state,key);
    invMixColumns(state);
    invShiftRows(state);
    subBytes(state);
}

void decrypt(uchar *state,uchar *extendedKey)
{
    // round 10
    subRoundKey(state,extendedKey+16*R);
    invShiftRows(state);
    subBytes(state);
    // round 9 to 1
    for(int i=R-1;i>=1;i--) round(state,extendedKey+16*i);
    //round 0
    subRoundKey(state,extendedKey);
}


int main()
{
    uchar key_in[2*N+1],cipher[2*N+1];
    cin>>key_in>>cipher;
    
    uchar ciphertext[N],key[N],extendedKey[N*(R+1)];
    for(int i=0;i<N;i++)
    {
        key[i]=ascii2hex(key_in[2*i])*16+key_in[2*i+1];
        ciphertext[i]=ascii2hex(cipher[2*i])*16+ascii2hex(cipher[2*i+1]);
    }
    extendKey(key,extendedKey);
    decrypt(ciphertext,extendedKey);
    for(int i=0;i<N;i++)
    {
        printf("%02x", ciphertext[i]);
    }
    cout<<endl;
}