using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel.Types;

namespace CIFem_grasshopper
{
    public class BeamParam : Grasshopper.Kernel.GH_Param<BeamGoo>
    {

        public BeamParam():base("3d beam", "3db", "3d beam used in frame structures","CIFem","Elements", Grasshopper.Kernel.GH_ParamAccess.item)
        {
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("71f3db8f-7b0d-4b3e-9b36-9f6d25766712");
            }
        }
    }
}
