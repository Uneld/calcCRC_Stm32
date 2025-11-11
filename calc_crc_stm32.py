# @file    calc_crc_stm32.py
# @brief   CRC32 calculation emulation for STM32 controllers
#
# This module provides a pure Python implementation of the CRC32 
# algorithm used in STM32 hardware. It is intended for desktop 
# environments, testing, and validation, ensuring results identical 
# to those produced by STM32 microcontrollers.
#
# @license MIT License
# Copyright (c) 2025 Uneld

 
import struct

POLY = 0x04C11DB7


def cal_crc32(word: int, crc32_value: int) -> int:
    """Обработка одного слова/байта для CRC32 (полином 0x04C11DB7)."""
    crc32_value ^= word
    crc32_value &= 0xFFFFFFFF  # ограничение до uint32_t
    for _ in range(32):  # цикл по битам
        if crc32_value & 0x80000000:
            crc32_value = ((crc32_value << 1) & 0xFFFFFFFF) ^ POLY
        else:
            crc32_value = (crc32_value << 1) & 0xFFFFFFFF
    return crc32_value


def calc_crc_stm32(in_data: bytes) -> int:
    """Эмуляция CRC32 STM32F103: проход по 4-байтным словам и хвостовым байтам."""
    crc32 = 0xFFFFFFFF
    word_size = 4
    length = len(in_data)

    # Основные слова
    for i in range(0, length - (length % word_size), word_size):
        word = struct.unpack_from('<I', in_data, i)[0]  # little-endian uint32_t
        crc32 = cal_crc32(word, crc32)

    # Хвостовые байты
    for b in in_data[length - (length % word_size):]:
        crc32 = cal_crc32(b, crc32)

    return crc32 & 0xFF  # только младший байт, как в STM32
