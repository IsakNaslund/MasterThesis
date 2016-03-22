using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Expressions;

namespace CIFem_grasshopper
{
    public class StructureParam : GH_Param<StructureGoo>
    {
        public StructureParam():base(new GH_InstanceDescription("Structure", "Str", "A structure", "CIFem", "Structure"))
        { }


        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("f8755248-b560-470b-ab1e-e86988ba935a");
            }
        }

        public override GH_Exposure Exposure
        {
            get
            {
                return GH_Exposure.hidden;
            }
        }
    }
}
