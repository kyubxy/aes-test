#include "softwareaes.hpp"

#define XTIME(a) ((a) & 0x80) ?  ((((a) << 1) ^ 0x1B) & 0xFF) : ((a) << 1)

void SoftwareAES::padPlain(uint8_t *pt, int pad) 
{

}

void SoftwareAES::byteSub() 
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            S(i,j) = sbox[S(i,j)];
}


void SoftwareAES::shiftRows() 
{
    // row 1
    {
        auto tmp = S(1,0);
        S(1,0) = S(1,1);
        S(1,1) = S(1,2);
        S(1,2) = S(1,3);
        S(1,3) = tmp;
    }

    // row 2
    {
        auto tmp1 = S(2,0);
        auto tmp2 = S(2,1);
        S(2,0) = S(2,2);
        S(2,1) = S(2,3);
        S(2,2) = tmp1;
        S(2,3) = tmp2;
    }

    // row 3
    {
        auto tmp1 = S(3,0);
        auto tmp2 = S(3,2);
        auto tmp3 = S(3,3);
        S(3,0) = S(3,3);
        S(3,1) = tmp1;
        S(3,2) = tmp2;
        S(3,3) = tmp3;
    }
}


void SoftwareAES::mixSingleCol(uint8_t *a)
{
    uint8_t t = a[0] ^ a[1] ^ a[2] ^ a[3];
    uint8_t u = a[0];
    a[0] ^= t ^ XTIME(a[0] ^ a[1]);
    a[1] ^= t ^ XTIME(a[1] ^ a[2]);
    a[2] ^= t ^ XTIME(a[2] ^ a[3]);
    a[3] ^= t ^ XTIME(a[3] ^ u);
}

void SoftwareAES::mixCols() 
{
    for (int i = 0; i < 4; i++)
        this->mixSingleCol(state[i]);
}

void SoftwareAES::roundKey(std::vector<uint8_t> key) 
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            S(i,j) ^= key[i][j]; // TODO: make the key a matrix ig
}
