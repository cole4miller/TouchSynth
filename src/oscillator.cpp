#include "oscillator.h"

int Oscillator::updateLevel(Wave wave, Display * display)
{
    currentStep = nextStep;
    nextStep++;
    if (display->selectWaveOn)
    {
        levelOut = ((wave.selectWaveY[currentStep+wave.selectWaveXstart] / 103.0) * 127.0) + 128;
    }
    else if (display->drawWaveOn)
    {
        if (display->smoothOn)
        {
            levelOut = ((wave.smoothWaveY[currentStep+wave.smoothWaveXstart] / 103.0) * 127.0) + 128;
        }
        else if (!display->smoothOn)
        {
            levelOut = ((wave.customWaveY[currentStep+wave.customWaveXstart] / 103.0) * 127.0) + 128;
        }
    }
    else
    {
        levelOut = 0;
    }
    
    if (nextStep >= numPoints)
    {
        nextStep = 0;
    }
    return levelOut;
}

int Oscillator::updateRate(Wave wave, Display * display)
{
    if (display->selectWaveOn)
    {
        numPoints = wave.selectWaveXend - wave.selectWaveXstart;
    }
    else if (display->drawWaveOn)
    {
        if (display->smoothOn)
        {
            numPoints = wave.smoothWaveXend - wave.smoothWaveXstart;
        }
        else if (!display->smoothOn)
        {
            numPoints = wave.customWaveXend - wave.customWaveXstart;
        }
    }
    else
    {
        numPoints = 1.0;
    }
    return numPoints;
}

void Oscillator::sequencer(Display * display)
{
    freq = noteArray[seqNotes[display->seqStep]];
    display->seqStep++;
    if (display->seqStep >= 8)
    {
        display->seqStep = 0;
    }

    /*
    freq = seqNotes[seqStep];
    seqStep++;
    if (seqStep >= numNotes)
    {
        seqStep = 0;
    }
    */
}