/*
 * conf.h
 *
 *  Created on: Jun 3, 2024
 *      Author: mhanzout
 */

#ifndef APPLICATION_USER_TASK_INC_CONF_H_
#define APPLICATION_USER_TASK_INC_CONF_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

#define FFT_LENGTH                     256
#define SAMPLE_TIME_MS_TASK            4 /*ms*/  //100 Hz

typedef struct
{
  float real;
  float imag;

} ComplexTypeDef;

typedef enum
{
  NO_WIND,
  HM_WIND,
  HN_WIND
} fftWindTyped;

typedef struct
{
  ComplexTypeDef Input[FFT_LENGTH];
  float Result[FFT_LENGTH * 2];
  uint32_t current_sample;
  fftWindTyped fft_windowing;
} FFT_TypeDef;
/* USER CODE END EM */

#define FIRST_HALF           1
#define SECOND_HALF          2

typedef enum
{
  FIR_FILTRE,
  IIR_FILTRE,
  RC_FILTRE,
  NOTCH_FILTRE,
  MOVING_AVG_FILTRE
} FiltreType;

typedef enum
{
  ACCELRO,
  SIN_WAVE,
  DUAL_SIN_WAVE,
  THRID_SIN_WAVE,
  GYRO_WAVE
} InType;

typedef struct
{
  uint8_t signal2_state;
  uint8_t signal3_state;

  float inputFreq1_Hz; /*2Hz*/
  float inputFreq2_Hz;
  float inputFreq3_Hz; /*2Hz*/
  uint32_t Amp1;
  uint32_t Amp2;
  uint32_t Amp3;

} inputSimuTypeDef;

typedef struct
{
  float fft_resolution;

} fftType_TypedDef;

typedef struct
{

  inputSimuTypeDef In;
  FiltreType filtre_Type;

  uint8_t fir_enable;
  uint8_t iir_enable;
  fftType_TypedDef fft;
  FFT_TypeDef *in_fft;
  FFT_TypeDef *out_fft;

} SimuleTypeDef;

#ifdef __cplusplus
}
#endif

#endif /* APPLICATION_USER_TASK_INC_CONF_H_ */
