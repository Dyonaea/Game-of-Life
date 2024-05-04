#include "event.h"

void edit_event(SDL_Event ev, int *edit, int *key_already_pressed)
{
    if (ev.key.keysym.scancode == SDL_SCANCODE_E)
    {
        if (key_already_pressed == 0)
        {
            if (*edit == 1)
            {
                edit = 0;
            }
            else edit = 1;
            key_already_pressed = 1;
        }
    }
}