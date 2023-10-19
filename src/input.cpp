#include <input.h>

int KnobIn::knobRange(int position, int min, int max)
{
    if (position < min)
    {
        position = min;
    }
    else if (position > max)
    {
        position = max;
    }
    return position;
}

void KnobIn::rotate(Display *display, Encoder knob)
{
    newPosition = knob.read() / 4;
    int diff = abs(newPosition - oldPosition);

    if ((newPosition - oldPosition) < 0)
    {
        diff = -1 * diff;
    }
    if (diff != 0)
    {
        display->menu = knobRange(display->menu + diff, 0, 3);
        oldPosition = newPosition;
    }
}

void KnobIn::modeChange(Display *display)
{
    if (display->menu == 6)
    {
        display->menu = 1;
    }
    else
    {
        display->menu++;
    }
    delayMicroseconds(20);
}
