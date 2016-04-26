using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_grasshopper;
using Grasshopper.Kernel;

using Rhino.Geometry;

namespace CIFem_grasshopper
{
    public class PointLoadComponent : GH_Component
    {
        public PointLoadComponent(): base("Point load", "PL", "Constructs a point load", "CIFem", "Loads")
        {
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("dba792b2-acfd-4867-89ad-2146d16c3b56");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddPointParameter("Load position", "P", "Position of the poit load", GH_ParamAccess.item);
            pManager.AddVectorParameter("Force", "F", "Force. Defaulted to 0 vector.", GH_ParamAccess.item, new Vector3d(0, 0, 0));
            pManager.AddVectorParameter("Moment", "M", "Moment. Defaulted to 0 vector.", GH_ParamAccess.item, new Vector3d(0,0,0));
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddParameter(new PointLoadParameter(), "PointLoad", "PL", "Constructed point load", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            Point3d pos = Point3d.Unset;
            Vector3d force = Vector3d.Unset;
            Vector3d moment = Vector3d.Unset;

            if (!DA.GetData(0,ref pos)) { return; }
            if (!DA.GetData(1, ref force)) { return; }
            if (!DA.GetData(2, ref moment)) { return; }

            DA.SetData(0, new PointLoadCarrier(pos, force, moment));
        }

        protected override Bitmap Icon
        {
            get
            {
                return Properties.Resources.PointLoadIcon;
            }
        }
    }
}
