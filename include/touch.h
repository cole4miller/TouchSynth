#pragma once
#include <Arduino.h>
#include "display.h"
#include "wave.h"
#include "memory.h"
#include "oscillator.h"
#include "XPT2046_Touchscreen.h"

class Display;
class Wave;
class Memory;
class Oscillator;
class Touch 
{
    public:
    uint16_t xin = 0;           // Values 0 - 319
    uint16_t yin = 0;           // Values 0 - 239

    Wave processTouch(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator);

    private:
    void mainMenu(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator);
    Wave bottomMenu1(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator);
    Wave bottomMenu2(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator);
    void bottomMenu3(Display * display, Wave wave, Memory sdcard);
    Wave bottomMenu4(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator);
    void bottomMenu5(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator);
    Wave drawWave(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator);
    Wave selectWave(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator);
    void settings(Display * display, Wave wave, Memory sdcard);
    Wave saveWave(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator);
    void sequencer(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator);
    void tuneInput(Display * display, Wave wave, Memory sdcard);
    void seqGateAdjust(Display * display, Wave wave, Memory sdcard);
    void triggerSens(Display * display, Wave wave, Memory sdcard);
    void credits(Display * display, Wave wave, Memory sdcard);
};