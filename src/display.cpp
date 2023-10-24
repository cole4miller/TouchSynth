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
    tft->drawFastHLine(162, 108, 152, ILI9341_WHITE);
    tft->drawFastHLine(162, 134, 151, CL(50, 50, 50));
    tft->drawFastHLine(162, 160, 151, CL(100, 100, 100));
    tft->drawFastHLine(162, 186, 151, CL(50, 50, 50));
    tft->drawFastHLine(162, 212, 152, ILI9341_WHITE);
    
    // Grid vertical lines
    tft->drawFastVLine(162, 108, 104, ILI9341_WHITE);
    tft->drawFastVLine(200, 108, 103, CL(50, 50, 50));
    tft->drawFastVLine(238, 108, 103, CL(100, 100, 100));
    tft->drawFastVLine(276, 108, 103, CL(50, 50, 50));
    tft->drawFastVLine(314, 108, 104, ILI9341_WHITE);

    // Wave form
    if (drawWaveOn)
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
        /*
        for (int i = 0; i < 303; i++)
        {
            if (wave.customPointUsed[i])
            {
                //tft->fillRoundRect((i + 10), (107 - wave.customWaveY[i]), 2, 2, 0, ILI9341_WHITE);
                tft->drawPixel(((i / 2) + 163), (160 - (wave.customWaveY[i] / 2)), ILI9341_WHITE);
                i++;
            }
        }
        */
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
        
        
        /*
        int xprev = 50;
        for (int i = wave.selectWaveXstart + 4; i <= wave.selectWaveXend; i++)
        {
            if (wave.selectPointUsed[i])
            {
                tft->drawLine(((xprev / 2.0) + 163), (160 - wave.selectWaveY[xprev] / 2.0), ((i / 2.0) + 163), 160 - wave.selectWaveY[i] / 2.0, ILI9341_WHITE);                
                xprev = i;
                i = i + 3;
            }
        }
        */
        /*
        for (int i = 0; i < 303; i++)
        {
            if (wave.selectPointUsed[i])
            {
                //tft->fillRoundRect((i + 10), (107 - wave.selectWaveY[i]), 2, 2, 0, ILI9341_WHITE);
                tft->drawPixel(((i / 2) + 163), (160 - (wave.selectWaveY[i] / 2)), ILI9341_WHITE);
                i++;
            }
        }
        */
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

// Draw wave screen
void Display::bottomMenu1()
{
    // Button text bubble
    tft->fillRoundRect(32, 217, 84, 20, 2, ILI9341_LIGHTGREY);
    tft->fillRoundRect(120, 217, 84, 20, 2, ILI9341_MAGENTA);
    tft->fillRoundRect(208, 217, 84, 20, 2, ILI9341_DARKGREEN);
   
    // Button text
    tft->setFont(Arial_9);
    tft->setTextColor(ILI9341_BLACK);
    
    tft->setCursor(55, 222);
    tft->print("Back");

    tft->setCursor(140, 222);
    tft->print("Clear");

    tft->setCursor(234, 222);
    tft->print("Set");
}

// Select wave screen
void Display::bottomMenu2()
{
    // Button text bubble
    tft->fillRoundRect(32, 217, 84, 20, 2, ILI9341_LIGHTGREY);
   
    // Button text
    tft->setFont(Arial_9);
    tft->setTextColor(ILI9341_BLACK);
    
    tft->setCursor(55, 222);
    tft->print("Back");

    if (selectWaveOn) {
        tft->fillRoundRect(208, 217, 84, 20, 2, ILI9341_DARKGREEN);
        tft->setCursor(236, 222);
        tft->print("On");  
    }
    else if (!selectWaveOn) {
        tft->fillRoundRect(208, 217, 84, 20, 2, ILI9341_LIGHTGREY);
        tft->setCursor(234, 222);
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
    
    tft->setCursor(55, 222);
    tft->print("Back");

    tft->setCursor(140, 222);
    tft->print("Reset");

    if (envelopeOn) {
        tft->fillRoundRect(208, 217, 84, 20, 2, ILI9341_DARKGREEN);
        tft->setCursor(236, 222);
        tft->print("On");  
    }
    else if (!envelopeOn) {
        tft->fillRoundRect(208, 217, 84, 20, 2, ILI9341_LIGHTGREY);
        tft->setCursor(234, 222);
        tft->print("Off");
    }
    
}

void Display::drawWave(Wave wave)
{
    drawGrid();
    bottomMenu1();
    int xprev = wave.waveXstart;
    
    for (int i = wave.waveXstart + 2; i <= wave.waveXend; i++)
    {
        if (wave.pointUsed[i])
        {
            tft->drawLine((xprev + 11), (108 - wave.waveY[xprev]), (i + 11), 108 - wave.waveY[i], ILI9341_WHITE);
            xprev = i;
            i++;
        }
    }
    

    /*
    for (int i = 0; i < 303; i++)
    {
        if (wave.pointUsed[i])
        {
            tft->fillRoundRect((i + 10), (107 - wave.waveY[i]), 2, 2, 0, ILI9341_WHITE);
            //tft->drawPixel((i + 11), (108 - wave.waveY[i]), ILI9341_WHITE);
        }
    }
    */
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
        //tft->drawPixel((220 + i), 56 + 20.0 * sin((2 * M_PI * i) / 36), ILI9341_BLACK);
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

void Display::update(Wave wave)
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

    tft->updateScreen();
}

void Display::setConfirm()
{
    tft->fillRoundRect(86, 56, 152, 104, 6, ILI9341_WHITE);
    
    tft->setFont(Arial_9);
    tft->setTextColor(ILI9341_BLACK);
    tft->setCursor(130, 100);
    tft->print("Set");

    delay(4000);
}


void Display::updateSet(Wave wave)
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
    }
    else if (menu == 3)
    {
        envelope();
    }

    tft->updateScreen();
}