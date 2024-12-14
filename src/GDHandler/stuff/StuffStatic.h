#pragma once
#include "Stuff.h"

class StuffStatic :
    public Stuff
{
public:

    PxRigidStatic* sActor;

    void setPxRigidStatic(PxRigidStatic* staActor) override;

};

