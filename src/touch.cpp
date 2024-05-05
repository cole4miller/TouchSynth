#include "touch.h"

void Touch::mainMenu(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator)
{
    if (xin > 48 && xin < 210 && yin > 105 && yin < 132)
    {
        display->menu = 1;
        display->changeScreen(wave, sdcard);
    }
    else if (xin > 209 && xin < 277 && yin > 105 && yin < 132)
    {
        if(display->drawWaveOn)
        {
            display->drawWaveOn = false;
        }
        else if(!display->drawWaveOn)
        {
            display->drawWaveOn = true;
            display->selectWaveOn = false;
        }
        oscillator->fillWave(wave, display);
        oscillator->fillBuffer(wave, display);
        display->changeScreen(wave, sdcard);
    }
    else if (xin > 48 && xin < 210 && yin > 136 && yin < 166)
    {
        display->menu = 2;
        display->changeScreen(wave, sdcard);
    }
    else if (xin > 209 && xin < 277 && yin > 136 && yin < 166)
    {
        if(display->selectWaveOn)
        {
            display->selectWaveOn = false;
        }
        else if(!display->selectWaveOn)
        {
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
            else if (display->selectWaveType == 2)
            {
                wave.triangleWave();
            }
            else if (display->selectWaveType == 3)
            {
                wave.sawtoothWave();
            }
        }
        oscillator->fillWave(wave, display);
        oscillator->fillBuffer(wave, display);
        display->changeScreen(wave, sdcard);
    }
    else if (xin > 48 && xin < 210 && yin > 170 && yin < 199)
    {
        display->menu = 5;
        display->changeScreen(wave, sdcard);
    }
    else if (xin > 209 && xin < 277 && yin > 170 && yin < 199)
    {
        if(display->seqOn)
        {
            display->seqOn = false;
        }
        else if(!display->seqOn)
        {
            display->seqOn = true;
        }
        oscillator->fillWave(wave, display);
        oscillator->fillBuffer(wave, display);
        display->changeScreen(wave, sdcard);
    }
    else if (xin > 48 && xin < 277 && yin > 202 && yin < 232)
    {
        display->menu = 3;
        display->changeScreen(wave, sdcard);
    }
}

// Draw wave bottom menu
Wave Touch::bottomMenu1(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator)
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
        wave = wave.smoothWave(wave, display->smoothLevel);
        if (!display->smoothOn)
        {
            wave.customWaveXstart = wave.waveXstart;
            wave.customWaveXend = wave.waveXend;
            for (int i = 0; i < 303; i++)
            {
                wave.customPointUsed[i] = wave.pointUsed[i];
                wave.customWaveY[i] = wave.waveY[i];
            }
        }
        else if (display->smoothOn)
        {
            wave.customWaveXstart = wave.smoothWaveXstart;
            wave.customWaveXend = wave.smoothWaveXend;
            for (int i = 0; i < 303; i++)
            {
                wave.customPointUsed[i] = wave.smoothPointUsed[i];
                wave.customWaveY[i] = wave.smoothWaveY[i];
            }
        }
        oscillator->fillWave(wave, display);
        oscillator->fillBuffer(wave, display);
        display->updateSet(wave, sdcard);
        
        /*
        Serial.print(" waveXstart: ");
        Serial.print("\t");
        Serial.println(wave.smoothWaveXstart);

        Serial.print(" waveXend: ");
        Serial.print("\t");
        Serial.println(wave.smoothWaveXend);

        Serial.println(" waveY array: ");
        for (int i = 0; i < 303; i++)
        {
            Serial.print(wave.smoothWaveY[i]);
            Serial.print("\t");
        }
        Serial.println();
        */
    
        Serial.print(" outWaveXstart: ");
        Serial.print("\t");
        Serial.println(oscillator->outWaveXstart);

        Serial.print(" outWaveXend: ");
        Serial.print("\t");
        Serial.println(oscillator->outWaveXend);

        Serial.println(" outWaveY array: ");
        for (int i = 0; i < 303; i++)
        {
            Serial.print(oscillator->outWaveY[i]);
            Serial.print("\t");
        }
        Serial.println();

        Serial.print(" osc freq: ");
        Serial.print("\t");
        Serial.println(oscillator->freq);
        Serial.print(" 1 / freq: ");
        Serial.print("\t");
        Serial.println((double)(1.0 / oscillator->freq), 10);
        Serial.print(" update time: ");
        Serial.print("\t");
        Serial.println((1.0 / oscillator->freq) / (((double)oscillator->updateTime) * (1e-6)));
        Serial.println(" output buffer: ");
        for (int i = 0; i < oscillator->bufferSteps+20; i++)
        {
            Serial.print(oscillator->bufferOut[i]);
            Serial.print("\t");
        }
    
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

