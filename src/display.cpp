#include "display.h"

Display::Display(int16_t *data1, int16_t *data2, ILI9341_t3n *screen)
    : tft(screen)
{
    data[0] = data1;    // Gate
    data[1] = data2;    // Freq
    tft->begin();
    tft->fillScreen(ILI9341_BLACK);

    tft->useFrameBuffer(true);

    tft->setRotation(1);
}

int Display::checkTrig()
{
    u_int16_t count = 0;
    for (int i = 1; i < BUFFER_SIZE; i++)
    {
        // Gate should be ~5 V out of +/- 10V input range
        // data[0] array in range +/- ~1650 mV (0-3.3V shifted to -1.65-1.65V)
        // 5V input ~825 mV from ADC, so 600 mV gives some leeway
        // if (data[0][i] > (600 * trigLevel / 100) && data[0][i-1] < (600 * trigLevel / 100))  
        
        if (data[0][i] > (600 * trigLevel / 100)) 
        {                       
            count++;
            //return i;
        }
        if (count > 1000)
        {
            return i;
        }
    }
    return BUFFER_SIZE;
}

double Display::getFreq(int sample)
{
    int noteIndex = round((data[1][sample] - 7) / -13.8);
    //int noteIndex = round((data[1][sample] - 1650.0) * ((16.5 + 84.5) / 16.5) / 83.3333) - 1;
    adccount++;
    adctotal = adctotal + data[1][sample];
    Serial.print("adc in:  ");
    Serial.println(adctotal/adccount);
    if (noteIndex < 0)
    {
        noteIndex = 0;
    }
    else if (noteIndex > 84)
    {
        noteIndex = 84;
    }
    double freq = noteArray[noteIndex];
    return freq;
}

// draws gridlines for wave draw window
void Display::drawGrid()
{
    // horizontal lines
    tft->drawFastHLine(9, 3, 306, textColor);
    tft->drawFastHLine(10, 4, 304, textColor);
    tft->drawFastHLine(10, 30, 304, secondColor);
    tft->drawFastHLine(10, 56, 304, secondColor);
    tft->drawFastHLine(10, 82, 304, secondColor);
    tft->drawFastHLine(10, 108, 304, thirdColor);
    tft->drawFastHLine(10, 134, 304, secondColor);
    tft->drawFastHLine(10, 160, 304, secondColor);
    tft->drawFastHLine(10, 186, 304, secondColor);
    tft->drawFastHLine(10, 212, 304, textColor);
    tft->drawFastHLine(9, 213, 306, textColor);

    // vertical lines
    tft->drawFastVLine(9, 3, 211, textColor);
    tft->drawFastVLine(10, 4, 209, textColor);
    tft->drawFastVLine(48, 5, 207, secondColor);
    tft->drawFastVLine(86, 5, 207, secondColor);
    tft->drawFastVLine(124, 5, 207, secondColor);
    tft->drawFastVLine(162, 5, 207, thirdColor);
    tft->drawFastVLine(200, 5, 207, secondColor);
    tft->drawFastVLine(238, 5, 207, secondColor);
    tft->drawFastVLine(276, 5, 207, secondColor);
    tft->drawFastVLine(314, 4, 209, textColor);
    tft->drawFastVLine(315, 3, 211, textColor);
}

