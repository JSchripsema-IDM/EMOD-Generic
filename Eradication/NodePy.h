/***************************************************************************************************

Copyright (c) 2018 Intellectual Ventures Property Holdings, LLC (IVPH) All rights reserved.

EMOD is licensed under the Creative Commons Attribution-Noncommercial-ShareAlike 4.0 License.
To view a copy of this license, visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode

***************************************************************************************************/

#pragma once
#include "Node.h"
#include "IndividualPy.h"

class ReportPy;

namespace Kernel
{
    class SpatialReportPy;

    class INodePy : public ISupports
    {
    public:
    };

    class NodePy : public Node, public INodePy
    {
        IMPLEMENT_DEFAULT_REFERENCE_COUNTING()

        // TODO Get rid of friending and provide accessors for all these floats
        friend class ::ReportPy;
        friend class Kernel::SpatialReportPy;

    public:
        static NodePy *CreateNode(ISimulationContext *_parent_sim, ExternalNodeId_t externalNodeId, suids::suid node_suid);
        virtual ~NodePy(void);

        virtual void resetNodeStateCounters(void);

    protected:
        NodePy();
        NodePy(ISimulationContext *_parent_sim, ExternalNodeId_t externalNodeId, suids::suid node_suid);
        virtual void Initialize() override;

        // Factory methods
        virtual Kernel::IndividualHuman *createHuman(suids::suid suid, float monte_carlo_weight, float initial_age, int gender);
    };

    class NodePyTest : public NodePy
    {
        public:
            static NodePyTest *CreateNode(ISimulationContext *_parent_sim, ExternalNodeId_t externalNodeId, suids::suid node_suid);
        protected:
            NodePyTest(ISimulationContext *_parent_sim, ExternalNodeId_t externalNodeId, suids::suid node_suid);
        private:
    };
}
