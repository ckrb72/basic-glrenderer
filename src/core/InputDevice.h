/*
    Defines InputDevice class used for setting up a supported device. Current Implementation will use SDL2 but ideally this can be swapped out whenever with a different framework.
    Support right now will just be for keyboards and mice but will eventually add controller support if it is called for.
*/

#pragma once

class InputDevice
{
private:


public:
    InputDevice();

    ~InputDevice();
};