void Display::mainMenu(Wave wave)
{
    // TouchSynth Title/Logo
    tft->drawFastHLine(10, 71, 304, textColor);
    tft->drawFastHLine(10, 72, 304, textColor);
    tft->drawFastHLine(10, 70, 304, textColor);
    for (int i = 0; i < 252; i+=4)
    {
        tft->drawLine((34 + i), 72 - 21.0 * sin((2 * M_PI * i) / 63.0), 38 + i, 72 - 21.0 * sin((2 * M_PI * (i + 5)) / 63.0), CL(255 - i, i, 255 - i));
        tft->drawLine((35 + i), 72 - 21.0 * sin((2 * M_PI * i) / 63.0), 39 + i, 72 - 21.0 * sin((2 * M_PI * (i + 5)) / 63.0), CL(255 - i, i, 255 - i));
        tft->drawLine((36 + i), 72 - 21.0 * sin((2 * M_PI * i) / 63.0), 40 + i, 72 - 21.0 * sin((2 * M_PI * (i + 5)) / 63.0), CL(255 - i, i, 255 - i));
        tft->drawLine((37 + i), 72 - 21.0 * sin((2 * M_PI * i) / 63.0), 41 + i, 72 - 21.0 * sin((2 * M_PI * (i + 5)) / 63.0), CL(255 - i, i, 255 - i));
        tft->drawLine((38 + i), 72 - 21.0 * sin((2 * M_PI * i) / 63.0), 42 + i, 72 - 21.0 * sin((2 * M_PI * (i + 5)) / 63.0), CL(255 - i, i, 255 - i));
        tft->drawLine((34 + i), 72 - 22.0 * sin((2 * M_PI * i) / 63.0), 38 + i, 72 - 22.0 * sin((2 * M_PI * (i + 5)) / 63.0), CL(255 - i, i, 255 - i));
        tft->drawLine((35 + i), 72 - 22.0 * sin((2 * M_PI * i) / 63.0), 39 + i, 72 - 22.0 * sin((2 * M_PI * (i + 5)) / 63.0), CL(255 - i, i, 255 - i));
        tft->drawLine((36 + i), 72 - 22.0 * sin((2 * M_PI * i) / 63.0), 40 + i, 72 - 22.0 * sin((2 * M_PI * (i + 5)) / 63.0), CL(255 - i, i, 255 - i));
        tft->drawLine((37 + i), 72 - 22.0 * sin((2 * M_PI * i) / 63.0), 41 + i, 72 - 22.0 * sin((2 * M_PI * (i + 5)) / 63.0), CL(255 - i, i, 255 - i));
        tft->drawLine((38 + i), 72 - 22.0 * sin((2 * M_PI * i) / 63.0), 42 + i, 72 - 22.0 * sin((2 * M_PI * (i + 5)) / 63.0), CL(255 - i, i, 255 - i));
        tft->drawLine((35 + i), 72 - 23.0 * sin((2 * M_PI * i) / 63.0), 39 + i, 72 - 23.0 * sin((2 * M_PI * (i + 5)) / 63.0), CL(255 - i, i, 255 - i));
        tft->drawLine((36 + i), 72 - 23.0 * sin((2 * M_PI * i) / 63.0), 40 + i, 72 - 23.0 * sin((2 * M_PI * (i + 5)) / 63.0), CL(255 - i, i, 255 - i));
        tft->drawLine((37 + i), 72 - 23.0 * sin((2 * M_PI * i) / 63.0), 41 + i, 72 - 23.0 * sin((2 * M_PI * (i + 5)) / 63.0), CL(255 - i, i, 255 - i));
    }
    
    tft->setFont(Arial_40);
    tft->setCursor(162, 30, true);
    tft->setTextColor(textColor);
    tft->print("TouchSynth");

    tft->setTextColor(textColor);
    tft->setFont(Arial_14);

    // Menu buttons
    tft->fillRoundRect(46, 103, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 105, 228, 27, 4, secondColor);
    tft->setCursor(128, 118, true);
    tft->print("Draw Wave");
    tft->fillRoundRect(46, 136, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 138, 228, 27, 4, secondColor);
    tft->setCursor(128, 151, true);
    tft->print("Select Wave");
    tft->fillRoundRect(46, 169, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 171, 228, 27, 4, secondColor);
    tft->setCursor(128, 185, true);
    tft->print("Sequencer");
    tft->fillRoundRect(46, 202, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 204, 228, 27, 4, secondColor);
    tft->setCursor(128, 218, true);
    tft->print("Settings");
    
    // On/Off sliders
    tft->setTextColor(ILI9341_BLACK);
    tft->setFont(Arial_8);
    if(drawWaveOn)
    {
        tft->fillRect(219, 106, 32, 25, textColor);
        tft->fillCircle(220, 118, 11, textColor);
        tft->fillCircle(250, 118, 11, textColor);
        tft->fillRect(220, 108, 30, 21, ILI9341_GREEN);
        tft->fillCircle(220, 118, 9, ILI9341_GREEN);
        tft->fillCircle(250, 118, 9, ILI9341_GREEN);
        tft->fillCircle(250, 118, 7, ILI9341_LIGHTGREY);
        tft->setCursor(227, 118, true);
        tft->print("ON");
    }
    else{
        tft->fillRect(219, 106, 32, 25, textColor);
        tft->fillCircle(220, 118, 11, textColor);
        tft->fillCircle(250, 118, 11, textColor);
        tft->fillRect(220, 108, 30, 21, ILI9341_DARKGREY);
        tft->fillCircle(220, 118, 9, ILI9341_DARKGREY);
        tft->fillCircle(250, 118, 9, ILI9341_DARKGREY);
        tft->fillCircle(220, 118, 7, ILI9341_LIGHTGREY);
        tft->setCursor(243, 118, true);
        tft->print("OFF");
    }
    if(selectWaveOn)
    {
        tft->fillRect(219, 139, 32, 25, textColor);
        tft->fillCircle(220, 151, 11, textColor);
        tft->fillCircle(250, 151, 11, textColor);
        tft->fillRect(220, 141, 30, 21, ILI9341_GREEN);
        tft->fillCircle(220, 151, 9, ILI9341_GREEN);
        tft->fillCircle(250, 151, 9, ILI9341_GREEN);
        tft->fillCircle(250, 151, 7, ILI9341_LIGHTGREY);
        tft->setCursor(227, 151, true);
        tft->print("ON");
    }
    else{
        tft->fillRect(219, 139, 32, 25, textColor);
        tft->fillCircle(220, 151, 11, textColor);
        tft->fillCircle(250, 151, 11, textColor);
        tft->fillRect(220, 141, 30, 21, ILI9341_DARKGREY);
        tft->fillCircle(220, 151, 9, ILI9341_DARKGREY);
        tft->fillCircle(250, 151, 9, ILI9341_DARKGREY);
        tft->fillCircle(220, 151, 7, ILI9341_LIGHTGREY);
        tft->setCursor(243, 151, true);
        tft->print("OFF");
    }
    if(seqOn)
    {
        tft->fillRect(219, 172, 32, 25, textColor);
        tft->fillCircle(220, 184, 11, textColor);
        tft->fillCircle(250, 184, 11, textColor);
        tft->fillRect(220, 174, 30, 21, ILI9341_GREEN);
        tft->fillCircle(220, 184, 9, ILI9341_GREEN);
        tft->fillCircle(250, 184, 9, ILI9341_GREEN);
        tft->fillCircle(250, 184, 7, ILI9341_LIGHTGREY);
        tft->setCursor(227, 184, true);
        tft->print("ON");
    }
    else{
        tft->fillRect(219, 172, 32, 25, textColor);
        tft->fillCircle(220, 184, 11, textColor);
        tft->fillCircle(250, 184, 11, textColor);
        tft->fillRect(220, 174, 30, 21, ILI9341_DARKGREY);
        tft->fillCircle(220, 184, 9, ILI9341_DARKGREY);
        tft->fillCircle(250, 184, 9, ILI9341_DARKGREY);
        tft->fillCircle(220, 184, 7, ILI9341_LIGHTGREY);
        tft->setCursor(243, 184, true);
        tft->print("OFF");
    }
}

