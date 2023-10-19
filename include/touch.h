#pragma once
#include <Arduino.h>
#include "display.h"
#include "XPT2046_Touchscreen.h"

class Touch 
{
    public:
    uint16_t xin = 0;           // Values 0 - 319
    uint16_t yin = 0;           // Values 0 - 239

    void processTouch(Display * display);
    private:
    void mainMenu(Display * display);
    void bottomMenu1(Display * display);
    void bottomMenu2(Display * display);
    void bottomMenu3(Display * display);
    void drawWave(Display * display);
    void selectWave(Display * display);
    void adjustAttack(Display * display);
    void adjustDecay(Display * display);
    void adjustSustain(Display * display);
    void adjustRelease(Display * display);
    void envelope(Display * display);
};