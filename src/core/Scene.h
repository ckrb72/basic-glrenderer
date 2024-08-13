/*
        Scene class declaration. In the context of our engine, a scene is an object that holds all the renderables and logic for a certain level or area in a game.
        For example, a scene in mario would be the first level. Scenes do not have to follow a level format and in theory an entire game should be able to be made
        in a single scene. However, a good use case for them is to partition the game into different areas (scenes) and then have a loading screen or quickly load between
        them when you need to. An example of this would be the open world in fallout being a single scene (in reality this probably isn't how this works but just bear with me)
        and then if you enter a house with a loading screen, that would be a different scene.
        This is pretty straight forward in terms of game design but I'm kind of winging this so the implementation might be a bit silly for a while.
*/

#pragma once

class Scene
{

public:

    //NOTE: Use of virtual functions below
    // We want this class to be abstract so every function will be virtual.
    // Also note that there is no constructor
    // Virtual functions are c++'s way of acheivieving runtime ploymorphism.
    // They are essentially function pointers (sort of) with some syntactic sugar
    // and are used in the oop context of c++. 
    // These could essentially be implemented yourself by using an array of function pointers
    // (which I am now realizing is what I sort of did in my c renderer), but we will use the actual
    // Language feature obviously.
    // Just remember, whenever you see a virtual function, it allows you to override it in derived classes.
    // Same idea as virtual memory if you know what that is.

    // This will be changeable on per scene basis
    // Runs at startup (sort of like constructor)
    virtual void start() = 0;

    // This will be changable on per scene basis
    // Runs each frame
    virtual void update(float delta) = 0;

    // This will be changable on per scene basis
    // Runs each frame
    virtual void render() = 0;

    // This will be changeable on per scene basis
    // Runs each frame
    //virtual void handle_events() = 0;


    // This probably shouldn't be changeable per scene but will do that anyway.
    // Runs each froms
    //virtual void handle_physics() = 0;
};