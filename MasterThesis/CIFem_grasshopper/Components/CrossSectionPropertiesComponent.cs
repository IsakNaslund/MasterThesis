using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using Grasshopper.Kernel;
using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class CrossSectionPropertiesComponent : GH_Component
    {
        public CrossSectionPropertiesComponent() : base("Cross Section Properties", "XSecProp", "Gives structural properties for a crosssection", "CIFem", "Elements")
        {
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("ef56bcd0-6563-4677-ab53-fd9fb9130d27");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new CrossSectionParameter(), "Cross section", "XSec", "Cross section to evaluate", GH_ParamAccess.item);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddNumberParameter("Area", "A", "Cross section area", GH_ParamAccess.item);
            pManager.AddNumberParameter("Iy", "Iy", "Second area moment of intertia around the strong axis", GH_ParamAccess.item);
            pManager.AddNumberParameter("Iz", "Iz", "Second area moment of intertia around the weak axis", GH_ParamAccess.item);
            pManager.AddNumberParameter("StVenants", "Kv", "St Venants rotational constant for the cross section", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            WR_IXSec xSec = null;

            if(!DA.GetData(0, ref xSec)) { return; }


            DA.SetData(0, xSec.Area);
            DA.SetData(1, xSec.Iy);
            DA.SetData(2, xSec.Iz);
            DA.SetData(3, xSec.Kv);
        }
    }
}
