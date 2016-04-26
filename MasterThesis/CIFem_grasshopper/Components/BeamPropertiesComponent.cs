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
            pManager.AddParameter(new Element3dOptPropParameter(), "Cross section Group", "XSG", "Optional cross section group to be used be optimizers", GH_ParamAccess.item);

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
            WR_Element3dOptProp optProp = null;

            if (!DA.GetData(0, ref xSec)) { return; }
            if (!DA.GetData(1, ref stREl)) { return; }
            if (!DA.GetData(2, ref enREl)) { return; }
            if (!DA.GetData(3, ref mat)) { return; }

            // Check releases
            if (!CheckReleases(stREl, enREl))
                return;

            BeamProperties beamProp;

            if (!DA.GetData(4, ref optProp))
                beamProp = new BeamProperties(mat, xSec, stREl, enREl);
            else
                beamProp = new BeamProperties(mat, xSec, stREl, enREl, optProp);


            DA.SetData(0, beamProp);

        }

        protected override Bitmap Icon
        {
            get
            {
                return CIFem_grasshopper.Properties.Resources.BeamPropertiesIcon;
            }
        }


        /// <summary>
        /// Checks the releases so that at least one end is restrained in x-, y-, z- and xx.
        /// </summary>
        /// <param name="sr"></param>
        /// <param name="er"></param>
        /// <returns>True if check is ok, false if errors exist</returns>
        private bool CheckReleases(WR_ReleaseBeam3d sr, WR_ReleaseBeam3d er)
        {
            bool b = true;

            string log = "Error, one of the ends must be restrained. Both ends unrestrained in:\n";

            if (sr.GetX() == 0 && er.GetX() == 0)
            {
                log += "X-dir\n";
                b = false;
            }
            if (sr.GetY() == 0 && er.GetY() == 0)
            {
                log += "Y-dir\n";
                b = false;
            }
            if (sr.GetZ() == 0 && er.GetZ() == 0)
            {
                log += "Z-dir\n";
                b = false;
            }
            if (sr.GetXX() == 0 && er.GetXX() == 0)
            {
                log += "Torsion\n";
                b = false;
            }

            if (!b)
                AddRuntimeMessage(GH_RuntimeMessageLevel.Error, log);

            return b;
        }
    }
}
