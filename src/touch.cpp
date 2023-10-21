#include "touch.h"

void Touch::mainMenu(Display * display)
{
    if (xin > 40 && xin < 280 && yin > 60 && yin < 110)
    {
        display->menu = 1;
        delay(50);
    }
    else if (xin > 40 && xin < 280 && yin > 120 && yin < 170)
    {
        display->menu = 2;
        delay(50);
    }
    else if (xin > 40 && xin < 280 && yin > 180 && yin < 230)
    {
        display->menu = 3;
        delay(50);
    }
}

Wave Touch::bottomMenu1(Display * display, Wave wave)
{
    if (xin >= 32 && xin <= 116 && yin > 217 && yin < 237)
    {
        display->menu = 0;
        delay(50);
    }
    else if (xin >= 120 && xin <= 204 && yin > 217 && yin < 237)
    {
        wave.resetWave();
    }
    else if (xin >= 208 && xin <= 292 && yin > 217 && yin < 237)
    {
        display->drawWaveOn = true;
        display->selectWaveOn = false;  
    }
    return wave;
}

void Touch::bottomMenu2(Display * display, Wave wave)
{
    if (xin >= 32 && xin <= 116 && yin > 217 && yin < 237)
    {
        display->menu = 0;
        delay(50);
    }
    else if (xin >= 208 && xin <= 292 && yin > 217 && yin < 237)
    {
        if (display->selectWaveOn) {
            display->selectWaveOn = false;  
        }
        else if (!display->selectWaveOn) {
            display->selectWaveOn = true;
            if (display->selectWaveType == 0)
            {
                wave.squareWave();
            } 
            else if (display->selectWaveType == 1)
            {
                wave.sineWave();
            }
            if (display->selectWaveType == 2)
            {
                wave.triangleWave();
            }
            if (display->selectWaveType == 3)
            {
                wave.sawtoothWave();
            }
        }
        delay(50);
    }
}

void Touch::bottomMenu3(Display * display)
{
    if (xin >= 32 && xin <= 116 && yin > 217 && yin < 237)
    {
        display->menu = 0;
        delay(50);
    }
    else if (xin >= 120 && xin <= 204 && yin > 217 && yin < 237)
    {
        display->attack = 75;
        display->decay = 75;
        display->sustain = 75;
        display->release = 75;
    }
    else if (xin >= 208 && xin <= 292 && yin > 217 && yin < 237)
    {
        if (display->envelopeOn) {
            display->envelopeOn = false;  
        }
        else if (!display->envelopeOn) {
            display->envelopeOn = true;
        }
        delay(50);
    }
}

Wave Touch::drawWave(Display * display, Wave wave)
{
    if (xin >= 11 && xin <= 313 && yin > 5 && yin < 211)
    {
        wave.updateWave(xin, yin);
    }
    wave = bottomMenu1(display, wave);
    return wave;
}

void Touch::selectWave(Display * display, Wave wave)
{
    if (xin >= 10 && xin <= 160 && yin >= 4 && yin <= 106)
    {
        display->selectWaveType = 0;
        if (display->selectWaveOn)
        {
            wave.squareWave();
        }
    }
    else if (xin >= 164 && xin <= 314 && yin >= 4 && yin <= 106)
    {
        display->selectWaveType = 1;
        if (display->selectWaveOn)
        {
            wave.sineWave();
        }
    }
    else if (xin >= 10 && xin <= 160 && yin >= 110 && yin <= 212)
    {
        display->selectWaveType = 2;
        if (display->selectWaveOn)
        {
            wave.triangleWave();
        }
    }
    else if (xin >= 164 && xin <= 314 && yin >= 110 && yin <= 212)
    {
        display->selectWaveType = 3;
        if (display->selectWaveOn)
        {
            wave.sawtoothWave();
        }
    }
    bottomMenu2(display, wave);
}

void Touch::adjustAttack(Display * display)
{
    if (yin > 4 && yin <= 32)
    {
        display->attack = 150;
    }
    else if (yin > 32 && yin < 184)
    {
        display->attack = 183 - yin;
    }
    else if (yin >= 184 && yin < 212)
    {
        display->attack = 0;
    }
}

void Touch::adjustDecay(Display * display)
{
    if (yin > 4 && yin <= 32)
    {
        display->decay = 150;
    }
    else if (yin > 32 && yin < 184)
    {
        display->decay = 183 - yin;
    }
    else if (yin >= 184 && yin < 212)
    {
        display->decay = 0;
    }
}

void Touch::adjustSustain(Display * display)
{
    if (yin > 4 && yin <= 32)
    {
        display->sustain = 150;
    }
    else if (yin > 32 && yin < 184)
    {
        display->sustain = 183 - yin;
    }
    else if (yin >= 184 && yin < 212)
    {
        display->sustain = 0;
    }
}

void Touch::adjustRelease(Display * display)
{
    if (yin > 4 && yin <= 32)
    {
        display->release = 150;
    }
    else if (yin > 32 && yin < 184)
    {
        display->release = 183 - yin;
    }
    else if (yin >= 184 && yin < 212)
    {
        display->release = 0;
    }
}

void Touch::envelope(Display * display)
{
    if (xin > 10 && xin < 85 && yin > 4 && yin < 212)
    {
        adjustAttack(display);
    }
    else if (xin > 86 && xin < 161 && yin > 4 && yin < 212)
    {
        adjustDecay(display);
    }
    else if (xin > 162 && xin < 237 && yin > 4 && yin < 212)
    {
        adjustSustain(display);
    }
    else if (xin > 238 && xin < 313 && yin > 4 && yin < 212)
    {
        adjustRelease(display);
    }
    bottomMenu3(display);
}

Wave Touch::processTouch(Display * display, Wave wave)
{
    if (display->menu == 0)
    {
        mainMenu(display);
    }
    else if (display->menu == 1)
    {
        wave = drawWave(display, wave);
    }
    else if (display->menu == 2)
    {
        selectWave(display, wave);
    }
    else if (display->menu == 3)
    {
        envelope(display);
    }
    return wave;
}

