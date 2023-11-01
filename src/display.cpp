#include "display.h"

Display::Display(int16_t *data1, int16_t *data2, ILI9341_t3n *screen)
    : tft(screen)
{
    data[0] = data1;
    data[1] = data2;
    tft->begin();
    tft->fillScreen(ILI9341_BLACK);

    tft->useFrameBuffer(true);

    tft->setRotation(1);
}

// draws gridlines for wave draw window
void Display::drawGrid()
{
    // horizontal lines
    tft->drawFastHLine(10, 4, 304, ILI9341_WHITE);
    tft->drawFastHLine(10, 30, 304, CL(50, 50, 50));
    tft->drawFastHLine(10, 56, 304, CL(50, 50, 50));
    tft->drawFastHLine(10, 82, 304, CL(50, 50, 50));
    tft->drawFastHLine(10, 108, 304, CL(100, 100, 100));
    tft->drawFastHLine(10, 134, 304, CL(50, 50, 50));
    tft->drawFastHLine(10, 160, 304, CL(50, 50, 50));
    tft->drawFastHLine(10, 186, 304, CL(50, 50, 50));
    tft->drawFastHLine(10, 212, 304, ILI9341_WHITE);

    // vertical lines
    tft->drawFastVLine(10, 4, 208, ILI9341_WHITE);
    tft->drawFastVLine(48, 5, 207, CL(50, 50, 50));
    tft->drawFastVLine(86, 5, 207, CL(50, 50, 50));
    tft->drawFastVLine(124, 5, 207, CL(50, 50, 50));
    tft->drawFastVLine(162, 5, 207, CL(100, 100, 100));
    tft->drawFastVLine(200, 5, 207, CL(50, 50, 50));
    tft->drawFastVLine(238, 5, 207, CL(50, 50, 50));
    tft->drawFastVLine(276, 5, 207, CL(50, 50, 50));
    tft->drawFastVLine(314, 4, 208, ILI9341_WHITE);
}

void Display::miniWave(Wave wave)
{
    // Grid horizontal lines
    tft->drawFastHLine(162, 134, 151, CL(50, 50, 50));
    tft->drawFastHLine(162, 160, 151, CL(100, 100, 100));
    tft->drawFastHLine(162, 186, 151, CL(50, 50, 50));
    
    // Grid vertical lines
    tft->drawFastVLine(200, 108, 103, CL(50, 50, 50));
    tft->drawFastVLine(238, 108, 103, CL(100, 100, 100));
    tft->drawFastVLine(276, 108, 103, CL(50, 50, 50));

    tft->drawRoundRect(162, 108, 152, 104, 4, ILI9341_WHITE);

    // Wave form
    if (drawWaveOn)
    {
        if (smoothOn)
        {
            wave.waveXstart = wave.customWaveXstart;
            wave.waveXend = wave.customWaveXend;
            for (int i = 0; i < 303; i++)
            {
                wave.pointUsed[i] = wave.customPointUsed[i];
                wave.waveY[i] = wave.customWaveY[i];
            }
            wave = wave.smoothWave(wave, smoothLevel);
            int xprev = wave.smoothWaveXstart;
            for (int i = wave.smoothWaveXstart + 4; i <= wave.smoothWaveXend; i++)
            {
                if (wave.smoothPointUsed[i])
                {
                    tft->drawLine(((xprev / 2.0) + 163), (160 - wave.smoothWaveY[xprev] / 2.0), ((i / 2.0) + 163), 160 - wave.smoothWaveY[i] / 2.0, ILI9341_WHITE);
                    xprev = i;
                    i = i + 3;
                }
            }
        }
        else if (!smoothOn)
        {
            int xprev = wave.customWaveXstart;
            for (int i = wave.customWaveXstart + 4; i <= wave.customWaveXend; i++)
            {
                if (wave.customPointUsed[i])
                {
                    tft->drawLine(((xprev / 2.0) + 163), (160 - wave.customWaveY[xprev] / 2.0), ((i / 2.0) + 163), 160 - wave.customWaveY[i] / 2.0, ILI9341_WHITE);
                    xprev = i;
                    i = i + 3;
                }
            }
        }
    }
    else if (selectWaveOn)
    {
        if (selectWaveType == 0)
        {
            tft->drawFastVLine(187, 121, 39, ILI9341_WHITE);
            tft->drawFastHLine(187, 121, 51, ILI9341_WHITE);
            tft->drawFastVLine(238, 121, 78, ILI9341_WHITE);
            tft->drawFastHLine(238, 199, 51, ILI9341_WHITE);
            tft->drawFastVLine(289, 160, 39, ILI9341_WHITE);
        }
        else if (selectWaveType == 1)
        {
            for (int i = 0; i < 102; i++)
            {
                tft->drawLine(187 + i, 39 * sin(2.0 * M_PI * i / 102.0) + 160, 187 + (i + 2), 39.0 * sin(2.0 * M_PI * (i + 2.0) / 102.0) + 160, ILI9341_WHITE);
                i++;
            }
        }
        else if (selectWaveType == 2)
        {
            tft->drawLine(188, 160, 213, 121, ILI9341_WHITE);
            tft->drawLine(213, 121, 263, 199, ILI9341_WHITE);
            tft->drawLine(263, 199, 288, 160, ILI9341_WHITE);
        }
        else if (selectWaveType == 3)
        {
            tft->drawFastVLine(188, 160, 39, ILI9341_WHITE);
            tft->drawLine(188, 199, 288, 121, ILI9341_WHITE);
            tft->drawFastVLine(288, 121, 39, ILI9341_WHITE);
        }
    }
}

