#include <Arduino.h>
#include <Encoder.h>
#include <SPI.h>
#include <SD.h>
#include "wave.h"
#include "display.h"
#include "sampler.h"
#include "input.h"
#include "touch.h"
#include "memory.h"
#include "oscillator.h"
#include "notes.h"

#include "XPT2046_Touchscreen.h"

const int channel_1_pin = A4;
const int channel_2_pin = A5;

const int knob_in_1 = 34;
const int knob_in_2 = 35;
const int knob_push = 33;

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

Oscillator oscillator;
int levelOut;
long numPoints;

IntervalTimer updateOut;
IntervalTimer seqNoteChange;

Encoder knob(knob_in_1, knob_in_2);
KnobIn knob_in;

int buttonState = 0;
int lastButtonState = 0;

int currentButtonState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void changePWM()
{
    levelOut = oscillator.updateLevel(wave, display);
    numPoints = oscillator.updateRate(wave, display);
    //long newPeriod = (1.0 / (oscillator.freq * numPoints));
    analogWrite(22, levelOut);
    updateOut.update((1.0 / (oscillator.freq * numPoints)) * 1000000.0);
    //Serial.print("newPeriod:  ");
    //Serial.println(newPeriod);
    //Serial.print("levelOut:  ");
    //Serial.println(levelOut);
    //Serial.print("numPoints:  ");
    //Serial.println(numPoints);
}

void changeSeqNote()
{
    if (display->seqOn)
    {
        oscillator.freq = display->noteArray[display->seqNoteArray[display->seqStep]];
    }
    seqNoteChange.update((60.0 / (display->BPM * 4)) * 1000000.0);
    display->seqStep++;
    if (display->seqStep >= 8)
    {
        display->seqStep = 0;
    }
}

void rotate()
{
    knob_in.rotate(display, knob);
}

void modeChange()
{
    knob_in.modeChange(display);
}

int16_t testarray[BUFFER_SIZE];
int16_t testarray2[BUFFER_SIZE];   

void setup()
{
    while (!Serial && millis() < 5000)
        ; // Wait 5 seconds for serial connection
   
    display = new Display(channel_1_data, channel_2_data, &tft);
    ts.begin();
    ts.setRotation(3);

    wave.resetWave();

    SD.begin(BUILTIN_SDCARD);

    updateOut.priority(0);
    updateOut.begin(changePWM, 1000000);

    seqNoteChange.priority(1);
    seqNoteChange.begin(changeSeqNote, ((60.0 / display->BPM) * 1000000.0));

    analogWriteFrequency(22, 585937.5);
    analogWriteResolution(8);

    //setupADC(channel_1_pin, channel_2_pin);

    //pinMode(knob_in_1, INPUT_PULLUP);
    //pinMode(knob_in_2, INPUT_PULLUP);
    //pinMode(knob_push, INPUT_PULLUP);

    //attachInterrupt(digitalPinToInterrupt(knob_in_2), rotate, CHANGE);

    //knob_in.oldPosition = knob.read();
    //knob_in.newPosition = knob_in.oldPosition;
}

void loop()
{
    /*
    if (DMA_completed())
    {
        processBuffers(channel_1_data, channel_2_data);

        // temporary: convert from mV to full 16 bit range (6V = )
        
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            screen_channel_1_data[i] = channel_1_data[i] * 5.46133333333 + 32767.0;
            screen_channel_2_data[i] = channel_2_data[i] * 5.46133333333 + 32767.0;
        }
        

        display->update(wave);
    }
    */
    display->update(wave, sdcard);
    if (ts.touched()) {
        TS_Point p = ts.getPoint();
        display->xin = (p.x - 200.0) * (320.0 / 3500.0);
        display->yin = (p.y - 300.0) * (240.0 / 3550.0);
        touch.xin = (p.x - 200.0) * (320.0 / 3550.0);
        touch.yin = (p.y - 300.0) * (240.0 / 3550.0);
        wave = touch.processTouch(display, wave, sdcard);
        for(int i = 0; i < 8; i++)
        {
            oscillator.seqNotes[i] = display->seqNoteArray[i];
        }
    }

    /*
    currentButtonState = digitalRead(knob_push);

    if (currentButtonState != lastButtonState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        if (currentButtonState != buttonState)
        {
            buttonState = currentButtonState;
            if (buttonState == LOW)
            {
                modeChange();
            }
        }
    }
    lastButtonState = currentButtonState;
    */
}

