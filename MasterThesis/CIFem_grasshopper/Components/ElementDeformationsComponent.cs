using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;

using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class ElementDeformationsComponent : GH_Component
    {

        public ElementDeformationsComponent() : base("Element displacements", "eDis", "Extracts element displacements", "CIFem", "Results")
        {
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("bf5493c6-f5fa-4c0e-9e51-05b7362ba45d");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new ResultElementParam(), "Result Element", "RE", "Result element", GH_ParamAccess.item);
            pManager.AddTextParameter("Load Comb", "LC", "Load combination to display results from", GH_ParamAccess.item);

            pManager[1].Optional = true;
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddNumberParameter("Position", "pos", "The relative position along the element. 0 indicates the start node.", GH_ParamAccess.list);
            pManager.AddNumberParameter("X-displacement", "u", "Displacement along the local x-axis", GH_ParamAccess.list);
            pManager.AddNumberParameter("Y-displacement", "v", "Displacement along the local y-axis", GH_ParamAccess.list);
            pManager.AddNumberParameter("Z-displcement", "w", "Displacement along the local y-axis", GH_ParamAccess.list);
            pManager.AddNumberParameter("Torsional displacement", "phi", "Torsional displacement", GH_ParamAccess.list);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            // Indata
            ResultElement re = null;
            string name = null;
            if (!DA.GetData(0, ref re)) { return; }


            if (!DA.GetData(1, ref name))
            {
                name = re.N1.First().Key;
            }

            DA.SetDataList(0, re.pos);
            DA.SetDataList(1, re.u[name]);
            DA.SetDataList(2, re.v[name]);
            DA.SetDataList(3, re.w[name]);
            DA.SetDataList(4, re.fi[name]);
        }
    }
}
