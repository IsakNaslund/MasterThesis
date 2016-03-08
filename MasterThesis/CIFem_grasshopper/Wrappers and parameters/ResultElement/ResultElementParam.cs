using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel.Types;
using Grasshopper.Kernel;

namespace CIFem_grasshopper
{
    public class ResultElementParam : Grasshopper.Kernel.GH_Param<ResultElementGoo>
    {
        public ResultElementParam():base(new GH_InstanceDescription("Element results parameter", "ElRes", "A results parameter for elements","CIFem","Results"))
        {
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("15dd06f1-7f94-421e-a5f0-764ad3081864");
            }
        }
    }
}
