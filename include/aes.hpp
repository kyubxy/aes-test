#pragma once

#include <cstdint>
#include <vector>

#define BLOCK_SIZE 128

// for simplicity we'll stick to implementing AES-128
class AES
{
private:
    int rounds;


protected:
    uint8_t *plaintext;
    std::size_t size;
    // we'll just store the key in a large buffer and read one byte at a time
    std::vector<uint8_t> key; 

    virtual void padPlain(uint8_t *pt, int pad) = 0;
    virtual void byteSub() = 0;
    virtual void shiftRows() = 0;
    virtual void mixCols() = 0;
    virtual void roundKey(std::vector<uint8_t> key) = 0;

public:
    AES(uint8_t *plaintext, std::size_t size, std::vector<uint8_t> key, int rounds=10)
    {
        this->plaintext = plaintext;
        this->size = size;
        this->key = key;
        this->rounds = rounds;
    }
	   
    void encrypt(uint8_t *ciphertext)
    {
        int keyi = 0;
        std::vector<uint8_t> s(key.begin()+keyi, key.begin()+keyi+4);
        roundKey(s);
        keyi += 4;
        for (int i = 0; i < rounds; i++)
        {
            byteSub();
            shiftRows();
            mixCols();
            std::vector<uint8_t> s1(key.begin()+keyi, key.begin()+keyi+4);
            roundKey(s1);
            keyi += 4;
        }
        byteSub();
        shiftRows();
        std::vector<uint8_t> s2(key.begin()+keyi, key.begin()+keyi+4);
        roundKey(s2);
    }
};
