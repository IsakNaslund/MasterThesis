using Grasshopper.Kernel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Rhino.Geometry;

namespace CIFem_grasshopper
{
    public class DeconstructResultElements : GH_Component
    {

        public DeconstructResultElements() : base("Deconstruct Result elements", "ResElem", "Deconstructs the results elements into data", "CIFem", "Results")
        {

        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("066cdb9b-dcdc-487a-a251-621cefb0f152");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new ResultElementParam(), "Result Element", "RE", "Result element", GH_ParamAccess.item);

        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {

            pManager.AddLineParameter("Centre Line", "CL", "Centre Line of element", GH_ParamAccess.item);
            pManager.AddTextParameter("Cross Section", "XS", "Cross section of the element", GH_ParamAccess.item);
            pManager.AddVectorParameter("Normal", "N", "Normal of the elements", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            ResultElement res = null;

            if (!DA.GetData(0, ref res)) { return; }

            DA.SetData(0, new Line(res.sPos, res.ePos));
            DA.SetData(1, CrossSectionCasts.GetRhinoString(res.SectionPropertyString));
            DA.SetData(2, res.elNormal);
        }



    }
}