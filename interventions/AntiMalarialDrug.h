/***************************************************************************************************

Copyright (c) 2018 Intellectual Ventures Property Holdings, LLC (IVPH) All rights reserved.

EMOD is licensed under the Creative Commons Attribution-Noncommercial-ShareAlike 4.0 License.
To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode

***************************************************************************************************/

#pragma once

#include "Drugs.h"
#include "MalariaInterventionsContainerContexts.h"  // for IMalariaDrugEffects methods
#include "MalariaDrugTypeParameters.h"
#include "InterventionEnums.h"

namespace Kernel
{
    typedef std::map<float,float> bodyweight_map_t;

    class AntimalarialDrug : public GenericDrug, public IMalariaDrugEffects
    {
        DECLARE_FACTORY_REGISTERED(IndividualIVFactory, AntimalarialDrug, IDistributableIntervention)

    public:
        AntimalarialDrug();
        virtual ~AntimalarialDrug();

        virtual bool Configure( const Configuration * ) override;

        // ISupports
        virtual void SetContextTo(IIndividualHumanContext *context) override;
        virtual int32_t AddRef() override { return GenericDrug::AddRef(); }
        virtual int32_t Release() override { return GenericDrug::Release(); }

        // IDistributableIntervention
        virtual bool Distribute(IIndividualHumanInterventionsContext *context, ICampaignCostObserver * const pCCO ) override;

        virtual IMalariaDrugEffects* GetMalariaDrug() override;

        // Other methods
        virtual DrugUsageType::Enum GetDrugUsageType();

        // IMalariaDrugEffects
        float get_drug_IRBC_killrate( const IStrainIdentity& rStrain ) override;
        float get_drug_hepatocyte(    const IStrainIdentity& rStrain ) override;
        float get_drug_gametocyte02(  const IStrainIdentity& rStrain ) override;
        float get_drug_gametocyte34(  const IStrainIdentity& rStrain ) override;
        float get_drug_gametocyteM(   const IStrainIdentity& rStrain ) override;

        static float BodyWeightByAge(float age_in_days);
        static const float _adult_bodyweight_kg;

    protected:
        virtual void  ConfigureDrugTreatment( IIndividualHumanInterventionsContext * ivc ) override;  // read in PkPd and drug-killing parameters from SusceptibilityFlagsMalaria
        virtual void ResetForNextDose(float dt) override;

        virtual void ApplyEffects() override;
        virtual void Expire() override;

        virtual float CalculateModifiedEfficacy( const IStrainIdentity& rStrain );
        virtual int GetNumDoses() const;

        DrugUsageType::Enum dosing_type;
        float drug_IRBC_killrate;
        float drug_hepatocyte;
        float drug_gametocyte02;
        float drug_gametocyte34;
        float drug_gametocyteM;
        MalariaDrugTypeParameters* pMalariaDrugTypeParameters;
        const DrugResistantModifiers* pDrugResistantModifiers;
        IMalariaDrugEffectsApply* imda;

        static bodyweight_map_t create_bodyweight_map();
        static const bodyweight_map_t bodyweight_map_;

        DECLARE_SERIALIZABLE(AntimalarialDrug);
    };
}
