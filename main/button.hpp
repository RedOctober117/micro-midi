#ifndef BUTTON_H
#define BUTTON_H

struct Button
{
  char previous_velocity = 0;
  char channel;
  char pitch;
};

void toggle_button(Button &btn);

#endif