void Display::mainMenu(Wave wave)
{
    
    for (int i = 0; i < 240; i++)
    {
        tft->drawLine(40 + i, 10.0 * sin(2.0 * M_PI * i / 240.0) + 90, 40 + (i + 2), 10.0 * sin(2.0 * M_PI * (i + 2.0) / 240.0) + 15, ILI9341_WHITE);
        i++;
    }
    tft->setFont(Arial_32);
    tft->setCursor(45, 35);
    tft->setTextColor(ILI9341_BLACK);
    tft->print("TouchSynth");
    

   /*
    for (int i = 0; i < 300; i++)
    {
        tft->drawLine(10 + i, 20 * sin(2.0 * M_PI * i / 600.0) * sin(2.0 * M_PI * i / 20.0) + 75, 10 + (i + 2), 20 * sin(2.0 * M_PI * i / 600.0) * sin(2.0 * M_PI * (i + 2.0) / 20.0) + 75, ILI9341_WHITE);
        i++;
    }
    tft->setFont(Arial_32);
    tft->setCursor(45, 10);
    tft->setTextColor(ILI9341_WHITE);
    tft->print("TouchSynth");
    */

    tft->setTextColor(ILI9341_WHITE);
    tft->setFont(Arial_14);
    tft->drawRoundRect(10, 108, 150, 32, 4, ILI9341_WHITE);
    tft->setCursor(36, 116);
    tft->print("Draw Wave");
    tft->drawRoundRect(10, 144, 150, 32, 4, ILI9341_WHITE);
    tft->setCursor(31, 152);
    tft->print("Select Wave");
    tft->drawRoundRect(10, 180, 150, 32, 4, ILI9341_WHITE);
    tft->setCursor(45, 188);
    tft->print("Envelope");

    miniWave(wave);
}

void Display::saveText()
{
    tft->setFont(Arial_18);
    tft->setTextColor(ILI9341_BLACK);
    tft->setCursor(18, 18);
    tft->print("Save Wave");

    tft->fillRoundRect(57, 48, 50, 50, 3, ILI9341_BLACK);
    tft->fillRoundRect(67, 48, 30, 18, 1, ILI9341_DARKGREY);
    tft->fillRoundRect(84, 50, 8, 14, 1, ILI9341_BLACK);

    tft->setCursor(36, 127);
    tft->print("1");

    tft->setCursor(114, 127);
    tft->print("2");

    tft->setCursor(192, 127);
    tft->print("3");

    tft->setCursor(269, 127);
    tft->print("4");

    tft->setCursor(36, 179);
    tft->print("5");

    tft->setCursor(114, 179);
    tft->print("6");

    tft->setCursor(192, 179);
    tft->print("7");

    tft->setCursor(269, 179);
    tft->print("8");
}

