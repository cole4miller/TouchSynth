#include <touch.h>

void Touch::mainMenu(Display * display)
{
    if (xin > 40 && xin < 280 && yin > 60 && yin < 110)
    {
        display->menu = 1;
    }
    else if (xin > 40 && xin < 280 && yin > 120 && yin < 170)
    {
        display->menu = 2;
    }
    else if (xin > 40 && xin < 280 && yin > 180 && yin < 230)
    {
        display->menu = 3;
    }
}

void Touch::bottomMenu1(Display * display)
{
    if (xin >= 32 && xin <= 116 && yin > 217 && yin < 237)
    {
        display->menu = 0;
    }
    else if (xin >= 120 && xin <= 204 && yin > 217 && yin < 237)
    {
        
    }
    else if (xin >= 208 && xin <= 292 && yin > 217 && yin < 237)
    {
        
    }
}

void Touch::bottomMenu2(Display * display)
{
    if (xin >= 32 && xin <= 116 && yin > 217 && yin < 237)
    {
        display->menu = 0;
    }
    else if (xin >= 120 && xin <= 204 && yin > 217 && yin < 237)
    {
        
    }
    else if (xin >= 208 && xin <= 292 && yin > 217 && yin < 237)
    {
        
    }
}

void Touch::bottomMenu3(Display * display)
{
    if (xin >= 32 && xin <= 116 && yin > 217 && yin < 237)
    {
        display->menu = 0;
    }
    else if (xin >= 120 && xin <= 204 && yin > 217 && yin < 237)
    {
        
    }
    else if (xin >= 208 && xin <= 292 && yin > 217 && yin < 237)
    {
        
    }
}

void Touch::drawWave(Display * display)
{
    
}

void Touch::selectWave(Display * display)
{
    
}

void Touch::adjustAttack(Display * display)
{
    if (yin > 4 && yin <= 32)
    {
        display->attack = 150;
    }
    else if (yin > 32 && yin < 184)
    {
        display->attack = 184 - yin;
    }
    if (yin >= 184 && yin < 212)
    {
        display->attack = 0;
    }
}

void Touch::adjustDecay(Display * display)
{
    if (yin > 4 && yin <= 32)
    {
        display->decay = 150;
    }
    else if (yin > 32 && yin < 184)
    {
        display->decay = 184 - yin;
    }
    if (yin >= 184 && yin < 212)
    {
        display->decay = 0;
    }
}

void Touch::adjustSustain(Display * display)
{
    if (yin > 4 && yin <= 32)
    {
        display->sustain = 150;
    }
    else if (yin > 32 && yin < 184)
    {
        display->sustain = 184 - yin;
    }
    if (yin >= 184 && yin < 212)
    {
        display->sustain = 0;
    }
}

void Touch::adjustRelease(Display * display)
{
    if (yin > 4 && yin <= 32)
    {
        display->release = 150;
    }
    else if (yin > 32 && yin < 184)
    {
        display->release = 184 - yin;
    }
    if (yin >= 184 && yin < 212)
    {
        display->release = 0;
    }
}

void Touch::envelope(Display * display)
{
    if (xin > 10 && xin < 85 && yin > 4 && yin < 212)
    {
        adjustAttack(display);
    }
    else if (xin > 86 && xin < 161 && yin > 4 && yin < 212)
    {
        adjustDecay(display);
    }
    else if (xin > 162 && xin < 237 && yin > 4 && yin < 212)
    {
        adjustSustain(display);
    }
    else if (xin > 238 && xin < 313 && yin > 4 && yin < 212)
    {
        adjustRelease(display);
    }
}

void Touch::processTouch(Display * display)
{
    if (display->menu == 0)
    {
        mainMenu(display);
    }
    else if (display->menu == 1)
    {
        drawWave(display);
    }
    else if (display->menu == 2)
    {
        selectWave(display);
    }
    else if (display->menu == 3)
    {
        envelope(display);
    }
}

