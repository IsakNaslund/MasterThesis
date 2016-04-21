using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel.Types;
using Grasshopper.Kernel;

namespace CIFem_grasshopper
{
    public class UtilisationParam : Grasshopper.Kernel.GH_Param<UtilisationGoo>
    {
        public UtilisationParam():base(new GH_InstanceDescription("Utilisation", "U", "Section utilisation","CIFem", "Parameters"))
        {
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("0deeb10a-b811-4cf1-86c9-3de6e0557006");
            }
        }
    }
}
