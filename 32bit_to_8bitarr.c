#include <stdio.h>
void print_32_to_8(unsigned long x);

int main()
{
    
    unsigned long buff[3] = {0x390055, 0x58485018, 0x20383852};
    
    for (int i = 0; i < 3; i++) {
        print_32_to_8(buff[i]);
    }
    
    
    
    

    return 0;
}

void print_32_to_8(unsigned long x) {
    
    unsigned int b1 = (unsigned int)(x & 0xff);
    unsigned int b2 = (unsigned int)(x >> 8) & 0xff;
    unsigned int b3 = (unsigned int)(x >> 16) & 0xff;
    unsigned int b4 = (unsigned int)(x >> 24);
    
    printf("%X\n", x);
    printf("%X\n", b1);
    printf("%X\n", b2);
    printf("%X\n", b3);
    printf("%X\n", b4);
}