void Display::drawSave(Wave wave, Memory sdcard)
{
    //Wave wave;

    // Grid horizontal lines
    tft->drawFastHLine(162, 30, 151, CL(50, 50, 50));
    tft->drawFastHLine(162, 56, 151, CL(100, 100, 100));
    tft->drawFastHLine(162, 82, 151, CL(50, 50, 50));
    
    // Grid vertical lines
    tft->drawFastVLine(200, 4, 103, CL(50, 50, 50));
    tft->drawFastVLine(238, 4, 103, CL(100, 100, 100));
    tft->drawFastVLine(276, 4, 103, CL(50, 50, 50));

    tft->drawRoundRect(162, 4, 152, 104, 4, ILI9341_WHITE);

    if (saveLoad)
    {
        wave = sdcard.loadFile(saveFile, wave);
        if (smoothOn)
        {
            wave.waveXstart = wave.previewWaveXstart;
            wave.waveXend = wave.previewWaveXend;
            for (int i = 0; i < 303; i++)
            {
                wave.pointUsed[i] = wave.previewPointUsed[i];
                wave.waveY[i] = wave.previewWaveY[i];
            }
            wave = wave.smoothWave(wave, smoothLevel);
            wave.previewWaveXstart = wave.smoothWaveXstart;
            wave.previewWaveXend = wave.smoothWaveXend;
            for (int i = 0; i < 303; i++)
            {
                wave.previewPointUsed[i] = wave.smoothPointUsed[i];
                wave.previewWaveY[i] = wave.smoothWaveY[i];
            }
        }
    }
    else if (!saveLoad)
    {
        if (smoothOn)
        {
            wave.waveXstart = wave.customWaveXstart;
            wave.waveXend = wave.customWaveXend;
            for (int i = 0; i < 303; i++)
            {
                wave.pointUsed[i] = wave.customPointUsed[i];
                wave.waveY[i] = wave.customWaveY[i];
            }
            wave = wave.smoothWave(wave, smoothLevel);
            wave.previewWaveXstart = wave.smoothWaveXstart;
            wave.previewWaveXend = wave.smoothWaveXend;
            for (int i = 0; i < 303; i++)
            {
                wave.previewPointUsed[i] = wave.smoothPointUsed[i];
                wave.previewWaveY[i] = wave.smoothWaveY[i];
            }
        }
        else if (!smoothOn)
        {
            wave.previewWaveXstart = wave.customWaveXstart;
            wave.previewWaveXend = wave.customWaveXend;
            for (int i = 0; i < 303; i++)
            {
                wave.previewPointUsed[i] = wave.customPointUsed[i];
                wave.previewWaveY[i] = wave.customWaveY[i];
            }
        }
    }

    int xprev = wave.previewWaveXstart;
    for (int i = wave.previewWaveXstart + 4; i <= wave.previewWaveXend; i++)
    {
        if (wave.previewPointUsed[i])
        {
            tft->drawLine(((xprev / 2.0) + 163), (56 - wave.previewWaveY[xprev] / 2.0), ((i / 2.0) + 163), 56 - wave.previewWaveY[i] / 2.0, ILI9341_WHITE);
            xprev = i;
            i = i + 3;
        }
    }

    /*
    if (smoothOn)
    {
        wave.waveXstart = wave.customWaveXstart;
        wave.waveXend = wave.customWaveXend;
        for (int i = 0; i < 303; i++)
        {
            wave.pointUsed[i] = wave.customPointUsed[i];
            wave.waveY[i] = wave.customWaveY[i];
        }
        wave = wave.smoothWave(wave, smoothLevel);
        int xprev = wave.smoothWaveXstart;
        for (int i = wave.smoothWaveXstart + 4; i <= wave.smoothWaveXend; i++)
        {
            if (wave.smoothPointUsed[i])
            {
                tft->drawLine(((xprev / 2.0) + 163), (56 - wave.smoothWaveY[xprev] / 2.0), ((i / 2.0) + 163), 56 - wave.smoothWaveY[i] / 2.0, ILI9341_WHITE);
                xprev = i;
                i = i + 3;
            }
        }
    }
    else if (!smoothOn)
    {
        int xprev = wave.customWaveXstart;
        for (int i = wave.customWaveXstart + 4; i <= wave.customWaveXend; i++)
        {
            if (wave.customPointUsed[i])
            {
                tft->drawLine(((xprev / 2.0) + 163), (56 - wave.customWaveY[xprev] / 2.0), ((i / 2.0) + 163), 56 - wave.customWaveY[i] / 2.0, ILI9341_WHITE);
                xprev = i;
                i = i + 3;
            }
        }
    }
    */
}

