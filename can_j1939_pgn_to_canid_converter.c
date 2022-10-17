#include <stdio.h>
#include <stdint.h>

uint32_t pgn_to_can_id(uint8_t priority, uint8_t data_page, uint8_t pdu_format, uint8_t pdu_specific, uint8_t source_add);
void printBits(size_t const size, void const * const ptr);

int main()
{
    
    // Electronic Engine Controller 1	
    uint8_t p = 3;
    uint8_t data_p = 0;
    uint8_t pdu_f = 0xF0;
    uint8_t pdu_s = 0x04;
    uint8_t sa = 0xFE;
    
    uint32_t converted_can_id = pgn_to_can_id(p, data_p, pdu_f, pdu_s, sa);
    
    printBits(sizeof(converted_can_id), &converted_can_id);

    return 0;
}


uint32_t pgn_to_can_id(uint8_t priority, uint8_t data_page, uint8_t pdu_format, uint8_t pdu_specific, uint8_t source_add)
{
    uint32_t can_id = 0;
    uint32_t pgn = 0;
    // PGN 21 bit + SA 8 bit
    // priority (3) - reserved (1) - data page (1) - pdu format (8) - pdu_specific (8) - source addres (8)
    // 28:26 priority - 25 reserved - 24 data page - 23:16 pdu_format - 15:8 pdu_specific - 7:0 source address 
    
    pgn |= ((priority & 0x7) << 26);
    pgn |= (0 << 25);           			// reserved bit
    pgn |= ((data_page & 0x1) << 24);
    pgn |= ((pdu_format & 0xFF) << 16);
    pgn |= ((pdu_specific & 0xFF) << 8);
    
    can_id = pgn + ((source_add & 0xFF) << 0);  
    
    return can_id;
}

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
        printf(" ");
    }
    puts("");
}