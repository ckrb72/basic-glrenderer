#pragma once
#include "../../math/lnal.h"
class CTransform
{
public:
    lnal::vec3 pos = {0.0, 0.0, 0.0};

    //lnal::quaternion rotation = {};


    CTransform();

    ~CTransform() {}
};