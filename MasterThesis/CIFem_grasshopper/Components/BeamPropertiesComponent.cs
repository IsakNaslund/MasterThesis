using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;

using CIFem_wrapper;

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
            pManager.AddTextParameter("Cross section", "XS", "Cross section for the beam on string form", GH_ParamAccess.item);
            pManager.AddParameter(new BeamReleaseParameter(), "Start Release", "SR", "Release at the start point fo the beam", GH_ParamAccess.item);
            pManager.AddParameter(new BeamReleaseParameter(), "End Release", "ER", "Release at the end point fo the beam", GH_ParamAccess.item);
            pManager.AddNumberParameter("Material Stiffness", "E", "Youngs modulus for the beam, set to steel by deafault", GH_ParamAccess.item, 210000000000);
            pManager.AddNumberParameter("Poisons ratio", "p", "Poisons ration for the material of the beam, set to steel by default", GH_ParamAccess.item, 0.3);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddParameter(new BeamPropertiesParam(), "Beam Properteies", "P", "Properties for a 3d beam", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            string crossSection = "";
            WR_ReleaseBeam3d stREl = null;
            WR_ReleaseBeam3d enREl = null;
            double E = double.NaN;
            double poi = double.NaN;

            if (!DA.GetData(0, ref crossSection)) { return; }
            if (!DA.GetData(1, ref stREl)) { return; }
            if (!DA.GetData(2, ref enREl)) { return; }
            if (!DA.GetData(3, ref E)) { return; }
            if (!DA.GetData(4, ref poi)) { return; }

            BeamProperties beamProp = new BeamProperties(E, poi, crossSection, stREl, enREl);
            
            

            DA.SetData(0, beamProp);

        }
    }
}
