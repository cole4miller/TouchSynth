#pragma once
#include <Arduino.h>
#include "display.h"
#include "wave.h"
#include "notes.h"

class Wave;

class Oscillator 
{
    public:
    double freq = C5;
    long numPoints = 1.0;
    int levelOut = 0;
    int currentStep = 0;
    int nextStep = 1;
    int seqStep = 0;
    short seqBPM = 300.0;
    double seqNotes[32] = {Eb5, Bb4, G4, Eb5, Bb4, G4, Eb5, Bb4, 
                           Db5, Bb4, F4, Db5, Bb4, F4, Db5, Bb4, 
                           Db5, Bb4, F4, Db5, Bb4, F4, Db5, Bb4,  
                           C5, Ab4, F4, C5, Ab4, F4, C5, Ab4};
    int numNotes = 32;

    int updateLevel(Wave wave, Display * display);
    int updateRate(Wave wave, Display * display);

    void sequencer();

    private:
    
};