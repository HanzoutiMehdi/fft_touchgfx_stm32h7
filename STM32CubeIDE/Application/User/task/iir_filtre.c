
/**
  ******************************************************************************
  * @file           : iir filtre
  * @brief          :
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "iir_filtre.h"



//static float FIR_IMPULSE_RESPONSE[FIR_FILTRE_LENGTH];

/**
  * @brief  TFIRFiltre_Init
  * @retval
  */
void  IIRFiltre_Init(IIRFiltre *iir, float alpha)
{
    /*chcek filtre coefficient bounds ans store*/
	if (alpha < 0.0f)
	{
		iir->alpha=0.0f;
	}
	else if (alpha> 1.0f)
	{
		iir->alpha=1.0f;
	}
	else
	{
		iir->alpha=alpha;

	}


	/*Clear output */

	iir->out = 0.0f;



}

/**
  * @brief  RFiltre_Update
  * @retval int
  */
float IIRFiltre_Update(IIRFiltre *iir, float inp)
{

  /*Compute y[n]= (1-aplfa)x[n]+ aplpha*y[n-1]*/
	iir->out=(1.0f- iir->alpha)*inp + iir->alpha * iir->out;



   return iir->out;

}








