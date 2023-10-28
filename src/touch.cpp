#include "touch.h"

void Touch::mainMenu(Display * display, Wave wave, Memory sdcard)
{
    if (xin > 10 && xin < 160 && yin > 108 && yin < 140)
    {
        display->menu = 1;
        display->changeScreen(wave, sdcard);
    }
    else if (xin > 10 && xin < 160 && yin > 144 && yin < 176)
    {
        display->menu = 2;
        display->changeScreen(wave, sdcard);
    }
    else if (xin > 10 && xin < 160 && yin > 180 && yin < 212)
    {
        display->menu = 3;
        display->changeScreen(wave, sdcard);
    }
}

Wave Touch::bottomMenu1(Display * display, Wave wave, Memory sdcard)
{
    if (xin >= 20 && xin <= 84 && yin > 217 && yin < 237)
    {
        display->menu = 0;
        display->waveOptions = false;
        display->changeScreen(wave, sdcard);
    }
    else if (xin >= 88 && xin <= 160 && yin > 217 && yin < 237)
    {
        wave.resetWave();
    }
    else if (xin >= 164 && xin <= 236 && yin > 217 && yin < 237)
    {
        display->drawWaveOn = true;
        display->selectWaveOn = false;  
        wave.customWaveXstart = wave.waveXstart;
        wave.customWaveXend = wave.waveXend;
        for (int i = 0; i < 303; i++)
        {
            wave.customPointUsed[i] = wave.pointUsed[i];
            wave.customWaveY[i] = wave.waveY[i];
        }
        display->updateSet(wave, sdcard);
    }
    else if (xin >= 240 && xin <= 312 && yin > 217 && yin < 237)
    {
        if (display->waveOptions)
        {
            display->waveOptions = false;
            display->changeScreen(wave, sdcard);
        }
        else if (!display->waveOptions)
        {
            display->waveOptions = true;
            display->changeScreen(wave, sdcard);
        }
    }
    return wave;
}