void Display::saveText()
{
    tft->setFont(Arial_18);
    tft->setTextColor(textColor);
    tft->setCursor(18, 16);
    if (saveLoad)
    {
        tft->print("Load Wave");
    }
    else if (!saveLoad)
    {
        tft->print("Save Wave");
    }
    
    tft->fillRoundRect(55, 46, 54, 54, 3, ILI9341_WHITE);
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
    // Grid horizontal lines
    tft->drawFastHLine(162, 30, 151, secondColor);
    tft->drawFastHLine(162, 56, 151, thirdColor);
    tft->drawFastHLine(162, 82, 151, secondColor);
    
    // Grid vertical lines
    tft->drawFastVLine(200, 4, 103, secondColor);
    tft->drawFastVLine(238, 4, 103, thirdColor);
    tft->drawFastVLine(276, 4, 103, secondColor);

    tft->drawRoundRect(162, 4, 152, 104, 4, textColor);

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
            tft->drawLine(((xprev / 2.0) + 163), (56 - wave.previewWaveY[xprev] / 2.0), ((i / 2.0) + 163), 56 - wave.previewWaveY[i] / 2.0, textColor);
            xprev = i;
            i = i + 3;
        }
    }
}

void Display::saveWave(Wave wave, Memory sdcard)
{
    // Button borders
    tft->fillRoundRect(5, 3, 154, 106, 4, textColor);
    tft->fillRoundRect(161, 3, 154, 106, 4, textColor);

    tft->fillRoundRect(5, 111, 76, 50, 4, textColor);
    tft->fillRoundRect(83, 111, 76, 50, 4, textColor);
    tft->fillRoundRect(161, 111, 76, 50, 4, textColor);
    tft->fillRoundRect(239, 111, 76, 50, 4, textColor);
    tft->fillRoundRect(5, 163, 76, 50, 4, textColor);
    tft->fillRoundRect(83, 163, 76, 50, 4, textColor);
    tft->fillRoundRect(161, 163, 76, 50, 4, textColor);
    tft->fillRoundRect(239, 163, 76, 50, 4, textColor);

    // Button fill
    tft->fillRoundRect(7, 5, 150, 102, 4, secondColor);
    tft->fillRoundRect(163, 5, 150, 102, 4, backgroundColor);
    
    tft->fillRoundRect(7, 113, 72, 46, 4, secondColor);
    tft->fillRoundRect(85, 113, 72, 46, 4, secondColor);
    tft->fillRoundRect(163, 113, 72, 46, 4, secondColor);
    tft->fillRoundRect(241, 113, 72, 46, 4, secondColor);
    tft->fillRoundRect(7, 165, 72, 46, 4, secondColor);
    tft->fillRoundRect(85, 165, 72, 46, 4, secondColor);
    tft->fillRoundRect(163, 165, 72, 46, 4, secondColor);
    tft->fillRoundRect(241, 165, 72, 46, 4, secondColor);

    if (saveFile == 1)
    {
        tft->fillRoundRect(7, 113, 72, 46, 4, thirdColor);
    }
    else if (saveFile == 2)
    {
        tft->fillRoundRect(85, 113, 72, 46, 4, thirdColor);
    }
    else if (saveFile == 3)
    {
        tft->fillRoundRect(163, 113, 72, 46, 4, thirdColor);
    }
    else if (saveFile == 4)
    {
        tft->fillRoundRect(241, 113, 72, 46, 4, thirdColor);
    }
    else if (saveFile == 5)
    {
        tft->fillRoundRect(7, 165, 72, 46, 4, thirdColor);
    }
    else if (saveFile == 6)
    {
        tft->fillRoundRect(85, 165, 72, 46, 4, thirdColor);
    }
    else if (saveFile == 7)
    {
        tft->fillRoundRect(163, 165, 72, 46, 4, thirdColor);
    }
    else if (saveFile == 8)
    {
        tft->fillRoundRect(241, 165, 72, 46, 4, thirdColor);
    }

    drawSave(wave, sdcard);
    saveText();
    bottomMenu4();
}