// Select wave bottom menu
Wave Touch::bottomMenu2(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator)
{
    if (xin >= 32 && xin <= 116 && yin > 217 && yin < 237)
    {
        display->menu = 0;
        display->changeScreen(wave, sdcard);
    }
    else if (xin >= 208 && xin <= 292 && yin > 217 && yin < 237)
    {
        if (display->selectWaveOn) 
        {
            display->selectWaveOn = false;  
        }
        else if (!display->selectWaveOn) 
        {
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
            else if (display->selectWaveType == 2)
            {
                wave.triangleWave();
            }
            else if (display->selectWaveType == 3)
            {
                wave.sawtoothWave();
            }
        }
        oscillator->fillWave(wave, display);
        oscillator->fillBuffer(wave, display);
        Serial.println(" output buffer: ");
        for (int i = 0; i < oscillator->bufferSteps+20; i++)
        {
            Serial.print(oscillator->bufferOut[i]);
            Serial.print("\t");
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
        //display->attack = 75;
        //display->decay = 75;
        //display->sustain = 75;
        //display->release = 75;
    }
    else if (xin >= 208 && xin <= 292 && yin > 217 && yin < 237)
    {
        /*
        if (display->envelopeOn) {
            display->envelopeOn = false;  
        }
        else if (!display->envelopeOn) {
            display->envelopeOn = true;
        }
        display->updateSet(wave, sdcard);
        */
    }
}

// Save/Load bottom menu
Wave Touch::bottomMenu4(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator)
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
            oscillator->fillWave(wave, display);
            oscillator->fillBuffer(wave, display);
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

// Sequencer bottom menu
void Touch::bottomMenu5(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator)
{
    if (xin >= 20 && xin <= 84 && yin > 217 && yin < 237)
    {
        display->menu = 0;
        display->changeScreen(wave, sdcard);
    }
    else if (xin >= 88 && xin <= 160 && yin > 217 && yin < 237)
    {
        for(int i = 0; i < 8; i++)
        {
            display->seqNoteArray[i] = 45;
        }
        display->BPM = 80;
        oscillator->fillWave(wave, display);
        oscillator->fillBuffer(wave, display);
        display->changeScreen(wave, sdcard);
        
    }
    else if (xin >= 164 && xin <= 236 && yin > 217 && yin < 237)
    {
        if (display->seqOn) {
            display->seqOn = false;  
        }
        else if (!display->seqOn) {
            display->seqOn = true;
        }
        oscillator->fillWave(wave, display);
        oscillator->fillBuffer(wave, display);
        display->updateSet(wave, sdcard);
    }
    else if (xin >= 240 && xin <= 312 && yin > 217 && yin < 237)
    {
        display->menu = 9;
        display->changeScreen(wave, sdcard);
    }
}

Wave Touch::drawWave(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator)
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
            if (wave.drawLR)
            {
                wave.drawLR = false;
                display->changeScreen(wave, sdcard);
            }
            else if (!wave.drawLR)
            {
                wave.drawLR = true;
                display->changeScreen(wave, sdcard);
            }
        }
    }
    else if (xin >= 11 && xin <= 313 && yin > 5 && yin < 211)
    {
        wave.updateWave(xin, yin);
        //if (display->smoothOn)
        //{

        //}
    }
    wave = bottomMenu1(display, wave, sdcard, oscillator);
    return wave;
}

Wave Touch::selectWave(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator)
{
    if (xin >= 10 && xin <= 160 && yin >= 4 && yin <= 106)
    {
        display->selectWaveType = 0;
        if (display->selectWaveOn)
        {
            wave.squareWave();
            oscillator->fillBuffer(wave, display);
        }
    }
    else if (xin >= 164 && xin <= 314 && yin >= 4 && yin <= 106)
    {
        display->selectWaveType = 1;
        if (display->selectWaveOn)
        {
            wave.sineWave();
            oscillator->fillBuffer(wave, display);
        }
    }
    else if (xin >= 10 && xin <= 160 && yin >= 110 && yin <= 212)
    {
        display->selectWaveType = 2;
        if (display->selectWaveOn)
        {
            wave.triangleWave();
            oscillator->fillBuffer(wave, display);
        }
    }
    else if (xin >= 164 && xin <= 314 && yin >= 110 && yin <= 212)
    {
        display->selectWaveType = 3;
        if (display->selectWaveOn)
        {
            wave.sawtoothWave();
            oscillator->fillBuffer(wave, display);
        }
    }
    wave = bottomMenu2(display, wave, sdcard, oscillator);
    return wave;
}

