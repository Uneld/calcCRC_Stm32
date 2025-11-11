# test_crc_stm32.py
import unittest
from calc_crc_stm32 import calc_crc_stm32

class TestCRCSTM32(unittest.TestCase):
    def test_crc_known_values(self):
        # Проверка массива [0..9]
        data = bytes(range(10))
        crc = calc_crc_stm32(data)
        self.assertEqual(crc, 0xD1, "CRC для [0..9] должно быть 0xD1")

        # Проверка массива [0..49]
        data = bytes(range(50))
        crc = calc_crc_stm32(data)
        # Значение можно проверить на STM32 и подставить сюда
        self.assertEqual(crc, 0xXX, "CRC для [0..49] должно совпадать с STM32")  # замените 0xXX на реальное значение

    def test_crc_empty(self):
        # Пустой массив
        data = b""
        crc = calc_crc_stm32(data)
        self.assertIsInstance(crc, int)

if __name__ == "__main__":
    unittest.main()
