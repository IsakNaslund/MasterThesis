using Grasshopper.Kernel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CIFem_grasshopper
{
    public class CrossSectionGroupParameter : GH_Param<CrossSectionGroupGoo>
    {
        public CrossSectionGroupParameter():base(new GH_InstanceDescription("Cross Section Group", "XSG", "A collection of cross sections for a beam", "CIFem", "Parameters"))
        { }


        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("1c247d16-5e30-4112-ac1e-882907b449a4");
            }
        }


    }
}