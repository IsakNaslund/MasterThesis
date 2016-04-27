using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper;
using Grasshopper.Kernel;

using CIFem_wrapper;
using System.Drawing;

namespace CIFem_grasshopper
{
    public class BeamReleaseComponent : GH_Component
    {
        public BeamReleaseComponent(): base("Beam release", "BR", 
            "Construct a beam release. Note that all releases are in global coordinates.", "CIFem", "Elements")
        { }


        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("2362253f-5a8a-440b-80ad-a9ae4401576b");
            }
        }

        public override GH_Exposure Exposure
        {
            get
            {
                return GH_Exposure.secondary;
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddBooleanParameter("X-translation", "X", "Fix translation in x direction", GH_ParamAccess.item);
            pManager.AddBooleanParameter("Y-translation", "Y", "Fix translation in y direction", GH_ParamAccess.item);
            pManager.AddBooleanParameter("Z-translation", "Z", "Fix translation in Z direction", GH_ParamAccess.item);
            pManager.AddBooleanParameter("X-rotation", "XX", "Fix rotation around the x-axis", GH_ParamAccess.item);
            pManager.AddBooleanParameter("Y-rotation", "YY", "Fix rotation around the x-axis", GH_ParamAccess.item);
            pManager.AddBooleanParameter("Y-rotation", "ZZ", "Fix rotation around the x-axis", GH_ParamAccess.item);

        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddParameter(new BeamReleaseParameter(), "Release", "R", "Release for beam", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            bool x = false;
            bool y = false;
            bool z = false;
            bool xx = false;
            bool yy = false;
            bool zz = false;

            if (!DA.GetData(0, ref x)) { return; }
            if (!DA.GetData(1, ref y)) { return; }
            if (!DA.GetData(2, ref z)) { return; }
            if (!DA.GetData(3, ref xx)) { return; }
            if (!DA.GetData(4, ref yy)) { return; }
            if (!DA.GetData(5, ref zz)) { return; }

            WR_ReleaseBeam3d rel = new WR_ReleaseBeam3d(x, y, z, xx, yy, zz);

            DA.SetData(0, rel);
        }

        protected override Bitmap Icon
        {
            get
            {
                return CIFem_grasshopper.Properties.Resources.BeamReleaseIcon;
            }
        }
    }
}
