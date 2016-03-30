using Grasshopper.Kernel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class StructurePropertiesComponent : GH_Component
    {
        public StructurePropertiesComponent() : base("Structure Properties", "SP", "Extract data fro astructure", "CIFem", "Structure")
        { }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("3da1f99f-bfad-4d78-8d74-040670d6a9a8");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new StructureParam(), "Structure", "S", "Structure to evaluate", GH_ParamAccess.item);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddNumberParameter("Weight", "W", "WEight of the structure", GH_ParamAccess.item);
            pManager.AddIntegerParameter("Node Count", "NC", "The number of nodes in the structure", GH_ParamAccess.item);
            pManager.AddIntegerParameter("Element Count", "EC", "The numberofelements in the structure", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            WR_Structure struc = null;

            if(!DA.GetData(0, ref struc)) { return; }

            DA.SetData(0, struc.GetWeight());
            DA.SetData(1, struc.NodeCount);
            DA.SetData(2, struc.ElementCount);
        }
    }
}
