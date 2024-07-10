#include <gui/screen1_screen/Screen1View.hpp>
#include "conf.h"
#include "stm32h7xx_hal.h"
extern float inputSignal;
extern float filt_out;
extern SimuleTypeDef  hSim;

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    for (uint8_t i=0;i<4;i++)
    {
    	Freq_vale_2_2_1Buffer1[i]=0;
    	Freq_vale_2_2_1Buffer2[i]=0;
    }
	Freq_vale_2_2_1.invalidate();


    Screen1ViewBase::setupScreen();
}

void Screen1View::ConfigCalback()
{
    for (uint8_t i=0;i<4;i++)
    {
    	Freq_vale_2_2_1Buffer1[i]=0;
    	Freq_vale_2_2_1Buffer2[i]=0;
    }


	Unicode::snprintf(Freq_vale_2_2_1Buffer1, 4, "%d", hSim.In.Amp1);
	Freq_vale_2_2_1.invalidate();


    Unicode::snprintf(Freq_vale_2_2_1Buffer2, 4, "%d", (uint32_t)hSim.In.inputFreq1_Hz);
    Freq_vale_2_2_1.invalidate();

}


void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

uint32_t ScreenTiming[5];//FPS = 17ms

void Screen1View::handleTickEvent()
{
	Sinput.addDataPoint(inputSignal);

	OutSign.addDataPoint(filt_out);

   if (tickCount<5)
   {
	   ScreenTiming[tickCount]=HAL_GetTick();

   }

if (tickCount % 50)
{
	Unicode::snprintf(Freq_vale_2_2_1Buffer1, 4, "%d", hSim.In.Amp1);
	Freq_vale_2_2_1.invalidate();


    Unicode::snprintf(Freq_vale_2_2_1Buffer2, 4, "%d", (uint32_t)hSim.In.inputFreq1_Hz);
    Freq_vale_2_2_1.invalidate();
}


	tickCount++;
}


void Screen1View::SliderFreqCalback(int value)
{

	hSim.In.inputFreq1_Hz=value;

    Unicode::snprintf(Freq_vale_2_2_1Buffer2, 4, "%d", value);
    Freq_vale_2_2_1.invalidate();

}

void Screen1View::AmplitudeCalback(int value)
{
	hSim.In.Amp1=value;


    Unicode::snprintf(Freq_vale_2_2_1Buffer1, 4, "%d", value);
    Freq_vale_2_2_1.invalidate();


}

void Screen1View::Signal2_cfg(void)
{
	hSim.In.signal2_state ^= 1;


}
void Screen1View::Signal3_cfg(void)
{
	hSim.In.signal3_state ^= 1;
}



