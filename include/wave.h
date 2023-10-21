#pragma once
#include <Arduino.h>
#include "display.h"
#include "touch.h"
#include "XPT2046_Touchscreen.h"

class Wave 
{
    public:
    uint16_t waveXstart = 302;  // x values from 0 to 302
    uint16_t waveXend = 0;
    bool pointUsed[303];        // Bool for whether each x value is drawn
    int waveY[303];             // Wave y values array, -103 <= y <= 103
    //uint16_t xin = 0;           // Values 0 - 319
    //uint16_t yin = 0;           // Values 0 - 239

    void updateWave(uint16_t xin, uint16_t yin);
    void resetWave();
    void squareWave();
    void sineWave();
    void triangleWave();
    void sawtoothWave();

    private:

};