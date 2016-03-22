using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;

using CIFem_wrapper;



namespace CIFem_grasshopper
{
    public class EigSolverComponent : GH_Component
    {
        public List<string> log { get; set; }
        private List<ResultElement> resElems { get; set; }
        private WR_EigenSolver _solver;
        double _eigVal;

        public EigSolverComponent(): base("Eigen Solver", "EigSlv", "A eigenmode solver of a structure", "CIFem", "Solvers")
        {
            log = new List<string>();
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("07fc970c-ab42-4384-bc0d-dbcb254e64a4");
            }
        }


        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new StructureParam(), "Structure", "Str", "The structure to solve", GH_ParamAccess.item);
            pManager.AddIntegerParameter("Mode", "m", "The mode to evaluate", GH_ParamAccess.item);
            pManager.AddBooleanParameter("Solve", "Go", "Toggle the solver", GH_ParamAccess.item);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            // Add displacements, reactions, element forces etc

            pManager.AddTextParameter("Messageboard", "log", "Outputs a log of the performed calculation", GH_ParamAccess.list);
            pManager.AddParameter(new ResultElementParam(), "Result Elements", "RE", "Result elements, storing results from the calculation", GH_ParamAccess.list);
            pManager.AddNumberParameter("EigVal", "EV", "The eigenvalue of choosen mode", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            // Indata
            bool go = false;
            WR_Structure structure = null;
            int mode = 0;

            if (!DA.GetData(0, ref structure)) { return; }
            if (!DA.GetData(1, ref mode)) { return; }
            if (!DA.GetData(2, ref go)) { return; }

            if (go)
            {
                resElems = new List<ResultElement>();

                // Solve
                _solver = new WR_EigenSolver(structure);
                _solver.Solve();
            }

            if (_solver != null && structure != null)
            {
                _eigVal = _solver.SetResultsToMode(mode);

                // Extract results
                List<WR_IElement> elems = structure.GetAllElements();
                resElems.Clear();

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
            DA.SetData(2, _eigVal);

        }
    }
}
