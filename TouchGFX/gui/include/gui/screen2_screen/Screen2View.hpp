#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void  handleTickEvent();
    virtual void FFT_InputCallback(AbstractDataGraph::GraphClickEvent value);
    virtual void FFT_OutputCallback(AbstractDataGraph::GraphClickEvent value);

    int TickCount;
    int fft_count=0;
protected:
};

#endif // SCREEN2VIEW_HPP
