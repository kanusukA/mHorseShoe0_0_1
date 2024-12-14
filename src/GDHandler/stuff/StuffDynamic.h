#pragma once
#include "Stuff.h"

class StuffDynamic :public Stuff
{

public:

    PxRigidDynamic* sActor;

    void setPxRigidDynamic(PxRigidDynamic* dynActor) override;

    bool update(float deltaTime) override;

    void getColliderData();

};

