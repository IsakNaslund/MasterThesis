using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;

using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class UtilisationComponent : GH_Component
    {
        public UtilisationComponent(): base("Utilisation Decomposition", "UtilDecomp", "Decomposes the utilisation parameter into a value and a description", "CIFem", "Results")
        {
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("8cac24d3-653d-475b-a491-f1ef3ecea2b5");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new UtilisationParam(), "Utilisation", "U", "Highest utilisation", GH_ParamAccess.item);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddNumberParameter("Utilisation degree", "U", "A number of the utilisations which ranges from 0 (not utilised at all) to 1 (utilised to the limit) and beyond (overutilised)", GH_ParamAccess.item);
            pManager.AddTextParameter("Utilisation description", "desc", "Information of the utilisation type", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            // Indata
            WR_Utilisation util = null;
            if (!DA.GetData(0, ref util)) { return; }

            DA.SetData(0, util.GetUtilisationDegree());
            DA.SetData(1, util.ToString());
        }
    }
}
