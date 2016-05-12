using CIFem_wrapper;
using Grasshopper.Kernel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CIFem_grasshopper
{
    public class CombinedSectionSizerComponent : GH_Component
    {
        public List<string> _log;
        private List<ResultElement> _resElems;
        private int _iterations;

        public CombinedSectionSizerComponent(): base("Combined optimizer", "CombSize", "Section sizer sizing elements based on mode shapes as initial input", "CIFem", "Optimizers")
        {
            _log = new List<string>();
            _iterations = 0;
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("1525c98c-0c8f-49bc-9ce0-7ce21d09a702");
            }
        }


        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new StructureParam(), "Structure", "Str", "The structure to solve", GH_ParamAccess.item);
            pManager.AddParameter(new LoadCombParameter(), "Load Combinations", "LC", "Diffrent loadcombinations for the structure", GH_ParamAccess.list);
            pManager.AddBooleanParameter("Solve", "Go", "Toggle the solver", GH_ParamAccess.item);
            pManager.AddIntegerParameter("Modes", "m", "The modes to optimize for", GH_ParamAccess.list);
            pManager.AddIntegerParameter("Max Iterations", "MI", "Maximum iterations to run before brake", GH_ParamAccess.item, 100);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            // Add displacements, reactions, element forces etc

            pManager.AddTextParameter("Messageboard", "log", "Outputs a log of the performed calculation", GH_ParamAccess.list);

            pManager.AddParameter(new ResultElementParam(), "Result Elements", "RE", "Result elements, storing results from the calculation", GH_ParamAccess.list);
            pManager.AddIntegerParameter("I", "Iterations", "Number of iterations ran", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            // Indata
            WR_Structure structure = null;
            List<WR_LoadCombination> loadCombinations = new List<WR_LoadCombination>();
            bool go = false;
            List<int> modes = new List<int>();
            int maxIterations = 0;

            System.Diagnostics.Stopwatch watch = new System.Diagnostics.Stopwatch();


            if (!DA.GetData(0, ref structure)) { return; }
            if (!DA.GetDataList(1, loadCombinations)) { return; }
            if (!DA.GetData(2, ref go)) { return; }
            if (!DA.GetDataList(3, modes)) { return; }
            if (!DA.GetData(4, ref maxIterations)) { return; }


            if (go)
            {

                _resElems = new List<ResultElement>();
                _log.Clear();
                watch.Restart();



                // Solve
                WR_CombinedSectionSizer optimizer = new WR_CombinedSectionSizer(structure);


                foreach (WR_LoadCombination lc in loadCombinations)
                {
                    optimizer.AddLoadCombination(lc);
                }




                watch.Stop();

                _log.Add(String.Format("Initialising: {0}ms", watch.ElapsedMilliseconds));

                watch.Restart();


                //Run
                _iterations = optimizer.Run(modes, maxIterations);


                watch.Stop();

                _log.Add(String.Format("Run mode shape optimization and section sizer: {0}ms", watch.ElapsedMilliseconds));

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
            DA.SetData(2, _iterations);

        }
    }
}