#include <stdio.h>
#include <stdint.h>

void setBit(uint8_t *pData, uint8_t i);
void resetBit(uint8_t *pData, uint8_t i);
void printBits(size_t const size, void const * const ptr);

int main()
{
    uint8_t my = 0;
    
    setBit(&my, 2);
    setBit(&my, 7);
    resetBit(&my, 2);
    resetBit(&my, 7);
    

    return 0;
}

void setBit(uint8_t *pData, uint8_t i)
{
    uint8_t temp;
    temp = *pData;
    
    temp |= (1 << i);
    printf("set bit ->%d\n", i);
    printBits(sizeof(temp), &temp);
    
    *pData = temp;
}

void resetBit(uint8_t *pData, uint8_t i)
{
    uint8_t temp;
    temp = *pData;
    
    temp &= ~(1 << i);
    printf("reset bit ->%d\n", i);
    printBits(sizeof(temp), &temp);
    
    *pData = temp;
}

// Assumes little endian
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}