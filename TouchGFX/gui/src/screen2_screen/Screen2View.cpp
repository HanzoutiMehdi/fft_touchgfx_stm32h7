#include <gui/screen2_screen/Screen2View.hpp>
#include "conf.h"

extern float inputSignal;
extern float filt_out;

#define MAX_GRAPH           152

extern uint32_t uAmpIn_fft[FFT_LENGTH];
extern uint32_t uAmpResult_fft[FFT_LENGTH];

extern uint32_t  MaxIndiceInput[3];
extern uint32_t  MaxIndiceFiltred[3];


#define   SAMPLING_FREQ          (float)1000/SAMPLE_TIME_MS_TASK    /*100Hz*/
#define   FFT_RESOLUTION        (float)SAMPLING_FREQ/FFT_LENGTH


Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
    //camp1.setVisible(false);
    camp2.setVisible(false);
    camp3.setVisible(false);

    campO1.setVisible(false);
    campO2.setVisible(false);
    campO3.setVisible(false);

    cfreq2.setVisible(false);
    cfreq3.setVisible(false);

    cfreq2_1.setVisible(false);

    cfreq3_1.setVisible(false);



}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}



void Screen2View::handleTickEvent()
{
float Attenuation1=0;
float Attenuation2=0;
float Attenuation3=0;

   if (fft_count>=(FFT_LENGTH/2))
   {
	   fft_count=0;
   }

   graph1.addDataPoint((float)(FFT_RESOLUTION*fft_count), (float)uAmpIn_fft[fft_count]);

   graph2.addDataPoint((float)(FFT_RESOLUTION*fft_count), (float)uAmpResult_fft[fft_count]);



   Attenuation1=  (float)uAmpResult_fft[MaxIndiceInput[0]]*100 /(float)uAmpIn_fft[MaxIndiceInput[0]];

   Attenuation2=  (float)uAmpResult_fft[MaxIndiceInput[1]]*100 /(float)uAmpIn_fft[MaxIndiceInput[1]];

   Attenuation3=  (float)uAmpResult_fft[MaxIndiceInput[1]]*100 /(float)uAmpIn_fft[MaxIndiceInput[2]];


   /*Set Amp1 */
	Unicode::snprintf(amp1Buffer, 8, "%d",  uAmpIn_fft[MaxIndiceInput[0]]);
    amp1.invalidate();

	Unicode::snprintf(freq1Buffer, 8, "%d", (uint32_t) (MaxIndiceInput[0]*1));
	cfreq1.invalidate();






    if (MaxIndiceInput[1] !=0)
    {
     	if (camp2.isVisible() == false)
         	{
         		camp2.setVisible(true);
         	}

	 Unicode::snprintf(amp2Buffer, 8, "%d",  uAmpIn_fft[MaxIndiceInput[1]]);
     amp2.invalidate();

     Unicode::snprintf(freq2Buffer, 8, "%d",  MaxIndiceInput[1]*1);
 	cfreq2.invalidate();





    }
    else
   {
   	 Unicode::snprintf(amp2Buffer, 8, "%d",  0);
        amp2.invalidate();
    	if (camp2.isVisible() == true)
     	{
     		camp2.setVisible(false);
     	}

    }
    if (MaxIndiceInput[2]!=0)
    {
    	if (camp3.isVisible() == false)
    	{
    		camp3.setVisible(true);
    	}

	Unicode::snprintf(amp3Buffer, 8, "%d",  uAmpIn_fft[MaxIndiceInput[2]]);
    amp3.invalidate();
    Unicode::snprintf(freq3Buffer, 8, "%d",  MaxIndiceInput[2]*1);
   	cfreq3.invalidate();


    }
    else
    {
    	Unicode::snprintf(amp3Buffer, 8, "%d",  0);
        amp3.invalidate();

    	if (camp3.isVisible() == true)
    	{
    		camp3.setVisible(false);
    	}
    }


    if (MaxIndiceFiltred[0]!=0)
    {
    	if (campO1.isVisible() == false)
            	{
            	  campO1.setVisible(true);
            	}
    	if (cfreq1_1.isVisible()== false)
    	{
    		cfreq1_1.setVisible(true);
    	}

       	/*Filtre Out */
	 Unicode::snprintf(amp1_1Buffer, 8, "%d",  uAmpResult_fft[MaxIndiceFiltred[0]]);
	 amp1_1.invalidate();

	 /*Attenuation */
	 Unicode::snprintf(freq1_1Buffer, 8, "%d", (int)Attenuation1);
	 freq1_1.invalidate();


    }
    else
    {
    	if (campO1.isVisible() == true)
        	{
        	  campO1.setVisible(false);
        	}

    	if (cfreq1_1.isVisible()== true)
    	{
    		cfreq1_1.setVisible(false);
    	}
    }
	 if (MaxIndiceFiltred[1]!=0)
	 {
	   if (campO2.isVisible() == false)
	 	{
			campO2.setVisible(true);
		}

   	if (cfreq2_1.isVisible()== false)
   	{
   		cfreq2_1.setVisible(true);
   	}

	   Unicode::snprintf(amp2_1Buffer, 8, "%d",  uAmpResult_fft[MaxIndiceFiltred[1]]);
	   amp2_1.invalidate();

		 /*Attenuation */
		 Unicode::snprintf(freq2_1Buffer, 8, "%d", (int)Attenuation2);
		 freq2_1.invalidate();


	 }
	 else
	 {
		   Unicode::snprintf(amp2_1Buffer, 8, "%d",  0);
		   amp2_1.invalidate();

			if (campO2.isVisible() == true)
			{
		       campO2.setVisible(false);
			}
		  	if (cfreq2_1.isVisible()== true)
		   	{
		   		cfreq2_1.setVisible(false);
		   	}



	 }

	   if (MaxIndiceFiltred[2]!=0)
	   {
		   if (campO3.isVisible() == false)
		  	 	{
		  			campO3.setVisible(true);
		  		}
		   Unicode::snprintf(amp3_1Buffer, 8, "%d",  uAmpResult_fft[MaxIndiceFiltred[2]]);
	    amp3_1.invalidate();
	   }
	   else
	   {
		 Unicode::snprintf(amp3_1Buffer, 8, "%d",  0);
	    amp3_1.invalidate();

			if (campO3.isVisible() == true)
			{
				campO3.setVisible(false);
			}

	   }






   fft_count++;


	TickCount++;


}


void Screen2View::FFT_InputCallback(AbstractDataGraph::GraphClickEvent value)
{
	TickCount++;
}
void Screen2View::FFT_OutputCallback(AbstractDataGraph::GraphClickEvent value)
{
	TickCount++;
}






