#ifndef _MATRIXLED_H_
#define _MATRIXLED_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "Common.h"

/**
 * @brief Buffer for matrix LED panel.
 * @note Supports mono-color, binary and up to 8x8 size panel.
*/
typedef struct _MatrixLED {
  uint8_t width;   ///< width  <= 8
  uint8_t height;  ///< height <= 8
  uint8_t buffer[8];  ///< 8*8 bit = 64 bit = 8 byte
} MatrixLED;

/**
 * @brief Array of MatrixLED modules.
 * @note Supports mono-color, binary.
*/
typedef struct _MatrixLEDArray {
  MatrixLED *matrixLEDs;
  size_t length;  ///< valid length of matrixLEDs.
} MatrixLEDArray;

/**
 * @brief Initialize MatrixLED.
 * @param matrixLED [in] Pointer of MatrixLED to initialize.
 * @param width [in] Number of LED on the panel (horizontal).
 * @param height [in] Number of LED on the panel (vertical).
 * @retval matrixLED Given matrixLED pointer on success
*/
MatrixLED *initMatrixLED(MatrixLED *matrixLED, uint8_t width, uint8_t height);

/**
 * @brief Invert all LEDs' state (on or off).
 * @param matrixLED [in] Pointer of MatrixLED to flip.
*/
void flipMatrixLED(MatrixLED *matrixLED);

/**
 * @brief Fill all LEDs with 0 or 1.
 * @param matrixLED [in] Pointer of MatrixLED to fill.
 * @param value [in] Value for filling (0 or 1).
*/
void fillMatrixLED(MatrixLED *matrixLED, bool value);

/**
 * @brief Shift all LEDs to left by one bit.
 * @param matrixLED [in] Pointer of MatrixLED to shift.
 * @retval uint8_t Pack of overflowed bits
*/
uint8_t leftShiftMatrixLED(MatrixLED *matrixLED, uint8_t padding);

/**
 * @brief Initialize MatrixLEDArray.
 * @param matrixLEDArray [in] Pointer to MatrixLED to initialize.
 * @param matrixLEDs [in] Pointer to an Array of MatrixLED.
 * @param width [in] Number of LED per one panel (horizontal).
 * @param height [in] Number of LED per one panel (vertical).
 * @retval MatrixLEDArray Given MatrixLEDArray pointer on success
*/
MatrixLEDArray *initMatrixLEDArray(MatrixLEDArray *matrixLEDArray, MatrixLED *matrixLEDs, size_t length, int8_t width, uint8_t height);

/**
 * @brief Invert all LEDs' state (on or off).
 * @param matrixLEDArray [in] Pointer of MatrixLEDArray to flip.
*/
void flipMatrixLEDArray(MatrixLEDArray *matrixLEDArray);

/**
 * @brief Fill all LEDs with 0 or 1.
 * @param matrixLEDArray [in] Pointer of MatrixLEDArray to fill.
 * @param value [in] Value for filling (0 or 1).
*/
void fillMatrixLEDArray(MatrixLEDArray *matrixLEDArray, bool value);

/**
 * @brief Shift all LEDs to left by one bit.
 * @param matrixLEDArray [in] Pointer of MatrixLEDArray to shift.
 * @retval uint8_t Pack of overflowed bits
*/
uint8_t leftShiftMatrixLEDArray(MatrixLEDArray *matrixLEDArray, uint8_t padding);

#endif  /* _MATRIXLED_H_ */
