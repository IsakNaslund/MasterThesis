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
        private int pos { get; set; }

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
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddIntegerParameter("Position", "pos", "The relative position along the element. 0 indicates the start node.", GH_ParamAccess.list);
            pManager.AddNumberParameter("AxialForce", "Nx", "Axial force", GH_ParamAccess.list);
            pManager.AddNumberParameter("ShearForceMinor", "Vy", "Shear force along weak axis", GH_ParamAccess.list);
            pManager.AddNumberParameter("ShearForceMajor", "Vz", "Shear force along strong axis", GH_ParamAccess.list);
            pManager.AddNumberParameter("Torsion", "T", "Torsion", GH_ParamAccess.list);
            pManager.AddNumberParameter("MomentMajor", "Myy", "Bending moment around the element y axis (strong bending)", GH_ParamAccess.list);
            pManager.AddNumberParameter("MomentMinor", "Mzz", "Bending moment around the element z axis (weak bending)", GH_ParamAccess.list);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            // Indata
            ResultElement re = null;
            if (!DA.GetData(0, ref re)) { return; }

            DA.SetDataList(0, re.pos);
            DA.SetDataList(1, re.N1);
            DA.SetDataList(2, re.Vy);
            DA.SetDataList(3, re.Vz);
            DA.SetDataList(4, re.T);
            DA.SetDataList(5, re.My);
            DA.SetDataList(6, re.Mz);
        }
    }
}
