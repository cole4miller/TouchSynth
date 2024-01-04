#pragma once
#include <Arduino.h>
#include <cmath>
#include "SPI.h"
#include "wave.h"
#include "ILI9341_t3n.h"
#include "ILI9341_t3n_font_Arial.h"
#include "display.h"
#include "notes.h"


#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 6
#define TFT_SCK 13
#define TFT_MISO 12
#define TFT_MOSI 11
#define TOUCH_CS 8

class Wave;
class Memory;

class Display
{
public:
    Display(int16_t *, int16_t *, ILI9341_t3n *);
    void update(Wave wave, Memory sdcard);
    void changeScreen(Wave wave, Memory sdcard);
    void updateSet(Wave wave, Memory sdcard);

    uint16_t menu = 0;              // 0 = Main menu, 1 = Draw Wave
                                    // 2 = Select Wave, 3 = Envelope
                                    // 4 - Save
    uint16_t xin = 0;               // Values 0 - 319
    uint16_t yin = 0;               // Values 0 - 239
    uint16_t attack = 75;           // Values 0 - 150
    uint16_t decay = 75;            // Values 0 - 150
    uint16_t sustain = 75;          // Values 0 - 150
    uint16_t release = 75;          // Values 0 - 150
    bool drawWaveOn = false;        // Activates custom wave form
    bool waveOptions = false;
    bool smoothOn = false;          // Custom wvae for smoothing effect
    uint16_t smoothLevel = 0;
    bool selectWaveOn = false;      // Activates preset wave form
    bool envelopeOn = false;        // Activates digital envelope
    uint16_t selectWaveType = 0;    // 0 = square, 1 = sine
                                    // 2 = triangle, 3 = sawtooth
    bool seqOn = false;
    int seqNoteArray[8] = {45, 45, 45, 45, 45, 45, 45, 45}; // element values 0 - 84
    int seqStep = 0;

    uint16_t saveFile = 0;
    bool saveLoad;                  // 0 = save, 1 = load
    int BPM = 80;

    double noteArray[85] = {
    C1, Db1, D1, Eb1, E1, F1, Gb1, G1, Ab1, A1, Bb1, B1note, 
    C2, Db2, D2, Eb2, E2, F2, Gb2, G2, Ab2, A2, Bb2, B2, 
    C3, Db3, D3, Eb3, E3, F3, Gb3, G3, Ab3, A3, Bb3, B3,
    C4, Db4, D4, Eb4, E4, F4, Gb4, G4, Ab4, A4, Bb4, B4, 
    C5, Db5, D5, Eb5, E5, F5, Gb5, G5, Ab5, A5, Bb5, B5, 
    C6, Db6, D6, Eb6, E6, F6, Gb6, G6, Ab6, A6, Bb6, B6, 
    C7, Db7, D7, Eb7, E7, F7, Gb7, G7, Ab7, A7, Bb7, B7, C8};

    const char* noteArrayText[85] = {
    "C1", "Db1", "D1", "Eb1", "E1", "F1", "Gb1", "G1", "Ab1", "A1", "Bb1", "B1", 
    "C2", "Db2", "D2", "Eb2", "E2", "F2", "Gb2", "G2", "Ab2", "A2", "Bb2", "B2", 
    "C3", "Db3", "D3", "Eb3", "E3", "F3", "Gb3", "G3", "Ab3", "A3", "Bb3", "B3", 
    "C4", "Db4", "D4", "Eb4", "E4", "F4", "Gb4", "G4", "Ab4", "A4", "Bb4", "B4", 
    "C5", "Db5", "D5", "Eb5", "E5", "F5", "Gb5", "G5", "Ab5", "A5", "Bb5", "B5", 
    "C6", "Db6", "D6", "Eb6", "E6", "F6", "Gb6", "G6", "Ab6", "A6", "Bb6", "B6", 
    "C7", "Db7", "D7", "Eb7", "E7", "F7", "Gb7", "G7", "Ab7", "A7", "Bb7", "B7", "C8"};

private:
    void drawGrid();
    void miniWave(Wave wave);
    void mainMenu(Wave wave);
    void saveText();
    void drawSave(Wave wave, Memory sdcard);
    void saveWave(Wave wave, Memory sdcard);
    void bottomMenu1();
    void bottomMenu2();
    void bottomMenu3();
    void bottomMenu4();
    void bottomMenu5();
    void drawWave(Wave wave);
    void waveIcons();
    void selectWave(Wave wave);
    void ADSRfaders();
    void envelope();
    void stepDisplay();
    void seqText();
    void sequencer();
    void setConfirm();
    void onConfirm();
    void offConfirm();
    void saveConfirm();

    int16_t *data[2];

    const float SAMPLE_RATE = 1176470.58824;

    ILI9341_t3n *tft;
};