void Display::saveWave(Wave wave, Memory sdcard)
{
    tft->fillRoundRect(6, 4, 152, 104, 4, ILI9341_LIGHTGREY);
    
    tft->fillRoundRect(6, 112, 74, 48, 4, ILI9341_LIGHTGREY);
    tft->fillRoundRect(84, 112, 74, 48, 4, ILI9341_LIGHTGREY);
    tft->fillRoundRect(162, 112, 74, 48, 4, ILI9341_LIGHTGREY);
    tft->fillRoundRect(240, 112, 74, 48, 4, ILI9341_LIGHTGREY);
    tft->fillRoundRect(6, 164, 74, 48, 4, ILI9341_LIGHTGREY);
    tft->fillRoundRect(84, 164, 74, 48, 4, ILI9341_LIGHTGREY);
    tft->fillRoundRect(162, 164, 74, 48, 4, ILI9341_LIGHTGREY);
    tft->fillRoundRect(240, 164, 74, 48, 4, ILI9341_LIGHTGREY);

    if (saveFile == 1)
    {
        tft->fillRoundRect(6, 112, 74, 48, 4, ILI9341_DARKGREY);
    }
    else if (saveFile == 2)
    {
        tft->fillRoundRect(84, 112, 74, 48, 4, ILI9341_DARKGREY);
    }
    else if (saveFile == 3)
    {
        tft->fillRoundRect(162, 112, 74, 48, 4, ILI9341_DARKGREY);
    }
    else if (saveFile == 4)
    {
        tft->fillRoundRect(240, 112, 74, 48, 4, ILI9341_DARKGREY);
    }
    else if (saveFile == 5)
    {
        tft->fillRoundRect(6, 164, 74, 48, 4, ILI9341_DARKGREY);
    }
    else if (saveFile == 6)
    {
        tft->fillRoundRect(84, 164, 74, 48, 4, ILI9341_DARKGREY);
    }
    else if (saveFile == 7)
    {
        tft->fillRoundRect(162, 164, 74, 48, 4, ILI9341_DARKGREY);
    }
    else if (saveFile == 8)
    {
        tft->fillRoundRect(240, 164, 74, 48, 4, ILI9341_DARKGREY);
    }
    
    tft->drawRoundRect(6, 4, 152, 104, 4, ILI9341_WHITE);
    
    tft->drawRoundRect(6, 112, 74, 48, 4, ILI9341_WHITE);
    tft->drawRoundRect(84, 112, 74, 48, 4, ILI9341_WHITE);
    tft->drawRoundRect(162, 112, 74, 48, 4, ILI9341_WHITE);
    tft->drawRoundRect(240, 112, 74, 48, 4, ILI9341_WHITE);
    tft->drawRoundRect(6, 164, 74, 48, 4, ILI9341_WHITE);
    tft->drawRoundRect(84, 164, 74, 48, 4, ILI9341_WHITE);
    tft->drawRoundRect(162, 164, 74, 48, 4, ILI9341_WHITE);
    tft->drawRoundRect(240, 164, 74, 48, 4, ILI9341_WHITE);

    drawSave(wave, sdcard);
    saveText();
    bottomMenu4();
}

