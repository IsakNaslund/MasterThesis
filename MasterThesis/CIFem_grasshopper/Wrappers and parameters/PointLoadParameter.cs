using Grasshopper.Kernel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CIFem_grasshopper
{
    public class PointLoadParameter : Grasshopper.Kernel.GH_Param<PointLoadGoo>
    {
        public PointLoadParameter():base(new GH_InstanceDescription("Point Load", "Pl", "Point Load", "CIFem", "Parameters"))
        { }


        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("f6e65c42-2fa2-4dab-a7cd-c786fab28385");
            }
        }
    }
}