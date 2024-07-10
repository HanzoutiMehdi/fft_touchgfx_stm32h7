#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent(void);

    virtual void SliderFreqCalback(int value);

    virtual void AmplitudeCalback(int value);

    virtual void Signal2_cfg(void);

    virtual void Signal3_cfg(void);

    virtual void ConfigCalback(void);

    int tickCount;
protected:
};

#endif // SCREEN1VIEW_HPP
