/***************************************************************************************************

Copyright (c) 2018 Intellectual Ventures Property Holdings, LLC (IVPH) All rights reserved.

EMOD is licensed under the Creative Commons Attribution-Noncommercial-ShareAlike 4.0 License.
To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode

***************************************************************************************************/

#include "stdafx.h"
#include "HealthSeekingBehaviorUpdateable.h"

SETUP_LOGGING( "HealthSeekingBehaviorUpdateable" )

namespace Kernel
{
    IMPLEMENT_FACTORY_REGISTERED(HealthSeekingBehaviorUpdateable)

    HealthSeekingBehaviorUpdateable::HealthSeekingBehaviorUpdateable() : SimpleHealthSeekingBehavior()
    {
        initSimTypes( 1, "TBHIV_SIM" );
    }

    void HealthSeekingBehaviorUpdateable::UpdateProbabilityofSeeking( float new_probability_of_seeking )
    {
        LOG_DEBUG_F("old probability of seeking is %f, new probability of seeking is %f\n", probability_of_seeking, new_probability_of_seeking);
        probability_of_seeking = new_probability_of_seeking;
    }

    IHealthSeekingBehavior* HealthSeekingBehaviorUpdateable::GetHSB()
    {
        return static_cast<IHealthSeekingBehavior*>(this);
    }

    REGISTER_SERIALIZABLE(HealthSeekingBehaviorUpdateable);

    void HealthSeekingBehaviorUpdateable::serialize(IArchive& ar, HealthSeekingBehaviorUpdateable* obj)
    {
        SimpleHealthSeekingBehavior::serialize(ar, obj);
    }   
}
