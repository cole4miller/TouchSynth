#include "wave.h"

void Wave::updateWave(uint16_t xin, uint16_t yin)
{
    if (!drawLR)
    {
        waveY[xin - 11] = (108 - yin);
        pointUsed[xin - 11] = true;
        
        if ((xin - 11) < waveXstart)
        {
            waveXstart = xin - 11;
        }

        if ((xin - 11) > waveXend)
        {
            waveXend = xin - 11;
        }
    }
    else
    {
        if ((xin - 11) > waveXend)
        {
            if ((xin - 11) < waveXstart)
            {
                waveXstart = xin - 11;
            } 
            waveXend = xin - 11;
            waveY[xin - 11] = (108 - yin);
            pointUsed[xin - 11] = true;
        }
    }
}

void Wave::resetWave()
{
    for (int i = 0; i < 303; i++)
    {
        waveY[i] = 0;
        smoothWaveY[i] = 0;
        pointUsed[i] = false;
        smoothPointUsed[i] = false;
    }
    waveXstart = 302;  
    waveXend = 0;
    smoothWaveXstart = 302;  
    smoothWaveXend = 0;
}

Wave Wave::smoothWave(Wave waveIn, uint16_t smoothLevel)
{
    waveIn.smoothWaveXstart = waveIn.waveXstart;
    waveIn.smoothWaveXend = waveIn.waveXend;
    int firstPoint = waveIn.smoothWaveXstart;
    waveIn.smoothPointUsed[firstPoint] = true;
    waveIn.smoothWaveY[firstPoint] = waveIn.waveY[firstPoint];
    int pointCount = 0;
    for (int i = firstPoint; i <= waveIn.waveXend; i++)
    {
        if (waveIn.pointUsed[i])
        {
            waveIn.smoothPointUsed[i] = true;
            waveIn.smoothWaveY[i] = waveIn.waveY[i];
            pointCount++;
        }
    }
    if (pointCount < 6)
    {
        return waveIn;
    }

    int secondPoint = firstPoint + 1;
    int thirdPoint = 0;
    int fourthPoint = 0;
    int fifthPoint = 0;
    int sixthPoint = 0;

    while (!waveIn.pointUsed[secondPoint])
    {
        secondPoint++;
    }
    if (waveIn.pointUsed[secondPoint])
    {
        waveIn.smoothPointUsed[secondPoint] = true;
    }
    
    if (waveIn.smoothPointUsed[secondPoint] == true && secondPoint < 302)
    {
        thirdPoint = secondPoint + 1;
        while (!waveIn.pointUsed[thirdPoint])
        {
            thirdPoint++;
        }
        if (waveIn.pointUsed[thirdPoint])
        {
            waveIn.smoothPointUsed[thirdPoint] = true;
        }
    }
    
    if (waveIn.smoothPointUsed[thirdPoint] == true && thirdPoint < 302)
    {
        fourthPoint = thirdPoint + 1;
        while (!waveIn.pointUsed[fourthPoint])
        {
            fourthPoint++;
        }
        if (waveIn.pointUsed[fourthPoint])
        {
            waveIn.smoothPointUsed[fourthPoint] = true;
        }
    }

    if (waveIn.smoothPointUsed[fourthPoint] == true && fourthPoint < 302)
    {
        fifthPoint = fourthPoint + 1;
        while (!waveIn.pointUsed[fifthPoint])
        {
            fifthPoint++;
        }
        if (waveIn.pointUsed[fifthPoint])
        {
            waveIn.smoothPointUsed[fifthPoint] = true;
        }
    }

    if (waveIn.smoothPointUsed[fifthPoint] == true && fifthPoint < 302)
    {
        sixthPoint = fifthPoint + 1;
        while (!waveIn.pointUsed[sixthPoint])
        {
            sixthPoint++;
        }
        if (waveIn.pointUsed[sixthPoint])
        {
            waveIn.smoothPointUsed[sixthPoint] = true;
        }
    }

    if (smoothLevel == 1 || (pointCount < 5 && pointCount > 3))
    {
        for (int i = secondPoint + 1; i <= waveIn.smoothWaveXend; i++)
        {
            if (waveIn.pointUsed[i])
            {
                waveIn.smoothWaveY[secondPoint] = (waveIn.waveY[firstPoint] + waveIn.waveY[secondPoint] + waveIn.waveY[i]) / 3.0;
                waveIn.smoothPointUsed[secondPoint] = true;
                firstPoint = secondPoint;
                secondPoint = i;
            }
        }
        waveIn.smoothPointUsed[secondPoint] = true;
        waveIn.smoothWaveY[secondPoint] = waveIn.waveY[secondPoint];
    }
    else if (smoothLevel == 2 && pointCount >= 5 && pointCount < 7)
    {
        waveIn.smoothWaveY[secondPoint] = (waveIn.waveY[firstPoint] + waveIn.waveY[secondPoint] + waveIn.waveY[thirdPoint]) / 3.0;
        for (int i = fourthPoint + 1; i <= waveIn.smoothWaveXend; i++)
        {
            if (waveIn.pointUsed[i])
            {
                waveIn.smoothWaveY[thirdPoint] = (waveIn.waveY[firstPoint] + waveIn.waveY[secondPoint] + 
                waveIn.waveY[thirdPoint] + waveIn.waveY[fourthPoint] + waveIn.waveY[i]) / 5.0;
                waveIn.smoothPointUsed[thirdPoint] = true;
                firstPoint = secondPoint;
                secondPoint = thirdPoint;
                thirdPoint = fourthPoint;
                fourthPoint = i;
            }
        }
        waveIn.smoothWaveY[thirdPoint] = (waveIn.waveY[secondPoint] + waveIn.waveY[thirdPoint] + waveIn.waveY[fourthPoint]) / 3.0;
        waveIn.smoothPointUsed[thirdPoint] = true;
        waveIn.smoothWaveY[fourthPoint] = waveIn.waveY[fourthPoint];
        waveIn.smoothPointUsed[fourthPoint] = true;
    }
    else if (smoothLevel == 2 && pointCount >= 7)
    {
        waveIn.smoothWaveY[secondPoint] = (waveIn.waveY[firstPoint] + waveIn.waveY[secondPoint] + waveIn.waveY[thirdPoint]) / 3.0;
        waveIn.smoothWaveY[thirdPoint] = (waveIn.waveY[firstPoint] + waveIn.waveY[secondPoint] + 
                waveIn.waveY[thirdPoint] + waveIn.waveY[fourthPoint] + waveIn.waveY[fifthPoint]) / 5.0;
        for (int i = sixthPoint + 1; i <= waveIn.smoothWaveXend; i++)
        {
            if (waveIn.pointUsed[i])
            {
                waveIn.smoothWaveY[fourthPoint] = (waveIn.waveY[firstPoint] + waveIn.waveY[secondPoint] + 
                waveIn.waveY[thirdPoint] + waveIn.waveY[fourthPoint] + waveIn.waveY[fifthPoint] +
                waveIn.waveY[sixthPoint] + waveIn.waveY[i]) / 7.0;
                waveIn.smoothPointUsed[fourthPoint] = true;
                firstPoint = secondPoint;
                secondPoint = thirdPoint;
                thirdPoint = fourthPoint;
                fourthPoint = fifthPoint;
                fifthPoint = sixthPoint;
                sixthPoint = i;
            }
        }
        waveIn.smoothWaveY[fourthPoint] = (waveIn.waveY[secondPoint] + waveIn.waveY[thirdPoint] + waveIn.waveY[fourthPoint] +
        waveIn.waveY[fifthPoint] + waveIn.waveY[sixthPoint]) / 5.0;
        waveIn.smoothPointUsed[fourthPoint] = true;
        waveIn.smoothWaveY[fifthPoint] = (waveIn.waveY[fourthPoint] + waveIn.waveY[fifthPoint] + waveIn.waveY[sixthPoint]) / 3.0;
        waveIn.smoothPointUsed[fifthPoint] = true;
        waveIn.smoothWaveY[sixthPoint] = waveIn.waveY[sixthPoint];
        waveIn.smoothPointUsed[sixthPoint] = true;
    }
    return waveIn;
}

void Wave::confirmLoad()
{
    waveXstart = previewWaveXstart;
    customWaveXstart = previewWaveXstart;
    waveXend = previewWaveXend;
    customWaveXend = previewWaveXend;
    for (int i = 0; i < 303; i++)
    {
        pointUsed[i] = previewPointUsed[i];
        customPointUsed[i] = previewPointUsed[i];
        waveY[i] = previewWaveY[i];
        customWaveY[i] = previewWaveY[i];
    }
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