/***************************************************************************************************

Copyright (c) 2018 Intellectual Ventures Property Holdings, LLC (IVPH) All rights reserved.

EMOD is licensed under the Creative Commons Attribution-Noncommercial-ShareAlike 4.0 License.
To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode

***************************************************************************************************/

#include "stdafx.h"

#include "IIndividualHuman.h"
#include "PropertyReportTB.h"

using namespace std;
using namespace json;

SETUP_LOGGING( "PropertyReportTB" )


namespace Kernel
{

/////////////////////////
// Initialization methods
/////////////////////////
IReport* PropertyReportTB::CreateReport()
{
    return _new_ PropertyReportTB();
}

PropertyReportTB::PropertyReportTB()
    :PropertyReport( "PropertyReportTB.json" )
{
}

void PropertyReportTB::LogIndividualData( IIndividualHuman* individual )
{
    PropertyReport::LogIndividualData( individual );

    std::string reportingBucket = individual->GetPropertyReportString();

    float monte_carlo_weight = (float)individual->GetMonteCarloWeight();
    IIndividualHumanTB* individual_tb = individual->GetIndividualContext()->GetIndividualTB();

    if(individual->GetStateChange() == HumanStateChange::KilledByInfection)
    {
        if (individual_tb->IsMDR())
        {
            disease_deaths_MDR[ reportingBucket ] += monte_carlo_weight;
        }
        if (individual_tb->IsOnTreatment())
        {
            disease_deaths_onTreatment[ reportingBucket ] +=monte_carlo_weight;
            if (individual_tb->IsTreatmentNaive() ) 
            {
                disease_deaths_txnaive[ reportingBucket ] += monte_carlo_weight;
            }
        }
    }

    if( individual->GetNewInfectionState() == NewInfectionState::NewlyActive)
    {
        new_active_TB_infections[ reportingBucket ] +=  monte_carlo_weight;
    }
    
    if (individual->IsInfected())
    {
        if (individual_tb->HasActiveInfection() )
        {
            active_infections[ reportingBucket ] += monte_carlo_weight;
        
            if (individual_tb->IsSmearPositive() )
            {
                active_smearpos_infections[ reportingBucket ] += monte_carlo_weight;
            }
        
            if (individual_tb->IsTreatmentNaive() && !individual_tb->IsOnTreatment())
            {
                active_naive_infections[ reportingBucket ] += monte_carlo_weight;
                if (!individual_tb->HasActivePresymptomaticInfection() )
                {
                    active_naive_symptomatic_infections[ reportingBucket ] += monte_carlo_weight;
                }
            }
            else if ( (individual_tb->HasFailedTreatment() || individual_tb->HasEverRelapsedAfterTreatment() )  && !individual_tb->IsOnTreatment())
            {
                active_retx_infections[ reportingBucket ] += monte_carlo_weight;
            }
        }

        if (individual_tb->IsOnTreatment() ) 
        {
            onTreatment[ reportingBucket ] += monte_carlo_weight;
        }

        if (individual_tb->IsMDR() && individual_tb->HasActiveInfection()  ) 
        {
            MDR_active_infections[ reportingBucket ] += monte_carlo_weight;
        
            if ( individual_tb->IsSmearPositive() )
            {
                MDR_active_smearpos_infections[ reportingBucket ] += monte_carlo_weight;
            }
            if (individual_tb->IsEvolvedMDR() )
            {
                MDR_active_evolved_infections[ reportingBucket] += monte_carlo_weight;
            }
            if (individual_tb->IsTreatmentNaive() )
            {
                MDR_active_naive_infections[ reportingBucket ] += monte_carlo_weight;
            }
            else if ( (individual_tb->HasFailedTreatment() || individual_tb->HasEverRelapsedAfterTreatment() )  && !individual_tb->IsOnTreatment())
            {
                MDR_active_retx_infections[ reportingBucket ] += monte_carlo_weight;
            }
        }

        infectious_reservoir[ reportingBucket] += (individual->GetInfectiousness() * monte_carlo_weight);
        if (individual_tb->IsMDR() )
        {
            MDR_infectious_reservoir[ reportingBucket] += (individual->GetInfectiousness() * monte_carlo_weight);
        }

        if(individual_tb->HasActivePresymptomaticInfection() && individual_tb->IsTreatmentNaive())
        {
            presymp_tx_naive_infectious_reservoir[ reportingBucket] += (individual->GetInfectiousness() * monte_carlo_weight);
            if (individual_tb->IsMDR() )
            {
                MDR_presymp_tx_naive_infectious_reservoir[ reportingBucket] += (individual->GetInfectiousness() * monte_carlo_weight);
            }
        }
        if (individual_tb->HasActiveInfection() && !individual_tb->IsTreatmentNaive()) //includes failed people and people who went from pendingrelapse to active
        {
            Retx_infectious_reservoir[ reportingBucket ] += (individual->GetInfectiousness() * monte_carlo_weight);
            if (individual_tb->IsMDR() )
            {
                MDR_Retx_infectious_reservoir[ reportingBucket] += (individual->GetInfectiousness() * monte_carlo_weight);
            }
        }
        if (individual_tb->HasActiveInfection() && !individual_tb->HasActivePresymptomaticInfection())
        {
            active_symp_infectious_reservoir[ reportingBucket ] += (individual->GetInfectiousness() * monte_carlo_weight);
        
            if ( individual_tb->IsTreatmentNaive() )
            {
                active_symp_naive_infectious_reservoir[ reportingBucket ] += (individual->GetInfectiousness() * monte_carlo_weight);
                if (individual_tb->IsMDR() )
                {
                    MDR_active_symp_naive_infectious_reservoir[ reportingBucket] += (individual->GetInfectiousness() * monte_carlo_weight);
                }
            }        
        }
    }
}

void PropertyReportTB::LogNodeData( INodeContext* pNC )
{
    PropertyReport::LogNodeData(pNC);

    LOG_DEBUG( "LogNodeData in PropertyReportTB\n" );
    for (const auto& reportingBucket : permutationsSet)
    {
        Accumulate("Active TB Infections:" + reportingBucket,                            active_infections[reportingBucket] );
        active_infections[reportingBucket] = 0.0f;
        Accumulate("Active Naive TB Infections:" + reportingBucket,                        active_naive_infections[reportingBucket] );
        active_naive_infections[reportingBucket] = 0.0f;
        Accumulate("Active Retx TB Infections:" + reportingBucket,                        active_retx_infections[reportingBucket] );
        active_retx_infections[reportingBucket] = 0.0f;
        Accumulate("Active Naive Symptomatic TB Infections:" + reportingBucket,            active_naive_symptomatic_infections[reportingBucket] );
        active_naive_symptomatic_infections[reportingBucket] = 0.0f;
        Accumulate("Active Smearpos TB Infections:" + reportingBucket, active_smearpos_infections[reportingBucket] );
        active_smearpos_infections[reportingBucket] = 0.0f;

        Accumulate("Disease Deaths while on tx (cumulative):" + reportingBucket,        disease_deaths_onTreatment[reportingBucket]);
        Accumulate("Disease Deaths tx naive (cumulative):" + reportingBucket,            disease_deaths_txnaive[reportingBucket]);
        Accumulate("Disease Deaths MDR (cumulative):" + reportingBucket,            disease_deaths_MDR[reportingBucket]);
        Accumulate("Receiving Treatment:" + reportingBucket,        onTreatment[reportingBucket]);
        onTreatment[reportingBucket] = 0.0f;
        Accumulate("Active MDR TB Infections:" + reportingBucket,        MDR_active_infections[reportingBucket] );
        MDR_active_infections[reportingBucket] = 0.0f;
        Accumulate("Active MDR Naive TB Infections:" + reportingBucket,        MDR_active_naive_infections[reportingBucket] );
        MDR_active_naive_infections[reportingBucket] = 0.0f;
        Accumulate("Active MDR Retx TB Infections:" + reportingBucket,        MDR_active_retx_infections[reportingBucket] );
        MDR_active_retx_infections[reportingBucket] = 0.0f;
        Accumulate("Active MDR (evolved) TB Infections:" + reportingBucket, MDR_active_evolved_infections[reportingBucket] );
        MDR_active_evolved_infections[reportingBucket] = 0.0f;
        Accumulate("Active MDR Smearpos TB Infections:" + reportingBucket, MDR_active_smearpos_infections[reportingBucket] );
        MDR_active_smearpos_infections[reportingBucket] = 0.0f;
        
        Accumulate("Total Infectious Reservoir:" + reportingBucket, infectious_reservoir[reportingBucket] );
        infectious_reservoir[reportingBucket] = 0.0f;
        Accumulate("Active Presymptomatic Naive Infectious Reservoir:" + reportingBucket, presymp_tx_naive_infectious_reservoir[reportingBucket] );
        presymp_tx_naive_infectious_reservoir[reportingBucket] = 0.0f;
        Accumulate("Retx Infectious Reservoir:" + reportingBucket, Retx_infectious_reservoir[reportingBucket] );
        Retx_infectious_reservoir[reportingBucket] = 0.0f;
        Accumulate("Active Symptomatic Infectious Reservoir:" + reportingBucket, active_symp_infectious_reservoir[reportingBucket] );
        active_symp_infectious_reservoir[reportingBucket] = 0.0f;
        Accumulate("Active Symptomatic Naive Infectious Reservoir:" + reportingBucket, active_symp_naive_infectious_reservoir[reportingBucket] );
        active_symp_naive_infectious_reservoir[ reportingBucket ] = 0.0f;

        Accumulate("MDR Total Infectious Reservoir:" + reportingBucket, MDR_infectious_reservoir[reportingBucket] );
        MDR_infectious_reservoir[reportingBucket] = 0.0f;
        Accumulate("MDR Active Presymptomatic Naive Infectious Reservoir:" + reportingBucket, MDR_presymp_tx_naive_infectious_reservoir[reportingBucket] );
        MDR_presymp_tx_naive_infectious_reservoir[reportingBucket] = 0.0f;
        Accumulate("MDR Retx Infectious Reservoir:" + reportingBucket, MDR_Retx_infectious_reservoir[reportingBucket] );
        MDR_Retx_infectious_reservoir[reportingBucket] = 0.0f;
        Accumulate("MDR Active Symptomatic Naive Infectious Reservoir:" + reportingBucket, MDR_active_symp_naive_infectious_reservoir[reportingBucket] );
        MDR_active_symp_naive_infectious_reservoir[ reportingBucket ] = 0.0f;

        Accumulate("New Active Infections:" + reportingBucket, new_active_TB_infections[reportingBucket] );
        new_active_TB_infections[reportingBucket] = 0.0f;
   }
}

}

