using Grasshopper.Kernel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CIFem_grasshopper
{
    public class LoadCombParameter : Grasshopper.Kernel.GH_Param<LoadCombGoo>
    {
        public LoadCombParameter():base(new GH_InstanceDescription("Load combiation", "LC", "Load combination", "CIFem", "Parameters"))
        { }


        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("f93c61aa-7ce1-43d5-8ed9-3fa982b94c5d");
            }
        }
    }
}
