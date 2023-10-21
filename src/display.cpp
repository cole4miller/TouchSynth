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

void Display::mainMenu()
{
    tft->setFont(Arial_18);
    tft->setCursor(90, 20);
    tft->setTextColor(ILI9341_WHITE);
    tft->print("TouchSynth");

    tft->setFont(Arial_14);
    tft->drawRoundRect(40, 60, 240, 50, 4, ILI9341_WHITE);
    tft->setCursor(110, 78);
    tft->print("Draw Wave");
    tft->drawRoundRect(40, 120, 240, 50, 4, ILI9341_WHITE);
    tft->setCursor(105, 138);
    tft->print("Select Wave");
    tft->drawRoundRect(40, 180, 240, 50, 4, ILI9341_WHITE);
    tft->setCursor(115, 198);
    tft->print("Envelope");
}

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

    for (int i = 0; i < 303; i++)
    {
        if (wave.pointUsed[i])
        {
            tft->drawPixel((i + 11), (108 - wave.waveY[i]), ILI9341_WHITE);
        }
    }
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
    for (int i = 0; i < 37; i++)
    {
        tft->drawPixel((220 + i), 56 + 20.0 * sin((2 * M_PI * i) / 36), ILI9341_BLACK);
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
        mainMenu();
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