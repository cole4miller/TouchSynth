#include "memory.h"

void Memory::saveFile(int file, Wave wave)
{
    if (file == 0)
    {
        return;
    }
    else if (file == 1)
    {
        char filename[] = "waveOne.txt";
        saveContent(wave, filename);
    }
    else if (file == 2)
    {
        char filename[] = "waveTwo.txt";
        saveContent(wave, filename);
    }
    else if (file == 3)
    {
        char filename[] = "waveThree.txt";
        saveContent(wave, filename);
    }
    else if (file == 4)
    {
        char filename[] = "waveFour.txt";
        saveContent(wave, filename);
    }
    else if (file == 5)
    {
        char filename[] = "waveFive.txt";
        saveContent(wave, filename);
    }
    else if (file == 6)
    {
        char filename[] = "waveSix.txt";
        saveContent(wave, filename);
    }
    else if (file == 7)
    {
        char filename[] = "waveSeven.txt";
        saveContent(wave, filename);
    }
    else if (file == 8)
    {
        char filename[] = "waveEight.txt";
        saveContent(wave, filename);
    }
}

Wave Memory::loadFile(int file, Wave wave)
{
    if (file == 0)
    {
        wave.previewWaveXstart = 302;
        wave.previewWaveXend = 0;
        for (int i = 0; i < 303; i++)
        {
            wave.previewWaveY[i] = 0;
            wave.previewPointUsed[i] = false;
        }
    }
    else if (file == 1)
    {
        char filename[] = "waveOne.txt";
        wave = loadContent(wave, filename);
    }
    else if (file == 2)
    {
        char filename[] = "waveTwo.txt";
        wave = loadContent(wave, filename);
    }
    else if (file == 3)
    {
        char filename[] = "waveThree.txt";
        wave = loadContent(wave, filename);
    }
    else if (file == 4)
    {
        char filename[] = "waveFour.txt";
        wave = loadContent(wave, filename);
    }
    else if (file == 5)
    {
        char filename[] = "waveFive.txt";
        wave = loadContent(wave, filename);
    }
    else if (file == 6)
    {
        char filename[] = "waveSix.txt";
        wave = loadContent(wave, filename);
    }
    else if (file == 7)
    {
        char filename[] = "waveSeven.txt";
        wave = loadContent(wave, filename);
    }
    else if (file == 8)
    {
        char filename[] = "waveEight.txt";
        wave = loadContent(wave, filename);
    }
    return wave;
}

void Memory::saveContent(Wave wave, char filename[])
{
    if (SD.exists(filename))
    {
        SD.remove(filename);
    }

    myFile = SD.open(filename, FILE_WRITE);
    if (myFile) {
        myFile.print(wave.customWaveXstart);
        myFile.println(",");
        myFile.print(wave.customWaveXend);
        myFile.println(",");
        for (int i = 0; i < 303; i++)
        {
            myFile.print(wave.customPointUsed[i]);
            myFile.println(",");
        }
        for (int i = 0; i < 303; i++)
        {
            myFile.print(wave.customWaveY[i]);
            myFile.println(",");
        }
    }
    myFile.close();
}

Wave Memory::loadContent(Wave wave, char filename[])
{
    int line = 0;

    myFile = SD.open(filename);
    
    if (myFile) {
        while (myFile.available()) {
            switch ((char)myFile.peek()) {
                case ',': 
                myFile.read();
                break;
                case '\r':
                myFile.read();
                break;
                
                default:
                if (line == 0)
                {
                    wave.previewWaveXstart = myFile.parseInt();
                    line++;
                }
                else if (line == 1)
                {
                    wave.previewWaveXend = myFile.parseInt();
                    line++;
                }
                else if (line > 1 && line <=304)
                {
                    wave.previewPointUsed[line - 2] = myFile.parseInt();
                    line++;
                }
                else if (line >= 305 && line <= 607)
                {
                    wave.previewWaveY[line - 305] = myFile.parseInt();
                    line++;
                }
                else if (line >607)
                {
                    myFile.close();
                    return wave;
                }      
                break;
            }
        }
        myFile.close();
    }
    return wave;
}