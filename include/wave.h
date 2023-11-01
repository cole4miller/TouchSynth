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
    
    // custom drawn wave
    uint16_t customWaveXstart = 302;  // x values from 0 to 302
    uint16_t customWaveXend = 0;
    bool customPointUsed[303];
    int customWaveY[303];

    // smooth custom wave
    uint16_t smoothWaveXstart = 302;  // x values from 0 to 302
    uint16_t smoothWaveXend = 0;
    bool smoothPointUsed[303];
    int smoothWaveY[303];
    
    // premade wave forms
    uint16_t selectWaveXstart = 302;  // x values from 0 to 302
    uint16_t selectWaveXend = 0;
    bool selectPointUsed[303];
    int selectWaveY[303];

    // preview wave forms on load screen
    uint16_t previewWaveXstart = 302;  // x values from 0 to 302
    uint16_t previewWaveXend = 0;
    bool previewPointUsed[303];
    int previewWaveY[303];

    int bpm = 100;

    void updateWave(uint16_t xin, uint16_t yin);
    void resetWave();
    Wave smoothWave(Wave waveIn, uint16_t smoothLevel);
    void confirmLoad();
    void squareWave();
    void sineWave();
    void triangleWave();
    void sawtoothWave();

    private:

};