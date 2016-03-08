using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;
using Rhino.Geometry;

namespace CIFem_grasshopper
{
    public class DisplacementComponent : GH_Component
    {

        List<Curve> _dispCrvs;

        public DisplacementComponent() : base("Element displacement", "eDisp", "Displays the displacement of the elements", "CIFem", "Results")
        {
            _dispCrvs = new List<Curve>();
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("ac587a53-5152-4af4-ae66-717af162a143");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new ResultElementParam(), "Result Element", "RE", "Result element", GH_ParamAccess.list);
            pManager.AddNumberParameter("Scale factor", "s", "The displacement scale", GH_ParamAccess.item, 10);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {


        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            List<ResultElement> res = new List<ResultElement>();
            double sFac = double.NaN;

            if (!DA.GetDataList(0, res)) { return; }
            if (!DA.GetData(1, ref sFac)) { return; }

            _dispCrvs.Clear();

            Point3d stPos, enPos;

            foreach (ResultElement re in res)
            {
                
            }


        }


        public override void DrawViewportWires(IGH_PreviewArgs args)
        {
            base.DrawViewportWires(args);
        }
    }
}
