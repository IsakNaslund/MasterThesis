using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Expressions;

namespace CIFem_grasshopper
{
    public class BeamReleaseParameter : Grasshopper.Kernel.GH_Param<BeamReleaseGoo>
    {
        public BeamReleaseParameter():base("BeamRelease", "BR", "Release for 3d beam", "CIFem", "Elements", Grasshopper.Kernel.GH_ParamAccess.item)
        { }


        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("aa256079-afa6-4e98-a639-fef249c951ac");
            }
        }
    }
}
