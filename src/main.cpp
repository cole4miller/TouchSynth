#include <Arduino.h>
#include <Encoder.h>
#include <SPI.h>
#include <SD.h>
#include "wave.h"
#include "display.h"
#include "sampler.h"
#include "touch.h"
#include "memory.h"
#include "oscillator.h"
#include "notes.h"

#include "XPT2046_Touchscreen.h"

// DAC output
#define SDI 7
#define SCK 21      
#define CS 20
#define HALFCLKns 30    // clock cycle duration is twice this
#define gateOut 17

const int channel_1_pin = 18;
const int channel_2_pin = 19;
int16_t channel_1_data[BUFFER_SIZE];
int16_t channel_2_data[BUFFER_SIZE];
uint16_t screen_channel_1_data[BUFFER_SIZE];
uint16_t screen_channel_2_data[BUFFER_SIZE];

Wave wave;
ILI9341_t3n tft = ILI9341_t3n(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCK, TFT_MISO);
Display *display;
Touch touch;
#define CS_PIN  8
XPT2046_Touchscreen ts(CS_PIN);

Memory sdcard;

Oscillator *oscillator;
int levelOut;
int bufferIndex = 0;

IntervalTimer updateOut;
IntervalTimer seqNoteChange;
//int16_t updateTime = 10;     // output update interval in microseconds
                            // output buffer can only handle low freqs
                            // at minimum of 1us update time

void DACout()
{
    // *****************
    // update DAC output
    // *****************

    int value = oscillator->bufferOut[bufferIndex];
    byte dacRegister = 0b00110000;
    int dacSecondaryByteMask = 0b0000000011111111;
    byte dacPrimaryByte = (value >> 8) | dacRegister;     
    byte dacSecondaryByte = value & dacSecondaryByteMask; 
    word data = word(dacPrimaryByte, dacSecondaryByte); 
    digitalWriteFast(CS,0);   
    delayNanoseconds(HALFCLKns);        
    for (int i=15; i>=0; i--)
    {
        digitalWriteFast(SDI, bitRead(data, i)); 
        delayNanoseconds(HALFCLKns);
        digitalWriteFast(SCK,1); 
        delayNanoseconds(HALFCLKns);
        digitalWriteFast(SCK,0); 
    } 
    delayNanoseconds(HALFCLKns); 
    digitalWriteFast(CS,1);
    if (bufferIndex < (oscillator->bufferSteps - 1))
    {
        bufferIndex++;
    }
    else if (bufferIndex >= (oscillator->bufferSteps - 1))
    {
        bufferIndex = 0;
    }
}

void changeSeqNote()
{
    if (display->seqOn)
    {
        int period = (60.0 / (display->BPM * 4)) * 1000000.0;
        if (!display->seqGateOn)
        {
            seqNoteChange.update(period * display->seqGate);
            oscillator->freq = display->noteArray[display->seqNoteArray[display->seqStep]];
            oscillator->fillWave(wave, display);
            oscillator->fillBuffer(wave, display);
            digitalWriteFast(gateOut,0);
            display->seqGateOn = true; 
        }
        else
        {
            seqNoteChange.update(period * (1 - display->seqGate));
            digitalWriteFast(gateOut,1);
            display->seqGateOn = false; 
            display->seqStep++;
            if (display->seqStep >= 8)
            {
                display->seqStep = 0;
            }
        }
    }
}  

void setup()
{
    while (!Serial && millis() < 5000)
        ; // Wait 5 seconds for serial connection
   
    display = new Display(channel_1_data, channel_2_data, &tft);
    ts.begin();
    ts.setRotation(3);

    oscillator = new Oscillator();

    pinMode(CS, OUTPUT);
    pinMode(SDI, OUTPUT);
    pinMode(SCK, OUTPUT);
    pinMode(gateOut, OUTPUT);

    wave.resetWave();
    wave.squareWave();

    SD.begin(BUILTIN_SDCARD);

    updateOut.priority(0);
    updateOut.begin(DACout, oscillator->updateTime);

    digitalWriteFast(CS,1);  

    seqNoteChange.priority(1);
    seqNoteChange.begin(changeSeqNote, ((60.0 / display->BPM) * 1000000.0));

    analogWriteFrequency(22, 585937.5);
    analogWriteResolution(8);

    setupADC(channel_1_pin, channel_2_pin);

    display->update(wave, sdcard);
}

void loop()
{ 
    if (DMA_completed())
    {
        if (!display->seqOn)
        {
            processBuffers(channel_1_data, channel_2_data);
            int sample = display->checkTrig();
            if (sample < BUFFER_SIZE)
            {
                oscillator->freq = display->getFreq(sample);
                oscillator->fillWave(wave, display);
                oscillator->fillBuffer(wave, display);
            }
        }
    }
    
    if (ts.touched()) 
    {
        TS_Point p = ts.getPoint();
        touch.xin = (p.x - 200.0) * (320.0 / 3550.0);
        touch.yin = (p.y - 300.0) * (240.0 / 3550.0);
        wave = touch.processTouch(display, wave, sdcard, oscillator);
        if (display->seqOn)
        {
            for(int i = 0; i < 8; i++)
            {
                oscillator->seqNotes[i] = display->seqNoteArray[i];
            }
        }
        
        display->update(wave, sdcard);
    }
}

