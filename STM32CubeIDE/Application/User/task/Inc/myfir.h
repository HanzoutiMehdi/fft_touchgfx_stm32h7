/**
  ******************************************************************************
  * @file    fir.h
  * @author  Mehdi 
  * @date    21-July-2021
  * @brief   This header file contains the Fir prototype
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FIR_FILTRE_H
#define __FIR_FILTRE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>


/*Filtre Ordre */
#define NUM_TAPS                     81

#define FIR_FILTRE_LENGTH         NUM_TAPS



void FIRFiltre_Init(float *FiltreCoef);
float FIRFiltre_Update(float inp);



#ifdef __cplusplus
}
#endif

#endif /* __ACCELERO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
