#include <windows.h>
#include "son.h"

void jouerSonVictoire()
{
    Beep(750, 300);
    Beep(1000, 300);
}

void jouerSonDefaite()
{
    Beep(250, 300);
    Beep(100, 300);
}
