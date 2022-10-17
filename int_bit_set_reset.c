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
	
	// data[2] de bizim bitlerini set - reset etmek istediğimiz verinin olduğunu varsayalım.
    uint8_t data[3];
    
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    
    setBit((data + 2), 0); // 0.biti 1 yap
    setBit((data + 2), 2);
    setBit((data + 2), 4);
    setBit((data + 2), 6);
    
    printBits(sizeof(uint8_t), data + 2);
    
    setBit((data + 2), 1); // 1.biti 1 yap
    setBit((data + 2), 3);
    setBit((data + 2), 5);
    setBit((data + 2), 7);
    
    resetBit((data + 2), 0);
    resetBit((data + 2), 2);
    resetBit((data + 2), 4);
    resetBit((data + 2), 6);
    
    printBits(sizeof(uint8_t), data + 2);
    

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