/***************************************************************************************************

Copyright (c) 2018 Intellectual Ventures Property Holdings, LLC (IVPH) All rights reserved.

EMOD is licensed under the Creative Commons Attribution-Noncommercial-ShareAlike 4.0 License.
To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode

***************************************************************************************************/

#include "stdafx.h"
#include <memory> // unique_ptr
#include "UnitTest++.h"
#include "componentTests.h"
#include "INodeContextFake.h"
#include "RandomFake.h"

#include "NodeProperties.h"
#include "Environment.h"
#include "Log.h"
#include "NodeDemographics.h"
#include "FileSystem.h"
#include "IdmMpi.h"

using namespace std; 
using namespace Kernel; 

SUITE(NodePropertiesTest)
{
    struct NodePropertiesTestFixture
    {
        IdmMpi::MessageInterface* m_pMpi;
        suids::suid next_suid;

        NodePropertiesTestFixture()
            : next_suid(suids::nil_suid())
        {
            next_suid.data++;

            Environment::setLogger(new SimpleLogger());
            int argc      = 1;
            char* exeName = "componentTests.exe";
            char** argv   = &exeName;
            string configFilename("testdata/NodePropertiesTest/config.json");
            string inputPath(".;testdata/NodePropertiesTest");
            string outputPath("testdata/NodePropertiesTest/output");
            string statePath("testdata/NodePropertiesTest");
            string dllPath("testdata/NodePropertiesTest");

            m_pMpi = IdmMpi::MessageInterface::CreateNull();

            Environment::Initialize( m_pMpi, configFilename, inputPath, outputPath, /*statePath, */dllPath, false);

            NPFactory::DeleteFactory();
            NPFactory::CreateFactory();
        }

        ~NodePropertiesTestFixture()
        {
            NPFactory::DeleteFactory();
            Environment::Finalize();
            NodeDemographicsFactory::SetDemographicsFileList( std::vector<std::string>() ) ;
        }

        suids::suid GetNextNodeSuid()
        {
            suids::suid next = next_suid;
            next_suid.data++;
            return next;
        }

        void TestReadingError( int lineNumber, bool isNodePropertiesError, const std::string& rDemogFilename, const std::string& rExpMsg )
        {
            // --------------------
            // --- Initialize test
            // --------------------
            NodeDemographicsFactory::SetDemographicsFileList( NodeDemographicsFactory::ConvertLegacyStringToSet( rDemogFilename ) ) ;

            unique_ptr<NodeDemographicsFactory> factory( NodeDemographicsFactory::CreateNodeDemographicsFactory(Environment::getInstance()->Config) );

            try
            {
                NPFactory::GetInstance()->Initialize( factory->GetNodePropertiesJson() );
                CHECK_LN( !isNodePropertiesError, lineNumber ); // if node property error, it shouldn't get here
            }
            catch( DetailedException& de )
            {
                std::string msg = de.GetMsg();
                bool passed = msg.find( rExpMsg ) != std::string::npos;
                if( !passed )
                {
                    PrintDebug( msg );
                }
                CHECK_LN( passed, lineNumber );
            }

            if( !isNodePropertiesError )
            {
                INodeContext* nodeContext = new INodeContextFake();
                unique_ptr<NodeDemographics> demographics( factory->CreateNodeDemographics( nodeContext ) );

                RandomFake rng;
                rng.SetUL( 0xFF0000 );

                try
                {
                    NPFactory::GetInstance()->GetInitialValues( &rng, demographics->GetJsonObject() );
                    CHECK_LN( false, lineNumber );
                }
                catch( DetailedException& e )
                {
                    std::string msg = e.GetMsg();
                    bool passed = msg.find( rExpMsg ) != std::string::npos;
                    if( !passed )
                    {
                        PrintDebug( msg );
                    }
                    CHECK_LN( passed, lineNumber );
                }
            }
        }
    };

    TEST_FIXTURE(NodePropertiesTestFixture, TestRead)
    {
        // --------------------
        // --- Initialize test
        // --------------------
        unique_ptr<NodeDemographicsFactory> factory( NodeDemographicsFactory::CreateNodeDemographicsFactory(Environment::getInstance()->Config) );

        NPFactory::GetInstance()->Initialize( factory->GetNodePropertiesJson() );

        try
        {
            INodeContext* nodeContext = new INodeContextFake();
            unique_ptr<NodeDemographics> demographics( factory->CreateNodeDemographics(nodeContext) );


            RandomFake rng;
            rng.SetUL( 0xFF0000);

            NPKeyValueContainer np_values = NPFactory::GetInstance()->GetInitialValues( &rng, demographics->GetJsonObject() );

            std::vector<NodeProperty*> np_list = NPFactory::GetInstance()->GetNPList();
            CHECK_EQUAL( 2, np_list.size() );
            CHECK_EQUAL( std::string("InterventionStatus"), np_list[0]->GetKey<NPKey>().ToString() );
            CHECK_EQUAL( std::string("Place"             ), np_list[1]->GetKey<NPKey>().ToString() );

            NPKeyValueContainer np_values_1 = np_list[0]->GetValues<NPKeyValueContainer>();
            CHECK_EQUAL( 4, np_values_1.Size() );
            CHECK(  np_values_1.Contains( "InterventionStatus:NONE"           ) );
            CHECK(  np_values_1.Contains( "InterventionStatus:SPRAYED_A"      ) );
            CHECK(  np_values_1.Contains( "InterventionStatus:SPRAYED_B"      ) );
            CHECK(  np_values_1.Contains( "InterventionStatus:FENCE_AND_TRAP" ) );
            CHECK( !np_values_1.Contains( "InterventionStatus:XXX"            ) );

            NPKeyValueContainer np_values_2 = np_list[ 1 ]->GetValues<NPKeyValueContainer>();
            CHECK_EQUAL( 2, np_values_2.Size() );
            CHECK( np_values_2.Contains( "Place:RURAL" ) );
            CHECK( np_values_2.Contains( "Place:URBAN" ) );

        }
        catch( DetailedException& e )
        {
            PrintDebug( e.GetMsg() );
            CHECK( false );
        }
    }

    TEST_FIXTURE(NodePropertiesTestFixture, TestUninitialized)
    {
        try
        {
            NPKey key ;
            CHECK( !key.IsValid() );
            key.ToString();
            CHECK( false );
        }
        catch( NullPointerException& )
        {
            CHECK( true );
        }

        NPKeyValue kv ;
        CHECK( !kv.IsValid() );
        try
        {
            kv.ToString();
            CHECK( false );
        }
        catch( NullPointerException& )
        {
            CHECK( true );
        }

        try
        {
            kv.GetKey<NPKey>();
            CHECK( false );
        }
        catch( NullPointerException& )
        {
            CHECK( true );
        }

        try
        {
            kv.GetValueAsString();
            CHECK( false );
        }
        catch( NullPointerException& )
        {
            CHECK( true );
        }

        try
        {
            kv.GetInitialDistribution();
            CHECK( false );
        }
        catch( NullPointerException& )
        {
            CHECK( true );
        }
    }

    TEST_FIXTURE(NodePropertiesTestFixture, TestMissingValues)
    {
        TestReadingError( __LINE__, true, "testdata/NodePropertiesTest/demog_TestMissingValues.json",
                          "Failed to find Values in map demographics[NodeProperties][0]");
    }

    TEST_FIXTURE(NodePropertiesTestFixture, TestMissingInitialDistribution)
    {
        TestReadingError( __LINE__, true, "testdata/NodePropertiesTest/demog_TestMissingInitialDistribution.json",
                          "Failed to find Initial_Distribution in map demographics[NodeProperties][0]");
    }

    TEST_FIXTURE(NodePropertiesTestFixture, TestInvalidNumInitialDistribution)
    {
        TestReadingError( __LINE__, true, "testdata/NodePropertiesTest/demog_TestInvalidNumInitialDistribution.json",
                          "Number of Values in Values (2) needs to be the same as number of values in Initial_Distribution (3).");
    }

    TEST_FIXTURE(NodePropertiesTestFixture, TestDuplicateValues)
    {
        TestReadingError( __LINE__, true, "testdata/NodePropertiesTest/demog_TestDuplicateValues.json",
                          "demographics[NodeProperties][0] with property=Risk has a duplicate value = HIGH");
    }

    TEST_FIXTURE(NodePropertiesTestFixture, TestZeroValues)
    {
        TestReadingError( __LINE__, true, "testdata/NodePropertiesTest/demog_TestZeroValues.json",
                          "demographics[NodeProperties][0][Values] (property=Risk) cannot have zero values.");
    }

    TEST_FIXTURE(NodePropertiesTestFixture, TestInvalidInitialDistribution)
    {
        TestReadingError( __LINE__, true, "testdata/NodePropertiesTest/demog_TestInvalidInitialDistribution.json",
                          "The values in demographics[NodeProperties][1][Initial_Distribution] (property=Risk) add up to 1.45.  They must add up to 1.0");
    }

    TEST_FIXTURE( NodePropertiesTestFixture, TestNodePropertyValues_UnknownKey )
    {
        TestReadingError( __LINE__, false, "testdata/NodePropertiesTest/demog_TestNodePropertyValues_UnknownKey.json",
                          "Could not find the key(XXX) for the key-value=XXX:URBAN.  Possible keys are: InterventionStatus, Place" );
    }

    TEST_FIXTURE( NodePropertiesTestFixture, TestNodePropertyValues_UnknownValue )
    {
        TestReadingError( __LINE__, false, "testdata/NodePropertiesTest/demog_TestNodePropertyValues_UnknownValue.json",
                          "Could not find the value(XXX) for the key(Place).  Possible values for the key are: RURAL, URBAN" );
    }

    TEST_FIXTURE( NodePropertiesTestFixture, TestNodePropertyValues_BadFormat )
    {
        TestReadingError( __LINE__, false, "testdata/NodePropertiesTest/demog_TestNodePropertyValues_BadFormat.json",
                          "Invalid NodeProperties Key-Value string = 'XXX-BadFormat-XXX'.  Format is 'key:value'." );
    }
}
