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

}

void Wave::sineWave()
{

}

void Wave::triangleWave()
{

}

void Wave::sawtoothWave()
{

}