// Draw wave screen
void Display::bottomMenu1(Wave wave)
{
    // Button text bubble
    tft->fillRoundRect(11, 216, 74, 22, 2, textColor);
    tft->fillRoundRect(13, 218, 70, 18, 2, ILI9341_LIGHTGREY);
    tft->fillRoundRect(87, 216, 74, 22, 2, textColor);
    tft->fillRoundRect(89, 218, 70, 18, 2, ILI9341_MAGENTA);
    tft->fillRoundRect(163, 216, 74, 22, 2, textColor);
    tft->fillRoundRect(165, 218, 70, 18, 2, ILI9341_DARKGREEN);
    tft->fillRoundRect(239, 216, 74, 22, 2, textColor);
    tft->fillRoundRect(241, 218, 70, 18, 2, ILI9341_CYAN);

    // Button text
    tft->setFont(Arial_9);
    tft->setTextColor(ILI9341_BLACK);
   
    if (waveOptions)
    {
        tft->fillRoundRect(162, 108, 152, 104, 0, ILI9341_LIGHTGREY);
        tft->drawRoundRect(162, 108, 152, 104, 0, textColor);
        tft->drawRoundRect(161, 107, 154, 106, 0, textColor);
        tft->drawFastHLine(162, 134, 152, textColor);
        tft->drawFastHLine(162, 135, 152, textColor);
        tft->drawFastHLine(162, 160, 152, textColor);
        tft->drawFastHLine(162, 161, 152, textColor);
        tft->drawFastHLine(162, 186, 152, textColor);
        tft->drawFastHLine(162, 187, 152, textColor);
        tft->fillTriangle(276, 216, 272, 212, 280, 212, textColor);
        tft->setCursor(180, 116);
        if (smoothLevel == 1) 
        {
            tft->print("Smooth:      Low");
        }
        else if (smoothLevel == 2)
        {
            tft->print("Smooth:      High");
        }
        else if (smoothLevel == 0)
        {
            tft->print("Smooth:       Off");
        }

        tft->setCursor(180, 143);
        tft->print("Save");

        tft->setCursor(180, 169);
        tft->print("Load");

        tft->setCursor(180, 194);
        tft->print("Draw:    L            R");
        tft->drawFastHLine(247, 198, 23, ILI9341_BLACK);
        tft->drawFastHLine(247, 199, 23, ILI9341_BLACK);
        tft->drawFastHLine(247, 200, 23, ILI9341_BLACK);
        if (!wave.drawLR)
        {
            tft->fillTriangle(242, 199, 250, 195, 250, 203, ILI9341_BLACK);
        }
        tft->fillTriangle(278, 199, 270, 195, 270, 203, ILI9341_BLACK);
    }
    
    tft->setCursor(33, 221);
    tft->print("Back");

    tft->setCursor(108, 221);
    tft->print("Clear");

    tft->setCursor(189, 221);
    tft->print("Set");

    
    if (waveOptions)
    {
        tft->setCursor(276, 227, true);
        tft->print("Close");
    }
    else
    {
        tft->setCursor(276, 229, true);
        tft->print("Options");
    }  
}

// Select wave screen
void Display::bottomMenu2()
{
    // Button text bubble
    tft->fillRoundRect(30, 215, 88, 24, 2, textColor);
    tft->fillRoundRect(206, 215, 88, 24, 2, textColor);
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
}

