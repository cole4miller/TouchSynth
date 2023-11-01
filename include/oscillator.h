#pragma once
#include <Arduino.h>
#include "display.h"
#include "wave.h"
#include "notes.h"

class Wave;

class Oscillator 
{
    public:
    double freq = C1;
    long numPoints = 1;
    int levelOut = 0;
    int currentStep = 0;
    int nextStep = 1;
    int seqStep = 0;
    double seqNotes[6] = {E4, Db5, Db4, E4, A5, A4};

    int updateLevel(Wave wave, Display * display);
    int updateRate(Wave wave, Display * display);

    void sequencer();

    private:
    
};