Wave Touch::bottomMenu2(Display * display, Wave wave, Memory sdcard)
{
    if (xin >= 32 && xin <= 116 && yin > 217 && yin < 237)
    {
        display->menu = 0;
        display->changeScreen(wave, sdcard);
    }
    else if (xin >= 208 && xin <= 292 && yin > 217 && yin < 237)
    {
        if (display->selectWaveOn) {
            display->selectWaveOn = false;  
        }
        else if (!display->selectWaveOn) {
            display->selectWaveOn = true;
            display->drawWaveOn = false;
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
        display->updateSet(wave, sdcard);
    }
    return wave;
}

void Touch::bottomMenu3(Display * display, Wave wave, Memory sdcard)
{
    if (xin >= 32 && xin <= 116 && yin > 217 && yin < 237)
    {
        display->menu = 0;
        display->changeScreen(wave, sdcard);
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
        display->updateSet(wave, sdcard);
    }
}

Wave Touch::bottomMenu4(Display * display, Wave wave, Memory sdcard)
{
    if (xin >= 6 && xin <= 106 && yin > 217 && yin < 237)
    {
        display->menu = 1;
        display->saveFile = 0;
        display->changeScreen(wave, sdcard);
    }
    else if (xin >= 110 && xin <= 210 && yin > 217 && yin < 237)
    {
        if (display->saveLoad)
        {
            wave = sdcard.loadFile(display->saveFile, wave);
            wave.confirmLoad();
            display->menu = 1;
            display->saveFile = 0;
            display->changeScreen(wave, sdcard);
        }
        else if (!display->saveLoad)
        {
            sdcard.saveFile(display->saveFile, wave);
            display->updateSet(wave, sdcard);
            display->menu = 1;
            display->saveFile = 0;
            display->changeScreen(wave, sdcard);
        }
    }
    else if (xin >= 214 && xin <= 314 && yin > 217 && yin < 237)
    {
        if (display->smoothOn && display->smoothLevel == 1)
            {
                display->smoothLevel = 2;
                display->changeScreen(wave, sdcard);
            }
            else if (display->smoothOn && display->smoothLevel == 2)
            {
                display->smoothOn = false;
                display->smoothLevel = 0;
                display->changeScreen(wave, sdcard);
            }
            else if (!display->smoothOn)
            {
                display->smoothOn = true;
                display->smoothLevel = 1;
                display->changeScreen(wave, sdcard);
            }
    }
    return wave;
}

Wave Touch::drawWave(Display * display, Wave wave, Memory sdcard)
{
    if (display->waveOptions)
    {
        if (xin >= 162 && xin <= 314 && yin >= 108 && yin < 134)
        {
            if (display->smoothOn && display->smoothLevel == 1)
            {
                display->smoothLevel = 2;
                display->changeScreen(wave, sdcard);
            }
            else if (display->smoothOn && display->smoothLevel == 2)
            {
                display->smoothOn = false;
                display->smoothLevel = 0;
                display->changeScreen(wave, sdcard);
            }
            else if (!display->smoothOn)
            {
                display->smoothOn = true;
                display->smoothLevel = 1;
                display->changeScreen(wave, sdcard);
            }
        }
        else if (xin >= 162 && xin <= 314 && yin > 134 && yin < 160)
        {
            display->menu = 4;
            display->saveLoad = false;
            display->changeScreen(wave, sdcard);
        }
        else if (xin >= 162 && xin <= 314 && yin > 160 && yin < 186)
        {
            display->menu = 4;
            display->saveLoad = true;
            display->changeScreen(wave, sdcard);
        }
        else if (xin >= 162 && xin <= 314 && yin > 186 && yin < 212)
        {
            if (display->waveOptions)
            {
                display->waveOptions = false;
                display->changeScreen(wave, sdcard);
            }
            else if (!display->waveOptions)
            {
                display->waveOptions = true;
                display->changeScreen(wave, sdcard);
            }
        }
    }
    else if (xin >= 11 && xin <= 313 && yin > 5 && yin < 211)
    {
        wave.updateWave(xin, yin);
    }
    wave = bottomMenu1(display, wave, sdcard);
    return wave;
}

Wave Touch::selectWave(Display * display, Wave wave, Memory sdcard)
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
    wave = bottomMenu2(display, wave, sdcard);
    return wave;
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

void Touch::envelope(Display * display, Wave wave, Memory sdcard)
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
    bottomMenu3(display, wave, sdcard);
}

Wave Touch::saveWave(Display * display, Wave wave, Memory sdcard)
{
    if (xin >= 6 && xin <= 80 && yin >= 112 && yin <= 160)
    {
        display->saveFile = 1;
    }
    else if (xin >= 84 && xin <= 158 && yin >= 112 && yin <= 160)
    {
        display->saveFile = 2;
    }
    else if (xin >= 162 && xin <= 236 && yin >= 112 && yin <= 160)
    {
        display->saveFile = 3;
    }
    else if (xin >= 240 && xin <= 314 && yin >= 112 && yin <= 160)
    {
        display->saveFile = 4;
    }
    else if (xin >= 6 && xin <= 80 && yin >= 164 && yin <= 212)
    {
        display->saveFile = 5;
    }
    else if (xin >= 84 && xin <= 158 && yin >= 164 && yin <= 212)
    {
        display->saveFile = 6;
    }
    else if (xin >= 162 && xin <= 236 && yin >= 164 && yin <= 212)
    {
        display->saveFile = 7;
    }
    else if (xin >= 240 && xin <= 314 && yin >= 164 && yin <= 212)
    {
        display->saveFile = 8;
    }
    wave = bottomMenu4(display, wave, sdcard);
    return wave;
}

Wave Touch::processTouch(Display * display, Wave wave, Memory sdcard)
{
    if (display->menu == 0)
    {
        mainMenu(display, wave, sdcard);
    }
    else if (display->menu == 1)
    {
        wave = drawWave(display, wave, sdcard);
    }
    else if (display->menu == 2)
    {
        wave = selectWave(display, wave, sdcard);
    }
    else if (display->menu == 3)
    {
        envelope(display, wave, sdcard);
    }
    else if (display->menu == 4)
    {
        wave = saveWave(display, wave, sdcard);
    }
    return wave;
}