// Draw wave screen
void Display::bottomMenu1()
{
    // Button text bubble
    tft->fillRoundRect(12, 217, 72, 20, 2, ILI9341_LIGHTGREY);
    tft->fillRoundRect(88, 217, 72, 20, 2, ILI9341_MAGENTA);
    tft->fillRoundRect(164, 217, 72, 20, 2, ILI9341_DARKGREEN);
    tft->fillRoundRect(240, 217, 72, 20, 2, ILI9341_CYAN);

    // Button text
    tft->setFont(Arial_9);
    tft->setTextColor(ILI9341_BLACK);
   
    if (waveOptions)
    {
        tft->fillRoundRect(162, 108, 152, 104, 2, ILI9341_LIGHTGREY);
        tft->drawRoundRect(162, 108, 152, 104, 2, ILI9341_WHITE);
        tft->drawFastHLine(162, 134, 152, ILI9341_WHITE);
        tft->drawFastHLine(162, 160, 152, ILI9341_WHITE);
        tft->drawFastHLine(162, 186, 152, ILI9341_WHITE);
        tft->fillTriangle(276, 216, 272, 212, 280, 212, ILI9341_WHITE);
        tft->setCursor(180, 116);
        if (smoothOn)
        {
            if (smoothLevel == 1) 
            {
                tft->print("Smooth:      Low");
            }
            else if (smoothLevel == 2)
            {
                tft->print("Smooth:      High");
            }
        }
        else if (!smoothOn)
        {
            tft->print("Smooth:       Off");
        }

        tft->setCursor(180, 142);
        tft->print("Save");

        tft->setCursor(180, 168);
        tft->print("Load");

        tft->setCursor(180, 194);
        tft->print("Close");
    }
    
    tft->setCursor(33, 222);
    tft->print("Back");

    tft->setCursor(108, 222);
    tft->print("Clear");

    tft->setCursor(189, 222);
    tft->print("Set");

    tft->setCursor(254, 222);
    tft->print("Options");
}

// Select wave screen
void Display::bottomMenu2()
{
    // Button text bubble
    tft->fillRoundRect(32, 217, 84, 20, 2, ILI9341_LIGHTGREY);
   
    // Button text
    tft->setFont(Arial_9);
    tft->setTextColor(ILI9341_BLACK);
    
    tft->setCursor(58, 222);
    tft->print("Back");

    if (selectWaveOn) {
        tft->fillRoundRect(208, 217, 84, 20, 2, ILI9341_DARKGREEN);
        tft->setCursor(240, 222);
        tft->print("On");  
    }
    else if (!selectWaveOn) {
        tft->fillRoundRect(208, 217, 84, 20, 2, ILI9341_LIGHTGREY);
        tft->setCursor(240, 222);
        tft->print("Off");
    }
}

// Envelope sliders screen
void Display::bottomMenu3()
{
    // Button text bubble
    tft->fillRoundRect(32, 217, 84, 20, 2, ILI9341_LIGHTGREY);
    tft->fillRoundRect(120, 217, 84, 20, 2, ILI9341_MAGENTA);
   
    // Button text
    tft->setFont(Arial_9);
    tft->setTextColor(ILI9341_BLACK);
    
    tft->setCursor(58, 222);
    tft->print("Back");

    tft->setCursor(145, 222);
    tft->print("Reset");

    tft->setCursor(240, 222);
    if (envelopeOn) 
    {
        tft->fillRoundRect(208, 217, 84, 20, 2, ILI9341_DARKGREEN);
        tft->print("On");  
    }
    else if (!envelopeOn) 
    {
        tft->fillRoundRect(208, 217, 84, 20, 2, ILI9341_LIGHTGREY);
        tft->print("Off");
    }
}

