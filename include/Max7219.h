#ifndef _MAX7219_H_
#define _MAX7219_H_

#include "MatrixBuffer.h"

#ifdef SIMULATOR
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>

#endif  /* SIMULATOR */

/*
 *  MAX7219の制御
 *
 *  DATA  = DAT  テスト環境ではD11へ接続
 *  LATCH = LAT  テスト環境ではD10へ接続
 *  CLOCK = CLK  テスト環境ではD13へ接続
 *
 *  MAX7219: 7セグメントLED8桁を制御可能なチップ
 *           8x8ドットマトリクスLEDの制御にも転用可能
 */

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

class Max7219_8x8 {
public:
  uint8_t DAT;
  uint8_t LAT;
  uint8_t CLK;
  uint8_t screen_n;

  #ifdef ARDUINO
  void init();
  void test();
  void sendToDevice(uint8_t addr, uint8_t data);
  #endif
  virtual void shiftToRegister(uint8_t addr, uint8_t data);
  virtual void print(MatrixBuffer *matrixBuffer);

  Max7219_8x8(uint8_t screen_n);
};

#ifdef SIMULATOR
class Max7219_8x8_Simlator : public Max7219_8x8 {
  #define HIGH
  #define LOW
  #define digitalWrite(a, b)

public:
  using Max7219_8x8::Max7219_8x8;

  struct VirtualDevice {
    std::vector<std::deque<uint8_t>> reg = std::vector<std::deque<uint8_t>>(8);

    void print_screen();
    std::string toString();
  };
  VirtualDevice virtualDevice;

  virtual std::string generateScreen();
  virtual void updateBuffer(MatrixBuffer *matrixBuffer);
  virtual void shiftToRegister(uint8_t addr, uint8_t data) override;
  virtual void print(MatrixBuffer *matrixBuffer) override;
};
#endif /* SIMULATOR */

#endif  /* _MAX7219_H_ */