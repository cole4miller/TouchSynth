#pragma once
#include <Arduino.h>
#include <cmath>
#include "SPI.h"
#include "wave.h"
#include "ILI9341_t3n.h"
#include "ILI9341_t3n_font_Arial.h"
#include "display.h"


#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 6
#define TFT_SCK 13
#define TFT_MISO 12
#define TFT_MOSI 11
#define TOUCH_CS 8

class Wave;

class Display
{
public:
    Display(int16_t *, int16_t *, ILI9341_t3n *);
    void update(Wave wave);

    uint16_t menu = 0;              // 0 = Main menu, 1 = Draw Wave
                                    // 2 = Select Wave, 3 = Envelope
    uint16_t xin = 0;               // Values 0 - 319
    uint16_t yin = 0;               // Values 0 - 239
    uint16_t attack = 75;           // Values 0 - 150
    uint16_t decay = 75;            // Values 0 - 150
    uint16_t sustain = 75;          // Values 0 - 150
    uint16_t release = 75;          // Values 0 - 150
    bool drawWaveOn = false;        // Activates custom wave form
    bool selectWaveOn = false;      // Activates preset wave form
    bool envelopeOn = false;        // Activates digital envelope
    uint16_t selectWaveType = 0;    // 0 = square, 1 = sine
                                    // 2 = triangle, 3 = sawtooth

private:
    void drawGrid();
    void mainMenu();
    void bottomMenu1();
    void bottomMenu2();
    void bottomMenu3();
    void drawWave(Wave wave);
    void waveIcons();
    void selectWave(Wave wave);
    void ADSRfaders();
    void envelope();

    int16_t *data[2];

    const float SAMPLE_RATE = 1176470.58824;

    ILI9341_t3n *tft;
};