void Touch::settings(Display * display, Wave wave, Memory sdcard)
{
    // Tune input
    if (xin > 48 && xin < 276 && yin > 71 && yin < 101)
    {
        display->menu = 6;
        display->changeScreen(wave, sdcard);
    }
    // Trigger Level
    else if (xin > 48 && xin < 276 && yin > 104 && yin < 134)
    {
        display->menu = 7;
        display->changeScreen(wave, sdcard);
    }
    // Light/Dark mode
    else if (xin > 48 && xin < 276 && yin > 136 && yin < 166)
    {
        if (display->lightDarkMode == 0)
        {
            display->lightDarkMode = 1;
            display->backgroundColor = 0xFFFF;
            display->secondColor = 0xC618;
            display->thirdColor = 0x7BEF;
            display->textColor = 0x0000;
        }
        else if (display->lightDarkMode == 1)
        {
            display->lightDarkMode = 0;
            display->backgroundColor = 0x0000;
            display->secondColor = 0x7BEF;
            display->thirdColor = 0xC618;
            display->textColor = 0xFFFF;
        }
        display->changeScreen(wave, sdcard);
    }
    // Credits
    else if (xin > 48 && xin < 276 && yin > 170 && yin < 200)
    {
        display->menu = 8;
        display->changeScreen(wave, sdcard);
    }
    // Back
    else if (xin > 48 && xin < 276 && yin > 203 && yin < 233)
    {
        display->menu = 0;
        display->changeScreen(wave, sdcard);
    }
}

Wave Touch::saveWave(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator)
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
    wave = bottomMenu4(display, wave, sdcard, oscillator);
    return wave;
}

void Touch::sequencer(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator)
{
    // Up arrows
    if (xin >= 162 && xin <= 314 && yin >= 4 && yin <= 22)
    {
        if(display->BPM < 200) 
        {
            display->BPM++;
        }
    }
    else if (xin >= 6 && xin <= 80 && yin >= 112 && yin <= 123)
    {
        if(display->seqNoteArray[0] < 84)
        {
            display->seqNoteArray[0]++;
        }
    }
    else if (xin >= 84 && xin <= 158 && yin >= 112 && yin <= 123)
    {
        if(display->seqNoteArray[1] < 84)
        {
            display->seqNoteArray[1]++;
        }
    }
    else if (xin >= 162 && xin <= 236 && yin >= 112 && yin <= 123)
    {
        if(display->seqNoteArray[2] < 84)
        {
            display->seqNoteArray[2]++;
        }
    }
    else if (xin >= 240 && xin <= 314 && yin >= 112 && yin <= 123)
    {
        if(display->seqNoteArray[3] < 84)
        {
            display->seqNoteArray[3]++;
        }
    }
    else if (xin >= 6 && xin <= 80 && yin >= 164 && yin <= 175)
    {
        if(display->seqNoteArray[4] < 84)
        {
            display->seqNoteArray[4]++;
        }
    }
    else if (xin >= 84 && xin <= 158 && yin >= 164 && yin <= 175)
    {
        if(display->seqNoteArray[5] < 84)
        {
            display->seqNoteArray[5]++;
        }
    }
    else if (xin >= 162 && xin <= 236 && yin >= 164 && yin <= 175)
    {
        if(display->seqNoteArray[6] < 84)
        {
            display->seqNoteArray[6]++;
        }
    }
    else if (xin >= 240 && xin <= 314 && yin >= 164 && yin <= 175)
    {
        if(display->seqNoteArray[7] < 84)
        {
            display->seqNoteArray[7]++;
        }
    }

    // Down Arrows
    else if (xin >= 162 && xin <= 314 && yin >= 90 && yin <= 108)
    {
        if(display->BPM > 1)
        {
            display->BPM--;
        }
    }
    else if (xin >= 6 && xin <= 80 && yin >= 149 && yin <= 160)
    {
        if(display->seqNoteArray[0] > 0)
        {
            display->seqNoteArray[0]--;
        }
    }
    else if (xin >= 84 && xin <= 158 && yin >= 149 && yin <= 160)
    {
        if(display->seqNoteArray[1] > 0)
        {
            display->seqNoteArray[1]--;
        }
    }
    else if (xin >= 162 && xin <= 236 && yin >= 149 && yin <= 160)
    {
        if(display->seqNoteArray[2] > 0)
        {
            display->seqNoteArray[2]--;
        }
    }
    else if (xin >= 240 && xin <= 314 && yin >= 149 && yin <= 160)
    {
        if(display->seqNoteArray[3] > 0)
        {
            display->seqNoteArray[3]--;
        }
    }
    else if (xin >= 6 && xin <= 80 && yin >= 201 && yin <= 212)
    {
        if(display->seqNoteArray[4] > 0)
        {
            display->seqNoteArray[4]--;
        }
    }
    else if (xin >= 84 && xin <= 158 && yin >= 201 && yin <= 212)
    {
        if(display->seqNoteArray[5] > 0)
        {
            display->seqNoteArray[5]--;
        }
    }
    else if (xin >= 162 && xin <= 236 && yin >= 201 && yin <= 212)
    {
        if(display->seqNoteArray[6] > 0)
        {
            display->seqNoteArray[6]--;
        }
    }
    else if (xin >= 240 && xin <= 314 && yin >= 201 && yin <= 212)
    {
        if(display->seqNoteArray[7] > 0)
        {
            display->seqNoteArray[7]--;
        }
    }

    bottomMenu5(display, wave, sdcard, oscillator);
    delay(200);
}

