using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;

using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class StructureComponentEigen : GH_Component
    {
        public List<string> log { get; set; }
        private List<ResultElement> resElems { get; set; }

        public StructureComponentEigen(): base("Structure Eigen", "Structure Eig", "A structure to hold beams, releases, forces etc. Solves for eigenvalues", "CIFem", "Structure")
        {
            log = new List<string>();
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("57194535-5b02-424a-b0e0-3e6cb81fd0c4");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new NodeParam(), "Restraint Nodes", "RN",
                "A list of nodes that may contain restraints", GH_ParamAccess.list);

            pManager.AddParameter(new BeamParam(), "Beams", "B", 
                "Beams that the structure should consist of", GH_ParamAccess.list);

            // Woops, should be restraints!
            //pManager.AddParameter(
            //    new BeamReleaseParameter(), "Releases", "R", "Releases for the structure", GH_ParamAccess.list);

            pManager.AddIntegerParameter("Mode", "m", "The mode to evaluate", GH_ParamAccess.item);
            pManager.AddBooleanParameter("Solve", "Go", "Toggle the solver", GH_ParamAccess.item);


        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            // Add displacements, reactions, element forces etc

            pManager.AddTextParameter(
                "Messageboard", "log", "Outputs a log of the performed calculation", GH_ParamAccess.list);

            pManager.AddParameter(new ResultElementParam(), "Result Elements", "RE", "Result elements, storing results from the calculation", GH_ParamAccess.list);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            // Indata
            bool go = false;
            List<WR_Node3d> nodes = new List<WR_Node3d>();
            List<WR_IElemRcp> beams = new List<WR_IElemRcp>();
            int mode = 0;

            if (!DA.GetDataList(0, nodes)) { return; }
            if (!DA.GetDataList(1, beams)) { return; }
            if (!DA.GetData(2, ref mode)) { return; }
            if (!DA.GetData(3, ref go)) { return; }

            if (go)
            {
                resElems = new List<ResultElement>();

                log.Clear();
                log.Add("Structure invokation started");

                // Create structure wrapper
                WR_Structure structure = new WR_Structure();

                // Add restraint nodes
                foreach (WR_Node3d n in nodes)
                    structure.AddNode(n);
                log.Add("" + nodes.Count + " nodes added to structure");

                // Add elements
                foreach (WR_Elem3dRcp e in beams)
                    structure.AddElementRcp(e);
                log.Add("" + beams.Count + " elements added to structure");

                // Add forces

                // Solve
                structure.EigenSolve(mode);

                // Extract results
                List<WR_IElement> elems = structure.GetAllElements();
                for (int i = 0; i < elems.Count; i++)
                {

                    if (elems[i] is WR_Element3d)
                    {
                        WR_Element3d el3d = (WR_Element3d)elems[i];
                        ResultElement re = new ResultElement(el3d);
                        resElems.Add(re);
                    }
                }
            }

            DA.SetData(0, log);
            DA.SetDataList(1, resElems);
        }
    }
}
