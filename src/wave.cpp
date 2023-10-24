#include "wave.h"

void Wave::updateWave(uint16_t xin, uint16_t yin)
{
    waveY[xin - 11] = (108 - yin);
    pointUsed[xin - 11] = true;
    Serial.print("x = ");
    Serial.print(xin);
    Serial.print(", y = ");
    Serial.println(yin);
    
    if ((xin - 11) < waveXstart)
    {
        waveXstart = xin - 11;
    }

    if ((xin - 11) > waveXend)
    {
        waveXend = xin - 11;
    }
}

void Wave::resetWave()
{
    for (int i = 0; i < 303; i++)
    {
        waveY[i] = 0;
        pointUsed[i] = false;
    }
    waveXstart = 302;  
    waveXend = 0;
}

void Wave::squareWave()
{
    selectWaveXstart = 50;
    selectWaveXend = 249;
    for (int i = 50; i < 150; i++) 
    {
        selectPointUsed[i] = true;
        selectWaveY[i] = 75;
    }
    for (int i = 150; i < 250; i++) 
    {
        selectPointUsed[i] = true;
        selectWaveY[i] = -75;
    }

}

void Wave::sineWave()
{
    selectWaveXstart = 50;
    selectWaveXend = 249;
    for (int i = 50; i < 250; i++) 
    {
        selectPointUsed[i] = true;
        selectWaveY[i] = 75 * sin(2.0 * M_PI * (i - 50.0) / 200.0);
    }
}

void Wave::triangleWave()
{
    selectWaveXstart = 50;
    selectWaveXend = 249;
    for (int i = 50; i < 100; i++) 
    {
        selectPointUsed[i] = true;
        selectWaveY[i] = 75.0 * (i - 50.0) / 50.0;
    }
    for (int i = 100; i < 200; i++) 
    {
        selectPointUsed[i] = true;
        selectWaveY[i] = 75.0 + (-75.0 * ((i - 100.0) / 50.0));
    }
    for (int i = 200; i < 250; i++) 
    {
        selectPointUsed[i] = true;
        selectWaveY[i] = -75.0 + (75.0 * (i - 200.0) / 50.0);
    }
}

void Wave::sawtoothWave()
{
    selectWaveXstart = 50;
    selectWaveXend = 249;
    for (int i = 50; i < 250; i++) 
    {
        selectPointUsed[i] = true;
        selectWaveY[i] = -75.0 + (75.0 * (i - 50.0) / 100.0);
    }
}