#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "display.h"
#include "wave.h"
#include "XPT2046_Touchscreen.h"

class Display;
class Wave;
class Touch;
class Memory 
{
    public:
    File myFile;

    uint16_t memWaveXstart = 302;  // x values from 0 to 302
    uint16_t memWaveXend = 0;
    bool memPointUsed[303];        // Bool for whether each x value is drawn
    int memWaveY[303];             // Wave y values array, -103 <= y <= 103

    void saveFile(int file, Wave wave);
    Wave loadFile(int file, Wave wave);

    // File format:
    // waveXstart,
    // waveXend,
    // pointUsed[0],
    // ...
    // pointUsed[302],
    // waveY[0],
    // ...
    // wavey[302],


    private:
    void saveContent(Wave wave, char filename[]);
    Wave loadContent(Wave wave, char filename[]);
};