/***************************************************************************************************

Copyright (c) 2018 Intellectual Ventures Property Holdings, LLC (IVPH) All rights reserved.

EMOD is licensed under the Creative Commons Attribution-Noncommercial-ShareAlike 4.0 License.
To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode

***************************************************************************************************/

#pragma once

#include "IIndividualHumanContext.h"
#include "IIndividualHumanHIV.h"
#include "RandomFake.h"
#include "IHIVInterventionsContainer.h"
#include "InfectionHIV.h"
#include "IIndividualHumanSTI.h"
#include "IIndividualHuman.h"
#include "IndividualEventContext.h"
#include "Interventions.h"
#include "ISimulationContext.h"
#include "MalariaContexts.h"

using namespace Kernel;

class IndividualHumanContextFake : public IIndividualHumanContext,
                                   public IIndividualHumanHIV,
                                   public IIndividualHumanEventContext,
                                   public IInfectionHIV,
                                   public IIndividualHumanSTI,
                                   public IIndividualHuman,
                                   public IMalariaHumanContext
{
public:
    IndividualHumanContextFake( IIndividualHumanInterventionsContext* pIHIC,
                                INodeContext* pNC,
                                INodeEventContext* pNEC,
                                ISusceptibilityHIV* pISusceptibilityHIV )
        : IIndividualHumanContext() 
        , m_RefCount(0)
        , m_Id()
        , m_pInterventionsContext(pIHIC)
        , m_pNodeContext(pNC)
        , m_pNodeEventContext(pNEC)
        , m_pISusceptibilityHIV( pISusceptibilityHIV )
        , m_Rand()
        , m_pMyRand(nullptr)
        , m_IntendsToBreastfeed(false)
        , m_IsPregnant(false)
        , m_Age(0.0)
        , m_WhoStage(0.0)
        , m_HasSTI(false)
        , m_HasHIV(false)
        , m_HasCoSTI(false)
        , m_Relationships()
        , m_Properties()
        , m_AssortivityIndex(-1)
    {
        m_Id.data = 1 ;
        if( pIHIC != nullptr )
        {
            pIHIC->SetContextTo( this );
        }
    }

    virtual ~IndividualHumanContextFake()
    {
        delete m_pMyRand;
    };

    // ---------------------
    // --- ISupport Methods
    // ---------------------
    virtual int32_t AddRef() override
    {
        m_RefCount++ ;
        return m_RefCount;
    }

    virtual int32_t Release() override
    {
        m_RefCount-- ;
        return m_RefCount;
    }

    // ------------------------------------
    // --- IIndividualHumanContext Methods
    // ------------------------------------
    virtual suids::suid GetSuid() const override
    {
        return m_Id ;
    }

    virtual IIndividualHumanInterventionsContext* GetInterventionsContext() const override
    {
        return m_pInterventionsContext ;
    }

    virtual IIndividualHuman* GetIndividual() override
    {
        return static_cast<IIndividualHuman*>(this);
    }

    virtual IIndividualHumanSTI* GetIndividualSTI() override
    {
        return static_cast<IIndividualHumanSTI*>(this);
    }

    virtual IIndividualHumanHIV* GetIndividualHIV() override
    {
        return static_cast<IIndividualHumanHIV*>(this);
    }

    virtual IMalariaHumanContext* GetIndividualMalaria() override
    {
        return static_cast<IMalariaHumanContext*>(this);
    }

    virtual IIndividualHumanEventContext* GetEventContext() override
    {
        return static_cast<IIndividualHumanEventContext*>(this) ;
    }

    virtual RANDOMBASE* GetRng() override
    { 
        if( m_pMyRand != nullptr )
        {
            return m_pMyRand;
        }
        else
        {
            return &m_Rand;
        }
    }

    virtual const AgentParams* GetParams()                    const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }

    virtual suids::suid   GetNextInfectionSuid()                    override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void          UpdateGroupMembership()                   override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void          UpdateGroupPopulation(float size_changes) override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }

    virtual ISusceptibilityContext* GetSusceptibilityContext() const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual IVaccineConsumer* GetVaccineContext()              const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }

    virtual IIndividualHumanCoInfection* GetIndividualCoInf()        override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual IIndividualHumanTB* GetIndividualTB()                    override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual IIndividualHumanPolio* GetIndividualPolio()              override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual IIndividualHumanTyphoid* GetIndividualTyphoid()          override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual IIndividualHumanVectorContext* GetIndividualVector()     override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }

    virtual const std::string& GetPropertyReportString() const     override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }

    // --------------------------------
    // --- IIndividualHuman Methods
    // --------------------------------
    virtual NewInfectionState::_enum GetNewInfectionState() const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void Update(float current_time, float dt)             override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual IMigrate* GetIMigrate()                               override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__,  "The method or operation is not implemented." ); }

    virtual IIndividualHumanContext* GetIndividualContext() override
    {
        return static_cast<IIndividualHumanContext*>(this);
    }

    virtual INodeContext* GetParent() const override
    {
        return m_pNodeContext ;
    }

    virtual void setupMaternalAntibodies(Kernel::IIndividualHumanContext *,Kernel::INodeContext *) override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual bool ShouldAcquire(float, float, float, TransmissionRoute::Enum)                       override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void AcquireNewInfection(const Kernel::IStrainIdentity*, TransmissionRoute::Enum, float) override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void SetParameters(Kernel::INodeContext*,float,float)                                  override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void InitializeHuman(void)                                                             override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void UpdateInfectiousness(float)                                                       override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void UpdateMCSamplingRate(float)                                                       override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual bool UpdatePregnancy(float)                                                            override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void InitiatePregnancy(float)                                                          override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual ProbabilityNumber getProbMaternalTransmission(void) const                              override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual suids::suid GetParentSuid(void) const                                                  override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual bool IsMigrating(void)                                                                 override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void ClearNewInfectionState(void)                                                      override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual const infection_list_t& GetInfections(void) const                                      override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual const suids::suid& GetMigrationDestination(void)                                       override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void SetContextTo(Kernel::INodeContext *)                                              override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual bool IsSymptomatic() const                                                             override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual bool IsNewlySymptomatic() const                                                        override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }


    virtual void SetGoingOnFamilyTrip( suids::suid migrationDestination, 
                                        MigrationType::Enum migrationType, 
                                        float timeUntilTrip, 
                                        float timeAtDestination,
                                        bool isDestinationNewHome ) override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }

    virtual void SetWaitingToGoOnFamilyTrip() override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void GoHome()                     override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }

    // --------------------------------
    // --- IIndividualHumanHIV Methods
    // --------------------------------
    virtual ISusceptibilityHIV* GetHIVSusceptibility() const override
    {
        return m_pISusceptibilityHIV ;
    }

    virtual bool IntendsToBreastfeed() const
    {
        return m_IntendsToBreastfeed ;
    }

    virtual IInfectionHIV* GetHIVInfection() const override
    {
        return (IInfectionHIV*)this ;
    }

    virtual bool HasHIV() const override
    {
        return m_HasHIV ;
    }

    virtual bool HasSTICoInfection() const override
    {
        return m_HasCoSTI ;
    }

    virtual void SetStiCoInfectionState() override
    { 
        m_HasCoSTI = true ;
        release_assert( !(m_HasSTI && (m_HasCoSTI || m_HasHIV)) );
    }

    virtual void ClearStiCoInfectionState() override
    { 
        m_HasCoSTI = false ;
        release_assert( !(m_HasSTI && (m_HasCoSTI || m_HasHIV)) );
    }

    virtual IHIVInterventionsContainer* GetHIVInterventionsContainer() const override
    {
        return m_pInterventionsContext->GetContainerHIV() ;
    }

    virtual std::string toString() const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }

    // -----------------------------------------
    // --- IIndividualHumanEventContext Methods
    // -----------------------------------------
    virtual bool IsPregnant() const override
    {
        return m_IsPregnant ;
    }

    virtual float GetAge() const override
    {
        return m_Age ;
    }

    virtual bool IsInfected() const override
    {
        return m_HasSTI || m_HasHIV ;
    }

    virtual int GetGender() const override
    {
        return m_Gender ;
    }

    virtual float            GetMonteCarloWeight() const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual bool             IsPossibleMother()    const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual float            GetInfectiousness()   const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual HumanStateChange GetStateChange(void)  const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void             Die( HumanStateChange )     override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void             BroadcastDeath()            override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual bool             AtHome()              const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual bool             IsOnFamilyTrip()      const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual const suids::suid& GetHomeNodeId()     const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual bool IsDead()                          const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }

    virtual IPKeyValueContainer* GetProperties() override
    {
        return &m_Properties ;
    }

    virtual INodeEventContext* GetNodeEventContext() override
    {
        return m_pNodeEventContext ;
    }

    // ------------------
    // --- IInfectionHIV Methods 
    // ------------------
    virtual float GetWHOStage() const override
    {
        return m_WhoStage ;
    }

    virtual NaturalNumber GetViralLoad()              const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual float GetPrognosis()                      const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual float GetTimeInfected()                   const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual float GetDaysTillDeath()                  const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual const HIVInfectionStage::Enum& GetStage() const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void SetupSuppressedDiseaseTimers()             override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void ApplySuppressionDropout()                  override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void ApplySuppressionFailure()                  override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }


    // ------------------
    // --- IIndividualHumanSTI Methods 
    // ------------------
    //virtual suids::suid GetSuid() const = 0; // pass-through to base
    //virtual bool IsInfected() const = 0; //  pass-through to base
    virtual bool IsBehavioralSuperSpreader()       const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual unsigned int GetExtrarelationalFlags() const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual bool IsCircumcised() const
    {
        return m_IsCircumcised;
    }

    virtual const IPKeyValueContainer& GetPropertiesConst() const override 
    {
        return m_Properties ;
    }

    virtual float GetCoInfectiveTransmissionFactor()           const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual float GetCoInfectiveAcquisitionFactor()           const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }

    virtual void UpdateSTINetworkParams(const char *prop = nullptr, const char* new_value = nullptr) override {throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented.");}

    virtual void UpdateInfectiousnessSTI(std::vector<act_prob_t> &act_prob_vec, unsigned int rel_id) override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }


    virtual void UpdatePausedRelationships( const Kernel::IdmDateTime &, float ) override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void UpdateHistory( const IdmDateTime& rCurrentTime, float dt ) override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual bool AvailableForRelationship(RelationshipType::Enum) const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void UpdateEligibility()                                    override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void ConsiderRelationships(float dt)                        override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void RemoveRelationship( IRelationship* pNewRelationship )  override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    //virtual std::string toString() const = 0 ;
    virtual unsigned int GetOpenRelationshipSlot() const       override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual NaturalNumber GetLast6MonthRels() const            override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual NaturalNumber GetLifetimeRelationshipCount() const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual NaturalNumber GetNumRelationshipsAtDeath() const   override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void NotifyPotentialExposure()                     override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void onEmigrating()                                override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual void onImmigrating()                               override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }
    virtual suids::suid GetNodeSuid() const                    override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }

    virtual void ClearAssortivityIndexes()                                     override { m_AssortivityIndex = -1; }
    virtual int GetAssortivityIndex( RelationshipType::Enum type ) const       override { return m_AssortivityIndex; }
    virtual void SetAssortivityIndex( RelationshipType::Enum type, int index ) override { m_AssortivityIndex = index; }

    virtual ProbabilityNumber getProbabilityUsingCondomThisAct( const IRelationshipParameters* pRelParams ) const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }

    virtual RelationshipSet_t& GetRelationshipsAtDeath() override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented."); }

    virtual float GetDebutAge() const override
    {
        return 13*365 ;
    }

    virtual RelationshipSet_t& GetRelationships() override
    {
        return m_Relationships ;
    }

    virtual void AddRelationship( IRelationship* pNewRelationship ) override
    {
        m_Relationships.insert( pNewRelationship );
    }

    virtual void UpdateNumCoitalActs( uint32_t numActs ) override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }
    virtual uint32_t GetTotalCoitalActs()          const override { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }
    virtual NaturalNumber GetLast6MonthRels( RelationshipType::Enum ofType ) const
    {
        return 0;
    }

    virtual NaturalNumber GetLast12MonthRels( RelationshipType::Enum ofType ) const override
    {
        return 0;
    }

    virtual NaturalNumber GetNumUniquePartners( int itp, int irel ) const override
    {
        return 0;
    }

    virtual NaturalNumber GetLifetimeRelationshipCount( RelationshipType::Enum ofType ) const
    {
        return 0;
    }

    // ---------------------------------
    // --- IMalariaHumanContext Methods 
    // ---------------------------------

    virtual const SimulationConfig *params() const    { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }
    virtual void  PerformMalariaTest( int test_type ) { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }
    virtual void  CountPositiveSlideFields( RANDOMBASE * rng,
                                            int nfields,
                                            float uL_per_field,
                                            int& positive_asexual_fields,
                                            int& positive_gametocyte_fields ) const
    {
        throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." );
    }
    virtual bool  CheckForParasitesWithTest(    int test_type )            const { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }
    virtual float CheckParasiteCountWithTest(   int test_type )            const { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }
    virtual float CheckGametocyteCountWithTest( int test_type )            const { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }
    virtual float GetGametocyteDensity()                                   const { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }
    virtual bool  HasFever()                                               const { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }
    virtual void  AddClinicalSymptom( ClinicalSymptomsEnum::Enum symptom )       { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }
    virtual bool  HasClinicalSymptom( ClinicalSymptomsEnum::Enum symptom ) const { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }
    virtual IMalariaSusceptibility* GetMalariaSusceptibilityContext()      const { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }
    virtual std::vector<std::pair<uint32_t,uint64_t>> GetInfectingStrainIds()     const { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }
    virtual bool ChallengeWithBites( int n_infectious_bites )                    { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }
    virtual bool ChallengeWithSporozoites( int n_sporozoites )                   { throw Kernel::NotYetImplementedException( __FILE__, __LINE__, __FUNCTION__, "The method or operation is not implemented." ); }



    // ------------------
    // --- Other Methods 
    // ------------------
    void SetId( int id )
    {
        m_Id.data = id ;
    }

    void SetIntendsToBreastfeed( bool feed )
    {
        m_IntendsToBreastfeed = feed ;
    }

    void SetIsPregnant( bool isPregnant )
    {
        m_IsPregnant = isPregnant ;
    }

    void SetGender( int gender )
    {
        m_Gender = gender ;
    }

    void SetAge( float age )
    {
        m_Age = age ;
    }

    void SetWhoStage( float stage )
    {
        m_WhoStage = stage ;
    }

    void SetHasSTI( bool hasSTI )
    {
        m_HasSTI = hasSTI ;
        release_assert( !(m_HasSTI && (m_HasCoSTI || m_HasHIV)) );
    }

    void SetHasHIV( bool hasHIV )
    {
        m_HasHIV = hasHIV ;
        release_assert( !(m_HasSTI && (m_HasCoSTI || m_HasHIV)) );
    }

    void SetIsCircumcised( bool isCircumcised )
    {
        m_IsCircumcised = isCircumcised;
    }

    void SetRandUL( uint32_t ul )
    {
        release_assert( m_pMyRand == nullptr );
        m_Rand.SetUL( ul );
    }

    void SetRandUL( const std::vector<uint32_t>& rUlVector )
    {
        release_assert( m_pMyRand == nullptr );
        m_Rand.SetUL( rUlVector );
    }

    void SetMyRand( RANDOMBASE* pRng )
    {
        m_pMyRand = pRng;
    }

private:
    int m_RefCount ;
    suids::suid m_Id ;
    IIndividualHumanInterventionsContext* m_pInterventionsContext ;
    INodeContext* m_pNodeContext ;
    INodeEventContext* m_pNodeEventContext ;
    ISusceptibilityHIV* m_pISusceptibilityHIV ;
    RandomFake m_Rand ;
    RANDOMBASE* m_pMyRand;
    bool m_IntendsToBreastfeed ;
    bool m_IsPregnant ;
    int m_Gender ;
    float m_Age ;
    float m_WhoStage ;
    bool m_HasSTI ;
    bool m_HasHIV ;
    bool m_HasCoSTI ;
    RelationshipSet_t m_Relationships ;
    IPKeyValueContainer m_Properties ;
    bool m_IsCircumcised;
    int m_AssortivityIndex;
};


