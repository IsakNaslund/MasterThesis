using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;

using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class ElementForcesComponent : GH_Component
    {

        public ElementForcesComponent() : base("Element forces", "eForce", "Extracts element forces in the previously given evaluation points", "CIFem", "Results")
        {
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("8405a17e-eef2-4a57-80aa-79b59f24e03b");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new ResultElementParam(), "Result Element", "RE", "Result element", GH_ParamAccess.item);
            pManager.AddTextParameter("Load Comb", "LC", "Load combination to display results from", GH_ParamAccess.item);

            pManager[1].Optional = true;
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddNumberParameter("Position", "pos", "The relative position along the element. 0 indicates the start node.", GH_ParamAccess.list);
            pManager.AddNumberParameter("AxialForce", "Nx", "Axial force", GH_ParamAccess.list);
            pManager.AddNumberParameter("ShearForceMinor", "Vy", "Shear force along weak axis", GH_ParamAccess.list);
            pManager.AddNumberParameter("ShearForceMajor", "Vz", "Shear force along strong axis", GH_ParamAccess.list);
            pManager.AddNumberParameter("Torsion", "T", "Torsion", GH_ParamAccess.list);
            pManager.AddNumberParameter("MomentMajor", "Myy", "Bending moment around the element y axis (strong bending)", GH_ParamAccess.list);
            pManager.AddNumberParameter("MomentMinor", "Mzz", "Bending moment around the element z axis (weak bending)", GH_ParamAccess.list);
            pManager.AddParameter(new UtilisationParam(), "Utilisation", "U", "Highest utilisation", GH_ParamAccess.list);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            // Indata
            ResultElement re = null;
            string name = null;
            if (!DA.GetData(0, ref re)) { return; }


            if (!DA.GetData(1, ref name))
            {
                 name = re.N1.First().Key;
            }

            DA.SetDataList(0, re.pos);
            DA.SetDataList(1, re.N1[name]);
            DA.SetDataList(2, re.Vy[name]);
            DA.SetDataList(3, re.Vz[name]);
            DA.SetDataList(4, re.T[name]);
            DA.SetDataList(5, re.My[name]);
            DA.SetDataList(6, re.Mz[name]);
            DA.SetDataList(7, re.util[name]);
        }
    }
}
