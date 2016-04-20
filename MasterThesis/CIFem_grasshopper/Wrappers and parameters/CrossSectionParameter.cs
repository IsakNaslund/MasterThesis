using Grasshopper.Kernel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CIFem_grasshopper
{
    public class CrossSectionParameter : GH_Param<CrossSectionGoo>
    {
        public CrossSectionParameter():base(new GH_InstanceDescription("Cross Section", "XS", "Cross section for a beam", "CIFem", "Parameters"))
        { }


        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("b14bb3c7-7ca4-439e-8431-3704d657ffd4");
            }
        }


    }
}