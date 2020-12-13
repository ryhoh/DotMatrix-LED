#ifndef _LED_CONTROLLERS_H_
#define _LED_CONTROLLERS_H_

#include "DeviceInterface.h"
#include "MatrixLED.h"
#include <stdint.h>

/*
 *  マトリクスLEDが複数接続（MAX7219のカスケード接続）されている場合、
 *  MAX7219に2Byteのデータを送る度に、古いデータが後ろのMAX7219へ押し出される
 *
 *  表示内容の更新を行うには、全体の表示内容を作った上で、
 *  それを1行(1digit)ずつMAX7219の数だけ繰り返して送信し、
 *  8行(8digit)分それを繰り返す
 *
 *  データ送信は (レジスタアドレス 1Byte, データ 1Byte) で行う
 *  レジスタアドレスは 0x01 ~ 0x08 を使う（0スタートでない）ことに注意
 */

/**
 * @brief Controller for Max7219
*/
typedef struct _Max7219 {
  uint8_t dat;  ///< Pin number connecting dat
  uint8_t lat;  ///< Pin number connecting lat (or cs)
  uint8_t clk;  ///< Pin number connecting clk
} Max7219;

/**
 * @brief Initialize Max7219.
 * @param max7219 [in] Pointer of Max7219 to initialize.
 * @param dat [in] dat pin.
 * @param lat [in] lat pin.
 * @param clk [in] clk pin.
 * @param brightness [in] Integer between [0, 9].
 * @retval max7219 Given Max7219 pointer
*/
Max7219 *initMax7219(Max7219 *max7219, uint8_t dat, uint8_t lat, uint8_t clk, uint8_t brightness);

/**
 * @brief Do test run.
 * @param max7219 [in] Pointer of Max7219 to test.
*/
void testRunMax7219(Max7219 *max7219);

/**
 * @brief Flush data from single MatrixLED to Max7219.
 * @param max7219 [in] Pointer of Max7219 to write.
 * @param matrixLED [in] Pointer of MatrixLED to read.
*/
void flushMatrixLEDByMax7219(Max7219 *max7219, MatrixLED *matrixLED);

/**
 * @brief Flush data from multiple MatrixLEDs to Max7219.
 * @param max7219 [in] Pointer of Max7219 to write.
 * @param matrixLEDs [in] Pointer of MatrixLED-Array to read.
 * @param length [in] Length of MatrixLED-Array.
 * @note When length is 1, same to flushMatrixLEDByMax7219.
*/
void flushMatrixLEDsByMax7219(Max7219 *max7219, MatrixLED *matrixLEDs, uint8_t length);

// params: レジスタアドレス, データ
// ラッチ操作を行わないバージョン
static inline void shiftOutToMax7219(Max7219 *max7219, uint8_t addr, uint8_t data)
{
  call_shiftOut(max7219->dat, max7219->clk, MSBFIRST, addr);
  call_shiftOut(max7219->dat, max7219->clk, MSBFIRST, data);
}

// params: レジスタアドレス, データ
// ラッチ操作を行う（1件だけ送る）バージョン
static inline void sendToMax7219(Max7219 *max7219, uint8_t addr, uint8_t data)
{
  call_digitalWrite(max7219->lat, LOW);
  shiftOutToMax7219(max7219, addr, data);
  call_digitalWrite(max7219->lat, HIGH);
  call_digitalWrite(max7219->lat, LOW);
}

#endif  /* _LED_CONTROLLERS_H_ */