using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;

using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class StructureConstructionComponent : GH_Component
    {

        public StructureConstructionComponent(): base("Structure", "Structure", "A structure to hold beams, releases, forces etc.", "CIFem", "Structure")
        {
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("5fbd562f-3209-43a3-a671-158404cb55b0");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new NodeParam(), "Restraint Nodes", "RN","A list of nodes that may contain restraints", GH_ParamAccess.list);

            pManager.AddParameter(new BeamParam(), "Beams", "B","Beams that the structure should consist of", GH_ParamAccess.list);

        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddParameter(new StructureParam(), "Structure", "S", "Constructed structure", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            // Indata
            List<WR_Node3d> nodes = new List<WR_Node3d>();
            List<WR_IElemRcp> beams = new List<WR_IElemRcp>();

            if (!DA.GetDataList(0, nodes)) { return; }
            if (!DA.GetDataList(1, beams)) { return; }


            // Create structure wrapper
            WR_Structure structure = new WR_Structure();

            // Add restraint nodes
            foreach (WR_Node3d n in nodes)
                structure.AddNode(n);

            // Add elements
            foreach (WR_Elem3dRcp e in beams)
                structure.AddElementRcp(e);

            DA.SetData(0, structure);
        }
    }
}
