using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;
using CIFem_wrapper;
using System.Drawing;

namespace CIFem_grasshopper.Components
{
    public class BeamSpringReleaseComponent : GH_Component
    {
        public BeamSpringReleaseComponent(): base("Beam spring release", "BSR", 
            "Construct a beam release with possibility of constructing springs. Note that all releases are in global coordinates.", 
            "CIFem", "Elements")
        { }


        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("c2c38109-395a-4276-acf4-b82fae9776f7");
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
            pManager.AddNumberParameter("X-translation", "X", "Fix translation in x direction. val < 0 => fixed, val = 0 => released, val > 0 => spring with stiffness=val", GH_ParamAccess.item);
            pManager.AddNumberParameter("Y-translation", "Y", "Fix translation in y direction. val < 0 => fixed, val = 0 => released, val > 0 => spring with stiffness=val", GH_ParamAccess.item);
            pManager.AddNumberParameter("Z-translation", "Z", "Fix translation in Z direction. val < 0 => fixed, val = 0 => released, val > 0 => spring with stiffness=val", GH_ParamAccess.item);
            pManager.AddNumberParameter("X-rotation", "XX", "Fix rotation around the x-axis. val < 0 => fixed, val = 0 => released, val > 0 => spring with stiffness=val", GH_ParamAccess.item);
            pManager.AddNumberParameter("Y-rotation", "YY", "Fix rotation around the x-axis. val < 0 => fixed, val = 0 => released, val > 0 => spring with stiffness=val", GH_ParamAccess.item);
            pManager.AddNumberParameter("Y-rotation", "ZZ", "Fix rotation around the x-axis. val < 0 => fixed, val = 0 => released, val > 0 => spring with stiffness=val", GH_ParamAccess.item);

        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddParameter(new BeamReleaseParameter(), "Release", "R", "Release for beam", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            double x = 0;
            double y = 0;
            double z = 0;
            double xx = 0;
            double yy = 0;
            double zz = 0;

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
                return Properties.Resources.BeamSpringReleaseIcon;
            }
        }
    }
}