// Save screen
void Display::bottomMenu4()
{
    // Button text bubble
    tft->fillRoundRect(5, 216, 102, 22, 4, textColor);
    tft->fillRoundRect(109, 216, 102, 22, 4, textColor);
    tft->fillRoundRect(213, 216, 102, 22, 4, textColor);
    tft->fillRoundRect(7, 218, 98, 18, 4, ILI9341_LIGHTGREY);
    tft->fillRoundRect(111, 218, 98, 18, 4, ILI9341_MAGENTA);
    tft->fillRoundRect(215, 218, 98, 18, 4, ILI9341_DARKGREEN);
   
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

// Sequencer screen
void Display::bottomMenu5()
{
    // Button text bubble
    tft->fillRoundRect(11, 216, 74, 22, 2, textColor);
    tft->fillRoundRect(13, 218, 70, 18, 2, ILI9341_LIGHTGREY);
    tft->fillRoundRect(87, 216, 74, 22, 2, textColor);
    tft->fillRoundRect(89, 218, 70, 18, 2, ILI9341_MAGENTA);
    tft->fillRoundRect(163, 216, 74, 22, 2, textColor);
    tft->fillRoundRect(239, 216, 74, 22, 2, textColor);
    tft->fillRoundRect(241, 218, 70, 18, 2, ILI9341_CYAN);
   
    // Button text
    tft->setFont(Arial_9);
    tft->setTextColor(ILI9341_BLACK);
    
    tft->setCursor(33, 221);
    tft->print("Back");

    tft->setCursor(108, 221);
    tft->print("Reset");

    tft->setCursor(189, 222);
    if (seqOn) 
    {
        tft->fillRoundRect(165, 218, 70, 18, 2, ILI9341_DARKGREEN);
        tft->print("On");  
    }
    else if (!seqOn) 
    {
        tft->fillRoundRect(165, 218, 70, 18, 2, ILI9341_LIGHTGREY);
        tft->print("Off");
    }

    tft->setCursor(276, 227, true);
    tft->print("Gate");
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
                tft->drawLine((xprev + 11), (108 - wave.smoothWaveY[xprev]), (i + 11), 108 - wave.smoothWaveY[i], textColor);
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
                tft->drawLine((xprev + 11), (108 - wave.waveY[xprev]), (i + 11), 108 - wave.waveY[i], textColor);
                xprev = i;
                i++;
            }
        }
    }
    bottomMenu1(wave);
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
    // Outlines
    tft->fillRoundRect(10, 4, 150, 102, 4, textColor);
    tft->fillRoundRect(10, 110, 150, 102, 4, textColor);
    tft->fillRoundRect(164, 4, 150, 102, 4, textColor);
    tft->fillRoundRect(164, 110, 150, 102, 4, textColor);

    // Fill
    tft->fillRoundRect(12, 6, 146, 98, 4, thirdColor);
    tft->fillRoundRect(166, 6, 146, 98, 4, thirdColor);
    tft->fillRoundRect(12, 112, 146, 98, 4, thirdColor);
    tft->fillRoundRect(166, 112, 146, 98, 4, thirdColor);
    if ( selectWaveType == 0)
    {
        tft->fillRoundRect(12, 6, 146, 98, 4, secondColor);
    }
    else if ( selectWaveType == 1)
    {
        tft->fillRoundRect(166, 6, 146, 98, 4, secondColor);
    }
    else if ( selectWaveType == 2)
    {
        tft->fillRoundRect(12, 112, 146, 98, 4, secondColor);
    }
    else if ( selectWaveType == 3)
    {
        tft->fillRoundRect(166, 112, 146, 98, 4, secondColor);
    }
    
    waveIcons();

    bottomMenu2();
}

void Display::settings()
{
    tft->setFont(Arial_28);
    tft->setCursor(162, 30, true);
    tft->setTextColor(textColor);
    tft->print("TouchSettings");

    tft->setTextColor(textColor);
    tft->setFont(Arial_14);
    
    // Menu buttons
    tft->fillRoundRect(46, 70, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 72, 228, 27, 4, secondColor);
    tft->setCursor(162, 87, true);
    tft->print("Pitch Tuning");
    tft->fillRoundRect(46, 103, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 105, 228, 27, 4, secondColor);
    tft->setCursor(162, 119, true);
    tft->print("Trigger Level");
    tft->fillRoundRect(46, 136, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 138, 228, 27, 4, secondColor);
    tft->setCursor(162, 153, true);
    tft->print("Light / Dark Mode");
    tft->fillRoundRect(46, 169, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 171, 228, 27, 4, secondColor);
    tft->setCursor(162, 184, true);
    tft->print("Credits");
    tft->fillRoundRect(46, 202, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 204, 228, 27, 4, secondColor);
    tft->setCursor(162, 217, true);
    tft->print("Back");
}

void Display::tuneInput()
{
    tft->setTextColor(textColor);
    tft->setFont(Arial_28);
    tft->setCursor(162, 30, true);
    tft->print("Pitch Tuning");
    tft->setFont(Arial_20);
    tft->setCursor(162, 70, true);
    tft->print("Adjust 1 V/Oct Input");

    tft->fillRoundRect(10, 108, 304, 52, 4, textColor);
    tft->fillRoundRect(12, 110, 300, 48, 4, secondColor);
    tft->drawFastHLine(12, 134, 300, ILI9341_BLACK);

    tft->fillRoundRect(12 + pitchTune, 110, 100, 48, 4, thirdColor);
    tft->drawRoundRect(12 + pitchTune, 110, 100, 48, 4, backgroundColor);
    tft->drawFastVLine(55 + pitchTune, 123, 22, backgroundColor);
    tft->drawFastVLine(62 + pitchTune, 120, 28, backgroundColor);
    tft->drawFastVLine(69 + pitchTune, 123, 22, backgroundColor);

    tft->setFont(Arial_14);
    tft->fillRoundRect(46, 169, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 171, 228, 27, 4, secondColor);
    tft->setCursor(162, 185, true);
    tft->print("Reset");
    
    tft->fillRoundRect(46, 202, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 204, 228, 27, 4, secondColor);
    tft->setCursor(162, 217, true);
    tft->print("Back");
}

void Display::triggerSens()
{
    tft->setTextColor(textColor);
    tft->setFont(Arial_28);
    tft->setCursor(162, 30, true);
    tft->print("Trigger Level");
    tft->setFont(Arial_16);
    tft->setCursor(162, 70, true);
    tft->print("Adjust Trigger Input Sensitivity");

    tft->fillRoundRect(10, 108, 304, 52, 4, textColor);
    tft->fillRoundRect(12, 110, 300, 48, 4, secondColor);
    tft->drawFastHLine(12, 134, 300, ILI9341_BLACK);

    tft->fillRoundRect(12 + trigLevel, 110, 100, 48, 4, thirdColor);
    tft->drawRoundRect(12 + trigLevel, 110, 100, 48, 4, backgroundColor);
    tft->drawFastVLine(55 + trigLevel, 123, 22, backgroundColor);
    tft->drawFastVLine(62 + trigLevel, 120, 28, backgroundColor);
    tft->drawFastVLine(69 + trigLevel, 123, 22, backgroundColor);

    tft->setFont(Arial_14);
    tft->fillRoundRect(46, 169, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 171, 228, 27, 4, secondColor);
    tft->setCursor(162, 185, true);
    tft->print("Reset");
    tft->fillRoundRect(46, 202, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 204, 228, 27, 4, secondColor);
    tft->setCursor(162, 217, true);
    tft->print("Back");
}

