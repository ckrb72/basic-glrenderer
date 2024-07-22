/*
        This class simply holds the various input devices that might be used by the game / engine.
        Going to make this very simple for our purposes but will add comments that give ideas about how
        we could make it more generic and allow for any number of input devices in the future.
*/
#pragma once

class InputManager
{
private:
    //Updates all the devices currently registered with the InputManager
    //Purposefully making this private because I don't want scenes to be able to call this themselves.
    //They should only be able to interact with the keyboard and mouse global variables.
    //Game object will be friend to this class so it can update the manager
    void update();


public:
    InputManager();

    ~InputManager();

    // Here you would register a device (keyboard, mouse, controller, etc.) with the InputManager
    // which will then make sure to update the inputs bitmasks (or whatever I end up using) every frame.
    // Don't really know how I would store the different devices yet so they are easily accessible and not confused for each other
    // But would ideally then be able to query different inputs for different purposes (i.e. different players).
    //void register_device(std::shared_ptr<InputDevice> device);
};