using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;

using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class ResultElementComponent : GH_Component
    {
        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("5e9a2fd9-b9ed-41d4-a4af-077f8c9a7ee6");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {

            pManager.AddBooleanParameter("X-translation", "X", "Fix translation in x direction", GH_ParamAccess.item);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddParameter(new ResultElementParam(), "Result Elements", "RE", "Result elements, storing results from the calculation", GH_ParamAccess.list);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            throw new NotImplementedException();
        }
    }
}
