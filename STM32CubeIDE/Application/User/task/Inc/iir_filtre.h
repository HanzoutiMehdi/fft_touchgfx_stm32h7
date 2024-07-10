/**
  ******************************************************************************
  * @file    iir_filtre.h
  * @author  Mehdi 
  * @date    21-July-2021
  * @brief   This header file contains the Fir prototype
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IIR_FILTRE_H
#define __IIR_FILTRE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>




typedef struct{
	float alpha;
	uint8_t bufIndex;
	float out;
	
	
}IIRFiltre;


void  IIRFiltre_Init(IIRFiltre *iir, float alpha);
float IIRFiltre_Update(IIRFiltre *iir, float inp);



#ifdef __cplusplus
}
#endif

#endif /* __ACCELERO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
