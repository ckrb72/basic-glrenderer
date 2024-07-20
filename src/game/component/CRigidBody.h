#pragma once

class CRigidBody
{
public:

    //Object's mass (0.0 for static object with collisions)
    float mass = 0.0;

    CRigidBody();

    ~CRigidBody() {}
};