// Save screen
void Display::bottomMenu4()
{
    // Button text bubble
    tft->fillRoundRect(6, 217, 100, 20, 4, ILI9341_LIGHTGREY);
    tft->fillRoundRect(110, 217, 100, 20, 4, ILI9341_MAGENTA);
    tft->fillRoundRect(214, 217, 100, 20, 4, ILI9341_DARKGREEN);
   
    // Button text
    tft->setFont(Arial_9);
    tft->setTextColor(ILI9341_BLACK);
    
    tft->setCursor(41, 222);
    tft->print("Back");

    tft->setCursor(145, 222);
    if (saveLoad) 
    {
        tft->print("Load");  
    }
    else if (!saveLoad) 
    {
        tft->print("Save");
    }

    tft->setCursor(224, 222);
    if (smoothLevel == 0) 
    {
        tft->print("Smooth:  Off");  
    }
    else if (smoothLevel == 1) 
    {
        tft->print("Smooth: Low");
    }
    else if (smoothLevel == 2) 
    {
        tft->print("Smooth: High");
    }
}

void Display::drawWave(Wave wave)
{
    drawGrid();
    int xprev = wave.waveXstart;
    int pointCount = 0;
    for (int i = xprev; i <= wave.waveXend; i++)
    {
        if (wave.pointUsed[i])
        {
            pointCount++;
        }
    }
    if (smoothOn && pointCount > 5)
    {
        wave = wave.smoothWave(wave, smoothLevel);
        for (int i = wave.smoothWaveXstart + 2; i <= wave.smoothWaveXend; i++)
        {
            if (wave.smoothPointUsed[i])
            {
                tft->drawLine((xprev + 11), (108 - wave.smoothWaveY[xprev]), (i + 11), 108 - wave.smoothWaveY[i], ILI9341_WHITE);
                xprev = i;
                i++;
            }
        }
    }
    else if (!smoothOn || pointCount <= 5)
    {
        for (int i = wave.waveXstart + 2; i <= wave.waveXend; i++)
        {
            if (wave.pointUsed[i])
            {
                tft->drawLine((xprev + 11), (108 - wave.waveY[xprev]), (i + 11), 108 - wave.waveY[i], ILI9341_WHITE);
                xprev = i;
                i++;
            }
        }
    }
    bottomMenu1();
}

void Display::waveIcons()
{
    // axis lines
    tft->drawFastHLine(48, 56, 76, ILI9341_BLACK);
    tft->drawFastHLine(200, 56, 76, ILI9341_BLACK);
    tft->drawFastHLine(48, 160, 76, ILI9341_BLACK);
    tft->drawFastHLine(200, 160, 76, ILI9341_BLACK);

    // squarewave
    tft->drawFastVLine(68, 36, 20, ILI9341_BLACK);
    tft->drawFastHLine(68, 36, 18, ILI9341_BLACK);
    tft->drawFastVLine(86, 36, 40, ILI9341_BLACK);
    tft->drawFastHLine(86, 76, 18, ILI9341_BLACK);
    tft->drawFastVLine(104, 56, 20, ILI9341_BLACK);

    // sinewave
    for (int i = 0; i < 35; i++)
    {
        tft->drawLine((220 + i), 56 + 20.0 * sin((2 * M_PI * i) / 36), 222 + i, 56 + 20.0 * sin((2 * M_PI * (i + 2)) / 36), ILI9341_BLACK);
        i++;
    }
    
    // triangle
    tft->drawLine(68, 160, 77, 140, ILI9341_BLACK);
    tft->drawLine(77, 140, 95, 180, ILI9341_BLACK);
    tft->drawLine(95, 180, 104, 160, ILI9341_BLACK);

    // sawtooth
    tft->drawFastVLine(220, 160, 20, ILI9341_BLACK);
    tft->drawLine(220, 180, 256, 140, ILI9341_BLACK);
    tft->drawFastVLine(256, 140, 20, ILI9341_BLACK);
}

