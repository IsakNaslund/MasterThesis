using CIFem_wrapper;
using Grasshopper.Kernel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CIFem_grasshopper
{
    public class ModeShapeOptimizerComponent : GH_Component
    {
        public List<string> log { get; set; }
        private List<ResultElement> resElems { get; set; }

        public ModeShapeOptimizerComponent(): base("Mode shape optimizer", "ModeSize", "Section sizer sizing elements based on mode shapes", "CIFem", "Optimizers")
        {
            log = new List<string>();
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("68dcaaf3-817d-4cf0-b0da-386a3c0d20d4");
            }
        }


        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new StructureParam(), "Structure", "Str", "The structure to solve", GH_ParamAccess.item);
            pManager.AddBooleanParameter("Solve", "Go", "Toggle the solver", GH_ParamAccess.item);
            pManager.AddNumberParameter("Max Ratio", "R", "Maximum ratio of eigenvalue in relation to the first before break", GH_ParamAccess.item, 5);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            // Add displacements, reactions, element forces etc

            pManager.AddTextParameter("Messageboard", "log", "Outputs a log of the performed calculation", GH_ParamAccess.list);

            pManager.AddParameter(new ResultElementParam(), "Result Elements", "RE", "Result elements, storing results from the calculation", GH_ParamAccess.list);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            // Indata
            WR_Structure structure = null;
            bool go = false;
            double maxRatio = 0;

            if (!DA.GetData(0, ref structure)) { return; }
            if (!DA.GetData(1, ref go)) { return; }
            if (!DA.GetData(2, ref maxRatio)) { return; }


            if (go)
            {
                resElems = new List<ResultElement>();

                // Solve
                WR_ModeShapeOptimizer optimizer = new WR_ModeShapeOptimizer(structure);

                optimizer.Run(maxRatio);

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
            DA.SetDataList(0, log);
            DA.SetDataList(1, resElems);

        }
    }
}

