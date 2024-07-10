/**
 ******************************************************************************
 * @file           : fft_task.c
 * @brief          : fft task
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "arm_math.h"
#include "conf.h"
#include  "FreeRTOS.h"
#include "queue.h"

/*Extern Global Variables-------------- */
extern SimuleTypeDef hSim;
extern QueueHandle_t xQueue_fft;

/*Private Variables ----------------------*/
static float32_t AmpResult_fft[FFT_LENGTH];
static float32_t Ampinp_fft[FFT_LENGTH];
static float32_t arm_sig_Input[FFT_LENGTH * 2];
static float32_t arm_sig_filt[FFT_LENGTH * 2];
static arm_cfft_radix4_instance_f32 arm_fft, arm_fft2; /* ARM CFFT module */


/*Public Varibales----------------------------- */
uint32_t uAmpIn_fft[FFT_LENGTH];  /*Shared with GUI*/
uint32_t uAmpResult_fft[FFT_LENGTH]; /*Shared with GUI*/
uint32_t MaxIndiceInput[3];   /*Shared with GUI*/
uint32_t MaxIndiceFiltred[3]; /*Shared with GUI */
FFT_TypeDef in_fft;
FFT_TypeDef out_fft;


/**
 * @brief  fft_task
 * @retval None
 */
void fft_task(void const *argument)
{
  uint32_t rx_mesage;

  //FFT RESOLUTION = 100 hz / 256  =0.4 Hz ===  > 5 Hz == > 12 Indice // 30Hz -->75

  /* Initialize the CFFT/CIFFT module, intFlag = 0, doBitReverse = 1 */
  arm_cfft_radix4_init_f32(&arm_fft, FFT_LENGTH, 0, 1);
  arm_cfft_radix4_init_f32(&arm_fft2, FFT_LENGTH, 0, 1);

  /*init struct*/
  hSim.in_fft = &in_fft;
  hSim.out_fft = &out_fft;

  while (1)
  {

    if (xQueueReceive(xQueue_fft, &(rx_mesage), 20) == pdPASS)
    {
      if (rx_mesage == SECOND_HALF)
      {

        for (uint32_t i = 256, j = 128; i < (FFT_LENGTH * 2); i++, j++)
        {

          arm_sig_Input[i] = in_fft.Input[j].real;
          arm_sig_filt[i] = out_fft.Input[j].real;
          arm_sig_filt[i + 1] = out_fft.Input[j].imag;
          arm_sig_Input[i + 1] = in_fft.Input[j].imag;
          i++;
        }
      }
      else
      {

        for (uint32_t i = 0, j = 0; i < FFT_LENGTH; i++, j++)
        {

          arm_sig_Input[i] = in_fft.Input[j].real;
          arm_sig_Input[i + 1] = in_fft.Input[j].imag;
          arm_sig_filt[i] = out_fft.Input[j].real;
          arm_sig_filt[i + 1] = out_fft.Input[j].imag;
          i++;

        }
      }

      /*Calcul amplitud when buffer is already processed */
      if (rx_mesage == SECOND_HALF)
      {
        /* Process the data through the CFFT/CIFFT module */
        arm_cfft_radix4_f32(&arm_fft, arm_sig_Input);

        arm_cfft_radix4_f32(&arm_fft2, arm_sig_filt);

        arm_cmplx_mag_f32(arm_sig_Input, (float*) Ampinp_fft, FFT_LENGTH);

        for (uint32_t i = 0; i < FFT_LENGTH; i++)
        {
          uAmpIn_fft[i] = Ampinp_fft[i];
        }

        arm_cmplx_mag_f32(arm_sig_filt, (float*) AmpResult_fft, FFT_LENGTH);

        for (uint32_t i = 0; i < FFT_LENGTH; i++)
        {
          uAmpResult_fft[i] = AmpResult_fft[i];
        }

        /*Calculate MaxIndice */
        findMaxIndices(uAmpIn_fft, FFT_LENGTH / 2, MaxIndiceInput);
        findMaxIndices(uAmpResult_fft, FFT_LENGTH / 2, MaxIndiceFiltred);
      }
    }

  }

}

/***
 *
 */
void findMaxIndices(const uint32_t *uAmpResult, size_t size, uint32_t *maxIndices)
{
  // Temporary variables
  uint32_t tempMax = 0, tempIndex = 0;
  uint8_t found = 0;
  typedef enum
  {
    FETCH1 = 0,
    FETCH2 = 1,
    FETCH3 = 2
  } tState;
#define THRESHOLD_VALUE  1000
  tState state = FETCH1;
  maxIndices[0] = 0;
  maxIndices[1] = 0;
  maxIndices[2] = 0;

  while (1)
  {
    switch (state)
    {
    case FETCH1:
    {
      maxIndices[0] = 0;
      tempMax = uAmpResult[0];
      found = 0;
      for (size_t j = 1; j < size; j++)
      {
        if ((uAmpResult[j] > tempMax) && (uAmpResult[j] > THRESHOLD_VALUE))
        {
          tempMax = uAmpResult[j];
          tempIndex = j;
          found = 1;
        }
      }
      if (found == 1)
      {
        maxIndices[0] = tempIndex;
        state = FETCH2;
      }
      else
      {
        return;
      }
      break;
    }

    case FETCH2:
    {
      maxIndices[1] = 0;
      tempMax = uAmpResult[tempIndex + 3];
      found = 0;
      for (size_t j = tempIndex + 3; j < size; j++)
      {
        if ((uAmpResult[j] > tempMax) && (uAmpResult[j] > THRESHOLD_VALUE))
        {
          tempMax = uAmpResult[j];
          tempIndex = j;
          found = 1;
        }
        else
        {
          if (found == 1)
            break;
        }

      }
      if (found == 1)
      {
        maxIndices[1] = tempIndex;
        state = FETCH3;
      }
      else
      {
        return;
      }

      break;
    }
    case FETCH3:
    {
      maxIndices[2] = 0;
      tempMax = uAmpResult[tempIndex + 3];
      found = 0;
      for (size_t j = tempIndex + 3; j < size; j++)
      {
        if ((uAmpResult[j] > tempMax) && (uAmpResult[j] > THRESHOLD_VALUE))
        {
          tempMax = uAmpResult[j];
          tempIndex = j;
          found = 1;
        }
      }
      if (found == 1)
      {
        maxIndices[2] = tempIndex;
      }
      return;

      break;
    }
    }

  }

}