void Display::credits()
{
    tft->setTextColor(textColor);
    tft->setFont(Arial_28);
    tft->setCursor(162, 25, true);
    tft->print("Credits");

    tft->setFont(Arial_18);
    tft->setCursor(162, 60, true);
    tft->print("Made By:");

    tft->setFont(Arial_16);
    tft->setCursor(162, 85, true);
    tft->print("Ai'Dan Van Iv, Michael Laun,");
    tft->setCursor(162, 110, true);
    tft->print("Cole Miller, Blake Roberts");

    tft->setFont(Arial_18);
    tft->setCursor(162, 140, true);
    tft->print("Special Thanks To:");

    tft->setFont(Arial_14);
    tft->setCursor(162, 164, true);
    tft->print("Don Heer, Rachael Cate,");
    tft->setCursor(162, 185, true);
    tft->print("Connor Moyce, Daft Punk");
    
    tft->setFont(Arial_14);
    tft->fillRoundRect(46, 202, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 204, 228, 27, 4, secondColor);
    tft->setCursor(162, 217, true);
    tft->print("Back");
}

void Display::seqText()
{
    tft->setFont(Arial_18);
    tft->setTextColor(textColor);
    tft->setCursor(82, 26, true);
    tft->print("Sequencer");

    tft->drawFastHLine(15, 48, 132, textColor);
    tft->drawFastHLine(15, 58, 132, textColor);
    tft->drawFastHLine(15, 68, 132, textColor);
    tft->drawFastHLine(15, 78, 132, textColor);
    tft->drawFastHLine(15, 88, 132, textColor);
    tft->drawFastVLine(15, 48, 40, textColor);
    tft->drawFastVLine(16, 48, 40, textColor);
    tft->drawFastVLine(19, 48, 40, textColor);
    tft->drawFastVLine(18, 48, 40, textColor);
    tft->drawFastVLine(82, 48, 40, textColor);
    tft->drawFastVLine(81, 48, 40, textColor);

    // First bar notes
    tft->fillCircle(30, 73, 5, textColor);
    tft->drawFastVLine(34, 53, 20, textColor);
    tft->drawFastVLine(35, 53, 20, textColor);
    tft->fillCircle(43, 83, 5, textColor);
    tft->drawFastVLine(47, 63, 20, textColor);
    tft->drawFastVLine(48, 63, 20, textColor);
    tft->fillCircle(56, 68, 5, textColor);
    tft->drawFastVLine(60, 48, 20, textColor);
    tft->drawFastVLine(61, 48, 20, textColor);
    tft->fillCircle(69, 78, 5, textColor);
    tft->drawFastVLine(73, 58, 20, textColor);
    tft->drawFastVLine(74, 58, 20, textColor);

    // Second bar notes
    tft->fillCircle(93, 63, 5, textColor);
    tft->drawFastVLine(97, 43, 20, textColor);
    tft->drawFastVLine(98, 43, 20, textColor);
    tft->fillCircle(106, 83, 5, textColor);
    tft->drawFastVLine(110, 63, 20, textColor);
    tft->drawFastVLine(111, 63, 20, textColor);
    tft->fillCircle(119, 68, 5, textColor);
    tft->drawFastVLine(123, 48, 20, textColor);
    tft->drawFastVLine(124, 48, 20, textColor);
    tft->fillCircle(132, 78, 5, textColor);
    tft->drawFastVLine(136, 58, 20, textColor);
    tft->drawFastVLine(137, 58, 20, textColor);

    tft->setFont(Arial_16);
    tft->setCursor(238, 38, true);
    tft->print("BPM");

    tft->setFont(Arial_28);
    tft->setCursor(238, 67, true);
    tft->print(BPM);

    tft->setFont(Arial_13);

    tft->setCursor(43, 136, true);
    //tft->print("1: ");
    tft->print(noteArrayText[seqNoteArray[0]]);
    
    tft->setCursor(121, 136, true);
    //tft->print("2: ");
    tft->print(noteArrayText[seqNoteArray[1]]);

    tft->setCursor(199, 136, true);
    //tft->print("3: ");
    tft->print(noteArrayText[seqNoteArray[2]]);

    tft->setCursor(277, 136, true);
    //tft->print("4: ");
    tft->print(noteArrayText[seqNoteArray[3]]);

    tft->setCursor(43, 188, true);
    //tft->print("5: ");
    tft->print(noteArrayText[seqNoteArray[4]]);

    tft->setCursor(121, 188, true);
    //tft->print("6: ");
    tft->print(noteArrayText[seqNoteArray[5]]);

    tft->setCursor(199, 188, true);
    //tft->print("7: ");
    tft->print(noteArrayText[seqNoteArray[6]]);

    tft->setCursor(277, 188, true);
    //tft->print("8: ");
    tft->print(noteArrayText[seqNoteArray[7]]);
}

