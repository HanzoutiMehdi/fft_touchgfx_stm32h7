/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "conf.h"
#include "cmsis_os.h"
#include "stdlib.h"
#include "myfir.h"
#include "iir_filtre.h"
#include  "FreeRTOS.h"
#include "queue.h"
#include "arm_math.h"

/*Extern Global Variables-------------- */
extern QueueHandle_t xQueue_fft;
extern float Fir_FiltreCoeff[NUM_TAPS];
extern FFT_TypeDef in_fft;
extern FFT_TypeDef out_fft;

/*Private Variables ----------------------*/


/*Public Varibales----------------------------- */
SimuleTypeDef hSim;
IIRFiltre hiir;
float inputSignal;
float filt_out;

#define APLFA_IIR    0.5f


/*Private Functions ----------------------*/
static void StoreNewSample(FFT_TypeDef *hfft, float in);
static float Get_NewSample(uint32_t discret_times_ms);
static float filtre_Sample(float in);




static uint32_t SamplingTime = SAMPLE_TIME_MS_TASK;
/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void vmainTask(void const *argument)
{
  /*init */
  uint32_t discret_times_ms = 0;

  hSim.In.Amp1 = 100;
  hSim.In.Amp2 = 70;
  hSim.In.Amp3 = 30;

  /*Init Sim*/
  hSim.In.inputFreq1_Hz = 5.0f; /*5Hz*/
  hSim.In.inputFreq2_Hz = 30.0f; /*30Hz*/

  /*Enable Filtre */
  hSim.fir_enable = 1;

  hSim.In.signal2_state = 1;

  /*Init FIR*/
  FIRFiltre_Init(Fir_FiltreCoeff);

  /*Init IIR*/
  IIRFiltre_Init(&hiir, APLFA_IIR);

  hSim.fft.fft_resolution = (float) 1000 / (SAMPLE_TIME_MS_TASK * FFT_LENGTH);

  while (1)
  {

    osDelay(SamplingTime); /*100hz*/

    /*Input STep get new sample (hSim.In.Type) -----------------------------------*/
    inputSignal = Get_NewSample(discret_times_ms);

    /*Increment Discret Time */
    discret_times_ms++;

    /*---FIltre Step --------------------------------------------------*/
    filt_out = filtre_Sample(inputSignal);

    /*Fill New Input_Sample in in_fft table */
    StoreNewSample(&in_fft, inputSignal);

    /*Fill New OutputSample in out_fft table */
    StoreNewSample(&out_fft, filt_out);

    if (out_fft.current_sample == FFT_LENGTH / 2)
    {
      uint32_t Process_buff = FIRST_HALF;
      /*Send HalfBuffer Process*/
      xQueueSend(xQueue_fft, (void* ) &Process_buff, 0);
    }

    if (out_fft.current_sample == 0)
    {
      uint32_t Process_buff = SECOND_HALF;
      /*Send HalfBuffer Process*/
      xQueueSend(xQueue_fft, (void* ) &Process_buff, 0);
    }

  } /*end loop*/

}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
static void StoreNewSample(FFT_TypeDef *hfft, float in)
{
  uint32_t nbre_sample = hfft->current_sample;

  /*Prepare Input Buffer*/
  hfft->Input[nbre_sample].real = in;
  hfft->Input[nbre_sample].imag = 0.0;

  hfft->current_sample++;

  if (nbre_sample >= FFT_LENGTH)
  {
    /*Send Second HalfBuffer Process*/
    hfft->current_sample = 0;

  }

}

/**
 * @brief  filtre_Sample
 * @retval Process Filtre depending hSim.fir / notch/iir ..

 */
static float filtre_Sample(float inputSignal)
{
  float out = 0.0;

  switch (hSim.filtre_Type)
  {

  case FIR_FILTRE:
  {
    /*FIR update*/
    out = FIRFiltre_Update( inputSignal);
    //out=lpfAcc.out;
    break;
  }

  case IIR_FILTRE:
  {
    /*IIR update*/
    IIRFiltre_Update(&hiir, inputSignal);
    out = hiir.out;
    break;
  }
  default:
  {
    while (1);
  }

  }

  return out;

}

#ifdef DEBUG
#define IN_SAMPLE_SIZE    500
float Tin[IN_SAMPLE_SIZE];
#endif

/**
 * @brief  Get_NewSample
 * @retval Get New Sample of an input Signal according to hSim.In.Type

 */
static float Get_NewSample(uint32_t sample_n)
{
  float inputSignal;

  /*sin(2* PI* Freq * n/SAMPLING_FREQ);         Sampling_Freq= SAMPLE_TIME_MS_TASK/1000.0f*/
  /*Calcualte discrete time */
  float discretTime = sample_n * SAMPLE_TIME_MS_TASK / 1000.0f;
  float inputSin;
  float inputSin2;

  /**
   *                            3ms == >  ~67 point
   * When SAMPLE_TIME_MS_TASK = 4ms == > SinWave Input need 50 point
   * When SAMPLE_TIME_MS_TASK = 5ms == > SinWave Input need 40 point
   * When SAMPLE_TIME_MS_TASK = 10ms == > SinWave Input need 20 point
   *
   */

  static uint16_t functionCounter = 0;

  if (functionCounter == 0)
  {
    uwTick = 0;

  }

  inputSin = hSim.In.Amp1 * arm_sin_f32(2.0f * M_PI * hSim.In.inputFreq1_Hz * (discretTime));
  inputSin2 = hSim.In.Amp2 * arm_sin_f32(2.0f * M_PI * hSim.In.inputFreq2_Hz * (discretTime));
  // inputSin3 = hSim.In.Amp3*arm_sin_f32(2.0f*M_PI*hSim.In.inputFreq3_Hz*(discretTime));

  /*Get Signal */
  inputSignal = inputSin;

#ifdef DEBUG  /*For debug the input Signal */
  if (functionCounter < IN_SAMPLE_SIZE)
  {
    Tin[functionCounter] = inputSignal;

    functionCounter++;
  }
#endif

  if (hSim.In.signal2_state != 0)
  {
    /**/
    inputSignal = inputSin + inputSin2;
  }

  return inputSignal;
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

