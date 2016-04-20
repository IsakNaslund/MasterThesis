using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel.Types;
using Grasshopper.Kernel;

namespace CIFem_grasshopper
{
    public class MaterialParam : GH_Param<MaterialGoo>
    {

        public MaterialParam() :base(new GH_InstanceDescription("Material", "M", "Material to use in structures","CIFem", "Parameters"))
        {
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("4e49f22b-7fca-41d0-8938-42857c169787");
            }
        }

    }
}
