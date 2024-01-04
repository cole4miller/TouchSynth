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
    short seqBPM = 75.0;
    //double seqNotes[32] = {Eb5, Bb4, G4, Eb5, Bb4, G4, Eb5, Bb4, 
    //                       Db5, Bb4, F4, Db5, Bb4, F4, Db5, Bb4, 
    //                       Db5, Bb4, F4, Db5, Bb4, F4, Db5, Bb4,  
    //                       C5, Ab4, F4, C5, Ab4, F4, C5, Ab4};
    //int numNotes = 32;

    int seqNotes[8] = {45, 45, 45, 45, 45, 45, 45, 45};

    double noteArray[85] = {
    C1, Db1, D1, Eb1, E1, F1, Gb1, G1, Ab1, A1, Bb1, B1note, 
    C2, Db2, D2, Eb2, E2, F2, Gb2, G2, Ab2, A2, Bb2, B2, 
    C3, Db3, D3, Eb3, E3, F3, Gb3, G3, Ab3, A3, Bb3, B3,
    C4, Db4, D4, Eb4, E4, F4, Gb4, G4, Ab4, A4, Bb4, B4, 
    C5, Db5, D5, Eb5, E5, F5, Gb5, G5, Ab5, A5, Bb5, B5, 
    C6, Db6, D6, Eb6, E6, F6, Gb6, G6, Ab6, A6, Bb6, B6, 
    C7, Db7, D7, Eb7, E7, F7, Gb7, G7, Ab7, A7, Bb7, B7, C8};

    int updateLevel(Wave wave, Display * display);
    int updateRate(Wave wave, Display * display);

    void sequencer(Display * display);

    private:
    
};