void Display::selectWave(Wave wave)
{
    tft->fillRoundRect(10, 4, 150, 102, 4, ILI9341_LIGHTGREY);
    tft->fillRoundRect(164, 4, 150, 102, 4, ILI9341_LIGHTGREY);
    tft->fillRoundRect(10, 110, 150, 102, 4, ILI9341_LIGHTGREY);
    tft->fillRoundRect(164, 110, 150, 102, 4, ILI9341_LIGHTGREY);
    if ( selectWaveType == 0)
    {
        tft->fillRoundRect(10, 4, 150, 102, 4, ILI9341_DARKGREY);
    }
    else if ( selectWaveType == 1)
    {
        tft->fillRoundRect(164, 4, 150, 102, 4, ILI9341_DARKGREY);
    }
    else if ( selectWaveType == 2)
    {
        tft->fillRoundRect(10, 110, 150, 102, 4, ILI9341_DARKGREY);
    }
    else if ( selectWaveType == 3)
    {
        tft->fillRoundRect(164, 110, 150, 102, 4, ILI9341_DARKGREY);
    }

    tft->drawRoundRect(10, 4, 150, 102, 4, ILI9341_WHITE);
    tft->drawRoundRect(10, 110, 150, 102, 4, ILI9341_WHITE);
    tft->drawRoundRect(164, 4, 150, 102, 4, ILI9341_WHITE);
    tft->drawRoundRect(164, 110, 150, 102, 4, ILI9341_WHITE);
    
    waveIcons();

    bottomMenu2();
}

void Display::ADSRfaders()
{
    tft->fillRoundRect(11, 155 - attack, 73, 56, 4, ILI9341_WHITE);
    tft->fillRoundRect(87, 155 - decay, 73, 56, 4, ILI9341_WHITE);
    tft->fillRoundRect(163, 155 - sustain, 73, 56, 4, ILI9341_WHITE);
    tft->fillRoundRect(239, 155 - release, 73, 56, 4, ILI9341_WHITE);

    tft->setFont(Arial_12);
    tft->setTextColor(ILI9341_BLACK);

    tft->setCursor(44, 160 - attack);
    tft->print("A");
    tft->setCursor(120, 160 - decay);
    tft->print("D");
    tft->setCursor(196, 160 - sustain);
    tft->print("S");
    tft->setCursor(272, 160 - release);
    tft->print("R");
}

void Display::envelope()
{
    tft->fillRoundRect(11, 5, 73, 206, 4, CL(50, 50, 50));
    tft->fillRoundRect(87, 5, 73, 206, 4, CL(50, 50, 50));
    tft->fillRoundRect(163, 5, 73, 206, 4, CL(50, 50, 50));
    tft->fillRoundRect(239, 5, 73, 206, 4, CL(50, 50, 50));

    tft->drawFastVLine(48, 5, 206, ILI9341_BLACK);
    tft->drawFastVLine(124, 5, 206, ILI9341_BLACK);
    tft->drawFastVLine(200, 5, 206, ILI9341_BLACK);
    tft->drawFastVLine(276, 5, 206, ILI9341_BLACK);
    
    tft->drawRoundRect(10, 4, 75, 208, 4, ILI9341_WHITE);
    tft->drawRoundRect(86, 4, 75, 208, 4, ILI9341_WHITE);
    tft->drawRoundRect(162, 4, 75, 208, 4, ILI9341_WHITE);
    tft->drawRoundRect(238, 4, 75, 208, 4, ILI9341_WHITE);

    ADSRfaders();
    bottomMenu3();
}

void Display::update(Wave wave, Memory sdcard)
{
    tft->fillScreen(ILI9341_BLACK);

    if (menu == 0)
    {
        mainMenu(wave);
    }
    else if (menu == 1)
    {
        drawWave(wave);
    }
    else if (menu == 2)
    {
        selectWave(wave);
    }
    else if (menu == 3)
    {
        envelope();
    }
    else if (menu == 4)
    {
        saveWave(wave, sdcard);
    }
    tft->updateScreen();
}

void Display::changeScreen(Wave wave, Memory sdcard)
{
    tft->fillScreen(ILI9341_BLACK);

    if (menu == 0)
    {
        mainMenu(wave);
    }
    else if (menu == 1)
    {
        drawWave(wave);
    }
    else if (menu == 2)
    {
        selectWave(wave);
    }
    else if (menu == 3)
    {
        envelope();
    }
    else if (menu == 4)
    {
        saveWave(wave, sdcard);
    }
    tft->updateScreen();
    delay(500);
}

