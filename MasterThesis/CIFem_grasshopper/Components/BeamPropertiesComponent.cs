using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;

using CIFem_wrapper;
using System.Drawing;

namespace CIFem_grasshopper
{
    public class BeamPropertiesComponent : GH_Component
    {
        public BeamPropertiesComponent(): base("Beam Properties", "BP", "Construct a beam properties", "CIFem", "Elements")
        { }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("7c40bc15-7da3-4495-a40e-1dcf2014e8e9");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new CrossSectionParameter(),"Cross section", "XS", "Cross section for the beam. Can be provided as a full cross section or as a string in correct format. "+
                "String formats:\nRectangular solid: REC[H]x[W]\nRectangular hollow: RHS[H]x[W]x[t]\nCircular solid: CSS[r]\nCircular hollow: CHS[r]x[t]", GH_ParamAccess.item);
            pManager.AddParameter(new BeamReleaseParameter(), "Start Release", "SR", "Release at the start point fo the beam", GH_ParamAccess.item);
            pManager.AddParameter(new BeamReleaseParameter(), "End Release", "ER", "Release at the end point fo the beam", GH_ParamAccess.item);
            pManager.AddParameter(new MaterialParam(), "Material", "M", "Material to use in the beam", GH_ParamAccess.item);
            pManager.AddParameter(new CrossSectionGroupParameter(), "Cross section Group", "XSG", "Optional cross section group to be used be optimizers", GH_ParamAccess.item);

            pManager[4].Optional = true;
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddParameter(new BeamPropertiesParam(), "Beam Properteies", "P", "Properties for a 3d beam", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            // string crossSection = "";
            WR_IXSec xSec= null;
            WR_ReleaseBeam3d stREl = null;
            WR_ReleaseBeam3d enREl = null;
            WR_Material mat = null;
            WR_SectionGroup secGroup = null;

            if (!DA.GetData(0, ref xSec)) { return; }
            if (!DA.GetData(1, ref stREl)) { return; }
            if (!DA.GetData(2, ref enREl)) { return; }
            if (!DA.GetData(3, ref mat)) { return; }


            BeamProperties beamProp;

            if (!DA.GetData(4, ref secGroup))
                beamProp = new BeamProperties(mat, xSec, stREl, enREl);
            else
                beamProp = new BeamProperties(mat, xSec, stREl, enREl, secGroup);


            DA.SetData(0, beamProp);

        }

        protected override Bitmap Icon
        {
            get
            {
                return CIFem_grasshopper.Properties.Resources.BeamPropertiesIcon;
            }
        }
    }
}
