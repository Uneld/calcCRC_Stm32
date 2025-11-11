/*
 * test_crc.cpp
 *
 * Пример теста для CRC_UNIT на STM32
 */

#include "CRC_UNIT.h"
#include <cstdio>

int main() {
	CRC_UNIT<uint8_t>::CRC_Init();

//	или HAL инициализация:

//	hcrc.Instance = CRC;
//	if (HAL_CRC_Init(&hcrc) != HAL_OK)
//	{
//	Error_Handler();
//	}
	
    uint8_t data1[10] = {0,1,2,3,4,5,6,7,8,9};
    uint8_t crc1 = CRC_UNIT<uint8_t>::calculateCRC(data1, 10);
    printf("CRC [0..9] = 0x%02X\n", crc1); // ожидаем 0xD1

    uint8_t data2[50];
    for (int i = 0; i < 50; i++) data2[i] = i;
    uint8_t crc2 = CRC_UNIT<uint8_t>::calculateCRC(data2, 50);
    printf("CRC [0..49] = 0x%02X\n", crc2); // сверить с Python

    return 0;
}
