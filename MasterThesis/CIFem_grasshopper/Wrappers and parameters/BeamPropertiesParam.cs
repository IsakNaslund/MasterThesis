using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CIFem_grasshopper
{
    public class BeamPropertiesParam : Grasshopper.Kernel.GH_Param<BeamPropertiesGoo>
    {

        public BeamPropertiesParam():base("3d Beam Prop", "3dbP", "Properties for a 3d beam","CIFem","Elements", Grasshopper.Kernel.GH_ParamAccess.item)
        {
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("0adfad12-b0fa-40af-82f7-4b8a92bd5339");
            }
        }
    }
}
