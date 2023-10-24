#pragma once
#include <Arduino.h>
#include "display.h"
#include "wave.h"
#include "XPT2046_Touchscreen.h"

class Display;
class Wave;
class Touch 
{
    public:
    uint16_t xin = 0;           // Values 0 - 319
    uint16_t yin = 0;           // Values 0 - 239

    Wave processTouch(Display * display, Wave wave);

    private:
    void mainMenu(Display * display);
    Wave bottomMenu1(Display * display, Wave wave);
    Wave bottomMenu2(Display * display, Wave wave);
    void bottomMenu3(Display * display);
    Wave drawWave(Display * display, Wave wave);
    Wave selectWave(Display * display, Wave wave);
    void adjustAttack(Display * display);
    void adjustDecay(Display * display);
    void adjustSustain(Display * display);
    void adjustRelease(Display * display);
    void envelope(Display * display);
};