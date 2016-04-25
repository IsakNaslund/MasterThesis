using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;

namespace CIFem_grasshopper.Debug
{
    public class DebugClassParameter : Grasshopper.Kernel.GH_Param<CIFem_grasshopper.Debug.DebugClassGoo>
    {
        public DebugClassParameter():base(new GH_InstanceDescription("Debug Class", "Debug", "A parameter for debugging purposes","CIFem", "Parameters"))
        {
        }

        public override GH_Exposure Exposure
        {
            get
            {
                return GH_Exposure.hidden;
            }
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("624ae66f-d6dd-4f12-ae64-6bfcb0663522");
            }
        }
    }
}