void Display::sequencer()
{
    // Button borders
    tft->fillRoundRect(5, 3, 154, 106, 4, textColor);
    tft->fillRoundRect(161, 3, 154, 106, 4, textColor);

    tft->fillRoundRect(5, 111, 76, 50, 4, textColor);
    tft->fillRoundRect(83, 111, 76, 50, 4, textColor);
    tft->fillRoundRect(161, 111, 76, 50, 4, textColor);
    tft->fillRoundRect(239, 111, 76, 50, 4, textColor);
    tft->fillRoundRect(5, 163, 76, 50, 4, textColor);
    tft->fillRoundRect(83, 163, 76, 50, 4, textColor);
    tft->fillRoundRect(161, 163, 76, 50, 4, textColor);
    tft->fillRoundRect(239, 163, 76, 50, 4, textColor);

    // Button fill
    tft->fillRoundRect(7, 5, 150, 102, 4, secondColor);
    tft->fillRoundRect(163, 5, 150, 102, 4, secondColor);
    
    tft->fillRoundRect(7, 113, 72, 46, 4, secondColor);
    tft->fillRoundRect(85, 113, 72, 46, 4, secondColor);
    tft->fillRoundRect(163, 113, 72, 46, 4, secondColor);
    tft->fillRoundRect(241, 113, 72, 46, 4, secondColor);
    tft->fillRoundRect(7, 165, 72, 46, 4, secondColor);
    tft->fillRoundRect(85, 165, 72, 46, 4, secondColor);
    tft->fillRoundRect(163, 165, 72, 46, 4, secondColor);
    tft->fillRoundRect(241, 165, 72, 46, 4, secondColor);

    // Up Arrows
    tft->fillRoundRect(163, 5, 150, 17, 3, thirdColor);
    
    tft->fillRoundRect(7, 113, 72, 12, 3, thirdColor);
    tft->fillRoundRect(85, 113, 72, 12, 3, thirdColor);
    tft->fillRoundRect(163, 113, 72, 12, 3, thirdColor);
    tft->fillRoundRect(241, 113, 72, 12, 3, thirdColor);
    tft->fillRoundRect(7, 165, 72, 12, 3, thirdColor);
    tft->fillRoundRect(85, 165, 72, 12, 3, thirdColor);
    tft->fillRoundRect(163, 165, 72, 12, 3, thirdColor);
    tft->fillRoundRect(241, 165, 72, 12, 3, thirdColor);

    tft->fillTriangle(238, 8, 232, 19, 244, 19, ILI9341_BLACK);
    
    tft->fillTriangle(43, 115, 39, 123, 47, 123, ILI9341_BLACK);
    tft->fillTriangle(121, 115, 117, 123, 125, 123, ILI9341_BLACK);
    tft->fillTriangle(199, 115, 195, 123, 203, 123, ILI9341_BLACK);
    tft->fillTriangle(277, 115, 273, 123, 281, 123, ILI9341_BLACK);
    tft->fillTriangle(43, 167, 39, 175, 47, 175, ILI9341_BLACK);
    tft->fillTriangle(121, 167, 117, 175, 125, 175, ILI9341_BLACK);
    tft->fillTriangle(199, 167, 195, 175, 203, 175, ILI9341_BLACK);
    tft->fillTriangle(277, 167, 273, 175, 281, 175, ILI9341_BLACK);

    // Down Arrows
    tft->fillRoundRect(163, 90, 150, 17, 3, thirdColor);

    tft->fillRoundRect(7, 147, 72, 12, 3, thirdColor);
    tft->fillRoundRect(85, 147, 72, 12, 3, thirdColor);
    tft->fillRoundRect(163, 147, 72, 12, 3, thirdColor);
    tft->fillRoundRect(241, 147, 72, 12, 3, thirdColor);
    tft->fillRoundRect(7, 199, 72, 12, 3, thirdColor);
    tft->fillRoundRect(85, 199, 72, 12, 3, thirdColor);
    tft->fillRoundRect(163, 199, 72, 12, 3, thirdColor);
    tft->fillRoundRect(241, 199, 72, 12, 3, thirdColor);

    tft->fillTriangle(238, 104, 232, 93, 244, 93, ILI9341_BLACK);

    tft->fillTriangle(43, 157, 39, 149, 47, 149, ILI9341_BLACK);
    tft->fillTriangle(121, 157, 117, 149, 125, 149, ILI9341_BLACK);
    tft->fillTriangle(199, 157, 195, 149, 203, 149, ILI9341_BLACK);
    tft->fillTriangle(277, 157, 273, 149, 281, 149, ILI9341_BLACK);
    tft->fillTriangle(43, 209, 39, 201, 47, 201, ILI9341_BLACK);
    tft->fillTriangle(121, 209, 117, 201, 125, 201, ILI9341_BLACK);
    tft->fillTriangle(199, 209, 195, 201, 203, 201, ILI9341_BLACK);
    tft->fillTriangle(277, 209, 273, 201, 281, 201, ILI9341_BLACK);

    seqText();
    bottomMenu5();
}

