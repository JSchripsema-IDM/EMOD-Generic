/***************************************************************************************************

Copyright (c) 2018 Intellectual Ventures Property Holdings, LLC (IVPH) All rights reserved.

EMOD is licensed under the Creative Commons Attribution-Noncommercial-ShareAlike 4.0 License.
To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode

***************************************************************************************************/

#include "stdafx.h"

#include "Sugar.h"
#include "MalariaContexts.h"
#include "MalariaInterventionsContainer.h"
#include "IIndividualHumanContext.h"

SETUP_LOGGING( "MalariaInterventionsContainer" )

namespace Kernel
{
    MalariaInterventionsContainer::MalariaInterventionsContainer()
        : VectorInterventionsContainer()
        , m_DrugEffectsCollection()
    {
    }

    MalariaInterventionsContainer::~MalariaInterventionsContainer()
    {
    }

    IMalariaDrugEffectsApply* MalariaInterventionsContainer::GetMalariaDrugApply()
    {
        return static_cast<IMalariaDrugEffectsApply*>(this);
    }

    IMalariaDrugEffects* MalariaInterventionsContainer::GetMalariaDrugStats()
    {
        return static_cast<IMalariaDrugEffects*>(this);
    }

    void MalariaInterventionsContainer::InfectiousLoopUpdate(float dt)
    {
        m_DrugEffectsCollection.clear();

        VectorInterventionsContainer::InfectiousLoopUpdate(dt);
    }

    void MalariaInterventionsContainer::AddDrugEffects( IMalariaDrugEffects* pDrugEffects )
    {
        m_DrugEffectsCollection.push_back( pDrugEffects );
    }

    void MalariaInterventionsContainer::RemoveDrugEffects( IMalariaDrugEffects* pDrugEffects )
    {
        for( int i = 0; i < m_DrugEffectsCollection.size(); ++i )
        {
            if( pDrugEffects == m_DrugEffectsCollection[ i ] )
            {
                m_DrugEffectsCollection[ i ] = m_DrugEffectsCollection.back();
                m_DrugEffectsCollection.pop_back();
            }
        }
    }

    int32_t MalariaInterventionsContainer::AddRef() { return InterventionsContainer::AddRef(); }
    int32_t MalariaInterventionsContainer::Release() { return InterventionsContainer::Release(); }

    float MalariaInterventionsContainer::get_drug_IRBC_killrate( const IStrainIdentity& rStrain )
    {
        float rate = 0.0 ;
        for( IMalariaDrugEffects* p_effects : m_DrugEffectsCollection )
        {
            rate += p_effects->get_drug_IRBC_killrate( rStrain );
        }
        return rate;
    }

    float MalariaInterventionsContainer::get_drug_hepatocyte( const IStrainIdentity& rStrain )
    {
        float rate = 0.0;
        for( IMalariaDrugEffects* p_effects : m_DrugEffectsCollection )
        {
            rate += p_effects->get_drug_hepatocyte( rStrain );
        }
        return rate;

    }

    float MalariaInterventionsContainer::get_drug_gametocyte02( const IStrainIdentity& rStrain )
    {
        float rate = 0.0;
        for( IMalariaDrugEffects* p_effects : m_DrugEffectsCollection )
        {
            rate += p_effects->get_drug_gametocyte02( rStrain );
        }
        return rate;
    }

    float MalariaInterventionsContainer::get_drug_gametocyte34( const IStrainIdentity& rStrain )
    {
        float rate = 0.0;
        for( IMalariaDrugEffects* p_effects : m_DrugEffectsCollection )
        {
            rate += p_effects->get_drug_gametocyte34( rStrain );
        }
        return rate;
    }

    float MalariaInterventionsContainer::get_drug_gametocyteM( const IStrainIdentity& rStrain )
    {
        float rate = 0.0;
        for( IMalariaDrugEffects* p_effects : m_DrugEffectsCollection )
        {
            rate += p_effects->get_drug_gametocyteM( rStrain );
        }
        return rate;
    }

    REGISTER_SERIALIZABLE(MalariaInterventionsContainer);

    void MalariaInterventionsContainer::serialize(IArchive& ar, MalariaInterventionsContainer* obj)
    {
        MalariaInterventionsContainer& container = *obj;
        VectorInterventionsContainer::serialize(ar, obj);

        if( ar.IsReader() )
        {
            for( auto iv : container.interventions )
            {
                IMalariaDrugEffects* p_mde = iv->GetMalariaDrug();
                if( p_mde )
                {
                    container.AddDrugEffects( p_mde );
                }
            }
        }
    }


}
