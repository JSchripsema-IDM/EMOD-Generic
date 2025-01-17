/***************************************************************************************************

Copyright (c) 2018 Intellectual Ventures Property Holdings, LLC (IVPH) All rights reserved.

EMOD is licensed under the Creative Commons Attribution-Noncommercial-ShareAlike 4.0 License.
To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode

***************************************************************************************************/

#pragma once

#include <string>
#include <list>
#include <vector>

#include "HealthSeekingBehavior.h"
#include "IHealthSeekingBehavior.h"

namespace Kernel
{
    class HealthSeekingBehaviorUpdateable :  public SimpleHealthSeekingBehavior, public IHealthSeekingBehavior
    {
        IMPLEMENT_DEFAULT_REFERENCE_COUNTING()
        DECLARE_FACTORY_REGISTERED(IndividualIVFactory, HealthSeekingBehaviorUpdateable, IDistributableIntervention)
    
    public: 
        HealthSeekingBehaviorUpdateable();
        virtual ~HealthSeekingBehaviorUpdateable() {};

        //IHealthSeekingBehavior
        virtual void UpdateProbabilityofSeeking(float new_probability_of_seeking) override;
        virtual IHealthSeekingBehavior* GetHSB() override;

    protected:
        DECLARE_SERIALIZABLE(HealthSeekingBehaviorUpdateable);
    };
}
