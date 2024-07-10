/*
  ******************************************************************************
  * @file         fft_task.h
  * @brief        This file provides
  * @Author       mhanzout
  * @date         Jul 10, 2024
  ******************************************************************************
  ******************************************************************************
                            EMBEDDED LOW LEVEL SOFWARE
  ******************************************************************************
  ******************************************************************************
 */
#ifndef APPLICATION_USER_TASK_INC_FFT_TASK_H_
#define APPLICATION_USER_TASK_INC_FFT_TASK_H_

#include "conf.h"

extern uint32_t uAmpIn_fft[FFT_LENGTH];  /*Shared with GUI*/
extern uint32_t uAmpResult_fft[FFT_LENGTH]; /*Shared with GUI*/
extern uint32_t MaxIndiceInput[3];   /*Shared with GUI*/
extern uint32_t MaxIndiceFiltred[3]; /*Shared with GUI */
extern FFT_TypeDef in_fft;
extern FFT_TypeDef out_fft;

void fft_task(void const *argument);
void findMaxIndices(const uint32_t *uAmpResult, size_t size, uint32_t *maxIndices);



#endif /* APPLICATION_USER_TASK_INC_FFT_TASK_H_ */
