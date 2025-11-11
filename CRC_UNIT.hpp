/**
 * @file    CRC_UNIT.hpp
 * @brief   CRC32 calculation using STM32 hardware CRC unit
 * 
 * This header defines a template class for performing CRC32 
 * calculations directly on STM32 microcontrollers. It leverages 
 * the built-in hardware CRC peripheral for maximum performance 
 * and reliability in embedded applications.
 * 
 * @license MIT License
 * Copyright (c) 2025 Uneld
 */

#ifndef SRC_USER_CRC_UNIT_H_
#define SRC_USER_CRC_UNIT_H_

#include "main.h"


template<typename TypeData>
class CRC_UNIT final {

public:
	CRC_UNIT();

	static void CRC_Init() {
	    RCC->AHBENR |= RCC_AHBENR_CRCEN; // �������� ������������ ������ CRC
	    CRC->CR = CRC_CR_RESET; // ���������� ������� CRC
	}

	static TypeData calculateCRC(TypeData *data, uint32_t length) {
		TypeData crc = 0;
		CRC->CR = CRC_CR_RESET; // ���������� ������� CRC
		uint8_t sizeData = sizeof(uint32_t);

		if (length >= sizeData) {
			uint32_t num_words = length / sizeData;
			uint32_t *src_32 = (uint32_t*) data;

			for (uint32_t i = 0; i < num_words; i++)
				CRC->DR = *(src_32++);

			data = (TypeData*) src_32;
			length %= sizeData;
		}

		uint8_t *src_8 = (uint8_t*) data;

		for (uint32_t i = 0; i < length; i++)
			CRC->DR = *(src_8++);

		crc = CRC->DR;

		return crc; // ���������� ��������� CRC
	}
};

#endif /* SRC_USER_CRC_UNIT_H_ */
