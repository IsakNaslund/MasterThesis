using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;

namespace CIFem_grasshopper
{
    public class ModeLoadCaseComponent : GH_Component
    {
        public ModeLoadCaseComponent() : base("Mode Choser", "Mode", "Constructs a load case string for eigen modes from an integer", "CIFem", "Results")
        {
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("b03d7e1c-46a9-459a-8d00-effaf9d353c9");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddIntegerParameter("Mode number", "M", "The mode number that you want to evaluate", GH_ParamAccess.item);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddTextParameter("Mode Load case", "LC", "Created load case string", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            int i = 0;

            if (!DA.GetData(0, ref i)) { return; }

            string lc = "Mode " + i;
            
            DA.SetData(0, lc);
        }

        public override GH_Exposure Exposure
        {
            get
            {
                return GH_Exposure.tertiary;
            }
        }
    }
}
