using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Expressions;

namespace CIFem_grasshopper
{
    public class NodeParam : GH_Param<NodeGoo>
    {
        public NodeParam():base(new GH_InstanceDescription("Node", "N", "Node (3d)", "CIFem", "Parameters"))
        { }


        public override Guid ComponentGuid
        { 
            get
            {
                return new Guid("76e98e7d-767e-47f2-80a3-4141262de18c");
            }
        }

    }
}