void Display::setConfirm()
{
    tft->fillRoundRect(106, 66, 112, 84, 6, ILI9341_WHITE);
    
    tft->setFont(Arial_16);
    tft->setTextColor(ILI9341_BLACK);
    tft->setCursor(145, 80);
    tft->print("Set");

    tft->drawLine(140, 120, 155, 135, ILI9341_GREEN);
    tft->drawLine(141, 120, 156, 135, ILI9341_GREEN);
    tft->drawLine(142, 120, 157, 135, ILI9341_GREEN);
    tft->drawLine(155, 135, 185, 110, ILI9341_GREEN);
    tft->drawLine(156, 135, 186, 110, ILI9341_GREEN);
    tft->drawLine(157, 135, 187, 110, ILI9341_GREEN);
}

void Display::onConfirm()
{
    tft->fillRoundRect(106, 66, 112, 84, 6, ILI9341_WHITE);
    
    tft->setFont(Arial_16);
    tft->setTextColor(ILI9341_BLACK);
    tft->setCursor(148, 80);
    tft->print("On");

    tft->drawCircle(162, 125, 12, ILI9341_GREEN);
    tft->drawCircle(162, 125, 11, ILI9341_GREEN);
    tft->drawCircle(162, 125, 10, ILI9341_GREEN);
    tft->drawFastVLine(161, 109, 15, ILI9341_GREEN);
    tft->drawFastVLine(162, 109, 15, ILI9341_GREEN);
    tft->drawFastVLine(163, 109, 15, ILI9341_GREEN);
}

void Display::offConfirm()
{
    tft->fillRoundRect(106, 66, 112, 84, 6, ILI9341_WHITE);
    
    tft->setFont(Arial_16);
    tft->setTextColor(ILI9341_BLACK);
    tft->setCursor(145, 80);
    tft->print("Off");

    tft->drawCircle(162, 125, 12, ILI9341_RED);
    tft->drawCircle(162, 125, 11, ILI9341_RED);
    tft->drawCircle(162, 125, 10, ILI9341_RED);
    tft->drawFastVLine(161, 109, 15, ILI9341_RED);
    tft->drawFastVLine(162, 109, 15, ILI9341_RED);
    tft->drawFastVLine(163, 109, 15, ILI9341_RED);
}

void Display::saveConfirm()
{
    tft->fillRoundRect(106, 66, 112, 84, 6, ILI9341_WHITE);
    
    tft->setFont(Arial_16);
    tft->setTextColor(ILI9341_BLACK);
    tft->setCursor(131, 80);
    tft->print("Saved");

    tft->drawLine(140, 120, 155, 135, ILI9341_GREEN);
    tft->drawLine(141, 120, 156, 135, ILI9341_GREEN);
    tft->drawLine(142, 120, 157, 135, ILI9341_GREEN);
    tft->drawLine(155, 135, 185, 110, ILI9341_GREEN);
    tft->drawLine(156, 135, 186, 110, ILI9341_GREEN);
    tft->drawLine(157, 135, 187, 110, ILI9341_GREEN);
}

void Display::updateSet(Wave wave, Memory sdcard)
{
    tft->fillScreen(ILI9341_BLACK);

    if (menu == 0)
    {
        mainMenu(wave);
    }
    else if (menu == 1)
    {
        drawWave(wave);
        setConfirm();
    }
    else if (menu == 2)
    {
        selectWave(wave);
        if (selectWaveOn)
        {
            onConfirm();
        }
        else if (!selectWaveOn)
        {
            offConfirm();
        }
    }
    else if (menu == 3)
    {
        envelope();
        if (envelopeOn)
        {
            onConfirm();
        }
        else if (!envelopeOn)
        {
            offConfirm();
        }
    }
    else if (menu == 4)
        {
            saveWave(wave, sdcard);
            saveConfirm();
        }
    tft->updateScreen();
    delay(1000);
}