void Display::seqGateAdjust()
{
    tft->setTextColor(textColor);
    tft->setFont(Arial_28);
    tft->setCursor(162, 30, true);
    tft->print("Gate Length");

    tft->drawFastHLine(12, 90, 26, textColor);
    tft->drawFastVLine(37, 60, 30, textColor);
    tft->drawFastHLine(37, 60, (62 + ((seqGate - 0.1) / 0.004) - 37), textColor);
    tft->drawFastVLine((62 + ((seqGate - 0.1) / 0.004)), 60, 30, textColor);
    tft->drawFastHLine((62 + ((seqGate - 0.1) / 0.004)), 90, (226 - ((seqGate - 0.1) / 0.004)), textColor);
    tft->drawFastVLine(286, 60, 30, textColor);
    tft->drawFastHLine(286, 60, 25, textColor);
    
    tft->fillRoundRect(10, 108, 304, 52, 4, textColor);
    tft->fillRoundRect(12, 110, 300, 48, 4, secondColor);
    tft->drawFastHLine(12, 134, 300, ILI9341_BLACK);

    tft->fillRoundRect(12 + ((seqGate - 0.1) / 0.004), 110, 100, 48, 4, thirdColor);
    tft->drawRoundRect(12 + ((seqGate - 0.1) / 0.004), 110, 100, 48, 4, backgroundColor);
    tft->drawFastVLine(55 + ((seqGate - 0.1) / 0.004), 123, 22, backgroundColor);
    tft->drawFastVLine(62 + ((seqGate - 0.1) / 0.004), 120, 28, backgroundColor);
    tft->drawFastVLine(69 + ((seqGate - 0.1) / 0.004), 123, 22, backgroundColor);

    tft->setFont(Arial_14);
    tft->fillRoundRect(46, 169, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 171, 228, 27, 4, secondColor);
    tft->setCursor(162, 185, true);
    tft->print("Reset");
    
    tft->fillRoundRect(46, 202, 232, 31, 4, textColor);
    tft->fillRoundRect(48, 204, 228, 27, 4, secondColor);
    tft->setCursor(162, 217, true);
    tft->print("Back");
}

void Display::update(Wave wave, Memory sdcard)
{
    tft->fillScreen(backgroundColor);

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
        settings();
    }
    else if (menu == 4)
    {
        saveWave(wave, sdcard);
    }
    else if (menu == 5)
    {
        sequencer();
    }
    else if (menu == 6)
    {
        tuneInput();
    }
    else if (menu == 7)
    {
        triggerSens();
    }
    else if (menu == 8)
    {
        credits();
    }
    else if (menu == 9)
    {
        seqGateAdjust();
    }
    tft->updateScreen();
}

void Display::changeScreen(Wave wave, Memory sdcard)
{
    tft->fillScreen(backgroundColor);

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
        settings();
    }
    else if (menu == 4)
    {
        saveWave(wave, sdcard);
    }
    else if (menu == 5)
    {
        sequencer();
    }
    else if (menu == 6)
    {
        tuneInput();
    }
    else if (menu == 7)
    {
        triggerSens();
    }
    else if (menu == 8)
    {
        credits();
    }
    else if (menu == 9)
    {
        seqGateAdjust();
    }
    tft->updateScreen();
    delay(500);
}

void Display::setConfirm()
{
    tft->fillRoundRect(104, 64, 116, 88, 6, textColor);
    tft->fillRoundRect(106, 66, 112, 84, 6, backgroundColor);
    
    tft->setFont(Arial_16);
    tft->setTextColor(textColor);
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
    tft->fillRoundRect(104, 64, 116, 88, 6, textColor);
    tft->fillRoundRect(106, 66, 112, 84, 6, backgroundColor);
    
    tft->setFont(Arial_16);
    tft->setTextColor(textColor);
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
    tft->fillRoundRect(104, 64, 116, 88, 6, textColor);
    tft->fillRoundRect(106, 66, 112, 84, 6, backgroundColor);
    
    tft->setFont(Arial_16);
    tft->setTextColor(textColor);
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
    tft->fillRoundRect(104, 64, 116, 88, 6, textColor);
    tft->fillRoundRect(106, 66, 112, 84, 6, backgroundColor);
    
    tft->setFont(Arial_16);
    tft->setTextColor(textColor);
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
    tft->fillScreen(backgroundColor);

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
        settings();
    
    }
    else if (menu == 4)
    {
        saveWave(wave, sdcard);
        saveConfirm();
    }
    else if (menu == 5)
    {
        sequencer();
        if (seqOn)
        {
            onConfirm();
        }
        else if (!seqOn)
        {
            offConfirm();
        }
    }
    else if (menu == 6)
    {
        tuneInput();
    }
    else if (menu == 7)
    {
        triggerSens();
    }
    else if (menu == 8)
    {
        credits();
    }
    else if (menu == 9)
    {
        seqGateAdjust();
    }
    tft->updateScreen();
    delay(1000);
}