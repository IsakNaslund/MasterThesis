using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;
using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class MaterialComponent : GH_Component
    {
        public MaterialComponent() : base("Material", "Mat", "Set up a material to use i structures", "CIFem", "Elements")
        {
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("adaa5568-1007-400a-9124-871b77e5966c");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddNumberParameter("Material Stiffness", "E", "Youngs modulus for the beam, set to steel by deafault", GH_ParamAccess.item, 210000000000);
            pManager.AddNumberParameter("Poisons ratio", "p", "Poisons ration for the material of the beam, set to steel by default", GH_ParamAccess.item, 0.3);
            pManager.AddNumberParameter("Density", "d", "Density of the material. Given in kg/m3", GH_ParamAccess.item, 7800);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddParameter(new MaterialParam(), "Material", "M", "The constructed material", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            double E, p, rho;
            E = 0;
            p = 0;
            rho = 0;

            if (!DA.GetData(0, ref E)) { return; }
            if (!DA.GetData(1, ref p)) { return; }
            if (!DA.GetData(2, ref rho)) { return; }

            WR_Material mat = new WR_Material(E, p, rho);


            DA.SetData(0, mat);

        }
    }
}
