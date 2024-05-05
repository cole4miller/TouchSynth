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

void Oscillator::fillWave(Wave wave, Display * display)
{
    if (display->drawWaveOn)
    {
        outWaveXstart = wave.customWaveXstart;
        outWaveXend = wave.customWaveXend;
        for (int i = 0; i < 303; i++)
        {
            outPointUsed[i] = wave.customPointUsed[i];
            outWaveY[i] = wave.customWaveY[i];
        }
    }
    else if (display->selectWaveOn)
    {
        outWaveXstart = wave.selectWaveXstart;
        outWaveXend = wave.selectWaveXend;
        for (int i = 0; i < 303; i++)
        {
            outPointUsed[i] = wave.selectPointUsed[i];
            outWaveY[i] = wave.selectWaveY[i];
        }
    }
    else
    {
        outWaveXstart = 302;  
        outWaveXend = 0;
        for (int i = 0; i < 303; i++)
        {
            outWaveY[i] = 0;
            outPointUsed[i] = false;
        }
    }

    uint16_t lastPointUsed = 0;

    for (int i = outWaveXstart; i < outWaveXend; i++)
    {
        if (outPointUsed[i])
        {
            lastPointUsed = i;
        }
        else
        {
            while (!outPointUsed[i])
            {
                i++;
            }
            float slope = ((float)outWaveY[i] - (float)outWaveY[lastPointUsed]) / ((float)i - (float)lastPointUsed);
            for (int j = 1; j < i - lastPointUsed; j++)
            {
                outWaveY[lastPointUsed + j] = (float)j * slope + (float)outWaveY[lastPointUsed];
                outPointUsed[lastPointUsed + j] = true;
            }
            lastPointUsed = i;
        }
    }
}

void Oscillator::fillBuffer(Wave wave, Display * display)
{
    bufferSteps = ((1.0 / freq) / (((double)updateTime) * (1e-6)));
    uint16_t waveSteps = outWaveXend - outWaveXstart;
    uint16_t index = 0;
    
    if (display->drawWaveOn || display->selectWaveOn)
    {
        for (int i = 0; i < bufferSteps; i++)
        {
            index = outWaveXstart + round(i * ((float)waveSteps / (float)bufferSteps));
            bufferOut[i] = (outWaveY[index] + 103.0) * (4095.0 / 206.0);
        }
    }
    else
    {
        for (int i = 0; i < bufferSteps; i++)
        {
            bufferOut[i] = 2048;
        }   
    }
}

void Oscillator::sequencer(Display * display)
{
    freq = noteArray[seqNotes[display->seqStep]];
    display->seqStep++;
    if (display->seqStep >= 8)
    {
        display->seqStep = 0;
    }
}