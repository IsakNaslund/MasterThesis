using CIFem_wrapper;
using Grasshopper.Kernel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CIFem_grasshopper
{
    public class ModeShapeOptimizerComponentRatio : GH_Component
    {
        private List<string> _log;
        private List<ResultElement> _resElems;

        public ModeShapeOptimizerComponentRatio(): base("Mode shape optimizer", "ModeSize", "Section sizer sizing elements based on mode shapes", "CIFem", "Optimizers")
        {
            _log = new List<string>();
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

            System.Diagnostics.Stopwatch watch = new System.Diagnostics.Stopwatch();


            if (!DA.GetData(0, ref structure)) { return; }
            if (!DA.GetData(1, ref go)) { return; }
            if (!DA.GetData(2, ref maxRatio)) { return; }


            if (go)
            {
                _resElems = new List<ResultElement>();
                _log.Clear();
                watch.Restart();

                // Solve
                WR_ModeShapeOptimizer optimizer = new WR_ModeShapeOptimizer(structure);

                watch.Stop();

                _log.Add(String.Format("Initialising: {0}ms", watch.ElapsedMilliseconds));

                watch.Restart();

                //Runs
                optimizer.Run(maxRatio);

                watch.Stop();

                _log.Add(String.Format("Run mode shape optimization: {0}ms", watch.ElapsedMilliseconds));

                watch.Restart();


                // Extract results
                List<WR_IElement> elems = structure.GetAllElements();
                for (int i = 0; i < elems.Count; i++)
                {

                    if (elems[i] is WR_Element3d)
                    {
                        WR_Element3d el3d = (WR_Element3d)elems[i];
                        ResultElement re = new ResultElement(el3d);
                        _resElems.Add(re);
                    }
                }

                watch.Stop();

                _log.Add(String.Format("Extract results: {0}ms", watch.ElapsedMilliseconds));

            }
            DA.SetDataList(0, _log);
            DA.SetDataList(1, _resElems);

        }
    }
}

