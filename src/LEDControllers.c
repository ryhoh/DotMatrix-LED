#include "LEDControllers.h"

Max7219 *initMax7219(
  Max7219 *max7219,
  uint8_t dat,
  uint8_t lat,
  uint8_t clk,
  uint8_t brightness
) {
  max7219->dat = dat;
  max7219->lat = lat;
  max7219->clk = clk;

  driv_call_pinMode(dat, OUTPUT);
  driv_call_pinMode(lat, OUTPUT);
  driv_call_pinMode(clk, OUTPUT);

  sendToMax7219(max7219, 0x0c, 0x01);  // シャットダウン -> オペレート
  sendToMax7219(max7219, 0x0b, 0x07);  // スキャンリミット設定 -> 8桁
  sendToMax7219(max7219, 0x09, 0x00);  // デコードモード -> No decodeモード

  // 残留表示を消去
  for (uint8_t addr_i = 1; addr_i < 9; ++addr_i) {
    sendToMax7219(max7219, addr_i, 0x0F);  // 文字blankを送信
  }

  // 輝度設定
  MACR_CLIP(brightness, MAX7219_BRIGHTNESS_LEVEL_MIN, MAX7219_BRIGHTNESS_LEVEL_MAX)
  sendToMax7219(max7219, 0x0a, brightness);
  driv_call_sleep(1000);

  return max7219;
}

void testRunMax7219(
  const Max7219 *max7219
) {
  // ディスプレイテストモード（全点灯）
  sendToMax7219(max7219, 0x0f, 0x01);
  driv_call_sleep(1000);

  // テストモード終了
  sendToMax7219(max7219, 0x0f, 0x00);
  driv_call_sleep(500);

  // リセット
  for (uint8_t addr_i = 1; addr_i < 9; ++addr_i) {
    sendToMax7219(max7219, addr_i, 0x00);
  }
}

void flushMatrixLEDByMax7219(
  const Max7219 *max7219,
  const MatrixLED *matrixLED
) {
  driv_call_digitalWrite(max7219->lat, LOW);
  for (uint8_t row_i = 0; row_i < 8; ++row_i) {
    shiftOutToMax7219(max7219, row_i + 1, *(matrixLED->buffer + row_i));
  }
  driv_call_digitalWrite(max7219->lat, HIGH);
  driv_call_digitalWrite(max7219->lat, LOW);
}

void flushMatrixLEDsByMax7219(
  const Max7219 *max7219,
  const MatrixLED *matrixLEDs,
  uint8_t length
) {
  for (uint8_t row_i = 0; row_i < 8; ++row_i) {
    driv_call_digitalWrite(max7219->lat, LOW);
    for (uint8_t matrix_i = 0; matrix_i < length; ++matrix_i) {
        shiftOutToMax7219(max7219, row_i + 1, *((matrixLEDs + matrix_i)->buffer + row_i));
    }
    driv_call_digitalWrite(max7219->lat, HIGH);
    driv_call_digitalWrite(max7219->lat, LOW);
  }
}