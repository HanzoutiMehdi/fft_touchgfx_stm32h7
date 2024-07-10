
/**
  ******************************************************************************
  * @file           : fir_filtre
  * @brief          :
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "myfir.h"
#include "arm_math.h"





/*Arm fir init */
#define BLOCK_SIZE            1
static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];
static arm_fir_instance_f32 S;



/**
  * @brief  TFIRFiltre_Init
  * @retval
  */
void FIRFiltre_Init(float *FiltreCoef)
{

	  /* Call FIR init function to initialize the instance structure. */
	  arm_fir_init_f32(&S, FIR_FILTRE_LENGTH, (float32_t *)FiltreCoef, &firStateF32[0], 1);

}

/**
  * @brief  FIRFiltre_Update
  * @retval int
  */
float FIRFiltre_Update(float inp)
{
	float outputF32;

  arm_fir_f32(&S, &inp, &outputF32 , 1);


  return outputF32;

}









/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