void Touch::tuneInput(Display * display, Wave wave, Memory sdcard)
{
    // slider
    if (xin > 11 && xin < 63 && yin > 109 && yin < 159)
    {
        display->pitchTune = 0;
    }
    else if (xin > 62 && xin < 263 && yin > 109 && yin < 159)
    {
        display->pitchTune = xin - 62;
    }
    else if (xin > 262 && xin < 313 && yin > 109 && yin < 159)
    {
        display->pitchTune = 200;
    }

    // Reset
    else if (xin > 48 && xin < 276 && yin > 170 && yin < 200)
    {
        display->pitchTune = 100;
        display->changeScreen(wave, sdcard);
    }
    // Back
    else if (xin > 48 && xin < 276 && yin > 203 && yin < 233)
    {
        display->menu = 3;
        display->changeScreen(wave, sdcard);
    }
}

void Touch::seqGateAdjust(Display * display, Wave wave, Memory sdcard)
{
    // slider
    if (xin > 11 && xin < 63 && yin > 109 && yin < 159)
    {
        display->seqGate = 0.1;
    }
    else if (xin > 62 && xin < 263 && yin > 109 && yin < 159)
    {
        display->seqGate = ((xin - 62) * 0.004) + 0.1;
    }
    else if (xin > 262 && xin < 313 && yin > 109 && yin < 159)
    {
        display->seqGate = 0.9;
    }

    // Reset
    else if (xin > 48 && xin < 276 && yin > 170 && yin < 200)
    {
        display->seqGate = 0.499;
        display->changeScreen(wave, sdcard);
    }
    // Back
    else if (xin > 48 && xin < 276 && yin > 203 && yin < 233)
    {
        display->menu = 5;
        display->changeScreen(wave, sdcard);
    }
}

void Touch::triggerSens(Display * display, Wave wave, Memory sdcard)
{
    // slider
    if (xin > 11 && xin < 63 && yin > 109 && yin < 159)
    {
        display->trigLevel = 0;
    }
    else if (xin > 62 && xin < 263 && yin > 109 && yin < 159)
    {
        display->trigLevel = xin - 62;
    }
    else if (xin > 262 && xin < 313 && yin > 109 && yin < 159)
    {
        display->trigLevel = 200;
    }

    // Reset
    else if (xin > 48 && xin < 276 && yin > 170 && yin < 200)
    {
        display->trigLevel = 100;
        display->changeScreen(wave, sdcard);
    }
    // Back
    else if (xin > 48 && xin < 276 && yin > 203 && yin < 233)
    {
        display->menu = 3;
        display->changeScreen(wave, sdcard);
    }
}

void Touch::credits(Display * display, Wave wave, Memory sdcard)
{
    // Back
    if (xin > 48 && xin < 276 && yin > 203 && yin < 233)
    {
        display->menu = 3;
        display->changeScreen(wave, sdcard);
    }
}

Wave Touch::processTouch(Display * display, Wave wave, Memory sdcard, Oscillator * oscillator)
{
    if (display->menu == 0)
    {
        mainMenu(display, wave, sdcard, oscillator);
    }
    else if (display->menu == 1)
    {
        wave = drawWave(display, wave, sdcard, oscillator);
    }
    else if (display->menu == 2)
    {
        wave = selectWave(display, wave, sdcard, oscillator);
    }
    else if (display->menu == 3)
    {
        settings(display, wave, sdcard);
    }
    else if (display->menu == 4)
    {
        wave = saveWave(display, wave, sdcard, oscillator);
    }
    else if (display->menu == 5)
    {
        sequencer(display, wave, sdcard, oscillator);
    }
    else if (display->menu == 6)
    {
        tuneInput(display, wave, sdcard);
    }
    else if (display->menu == 7)
    {
        triggerSens(display, wave, sdcard);
    }
    else if (display->menu == 8)
    {
        credits(display, wave, sdcard);
    }
    else if (display->menu == 9)
    {
        seqGateAdjust(display, wave, sdcard);
    }
    return wave;
}

