using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;

using CIFem_wrapper;


namespace CIFem_grasshopper
{
    public class LinearSolverComponent : GH_Component
    {
        public List<string> log { get; set; }
        private List<ResultElement> resElems { get; set; }

        public LinearSolverComponent(): base("Linear Solver", "LinSlv", "A Linear solver of a structure", "CIFem", "Solvers")
        {
            log = new List<string>();
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("bf48f1f2-9cb8-4532-95f5-5cb8150c6e22");
            }
        }


        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new StructureParam(), "Structure", "Str", "The structure to solve", GH_ParamAccess.item);
            pManager.AddParameter(new LoadCombParameter(), "Load Combinations", "LC", "Diffrent loadcombinations for the structure", GH_ParamAccess.list);
            pManager.AddBooleanParameter("Solve", "Go", "Toggle the solver", GH_ParamAccess.item);
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
            List<WR_LoadCombination> loadCombinations = new List<WR_LoadCombination>();
            bool go = false;

            if (!DA.GetData(0, ref structure)) { return; }
            if (!DA.GetDataList(1, loadCombinations)) { return; }
            if (!DA.GetData(2, ref go)) { return; }

            if (go)
            {
                resElems = new List<ResultElement>();

                // Solve
                WR_LinearSolver solver = new WR_LinearSolver(structure);

                foreach (WR_LoadCombination lc in loadCombinations)
                {
                    solver.AddLoadCombination(lc);
                }

                // Check structure
                solver.CheckStructure();
                if (!structure.IsValidForLinearSolver())
                    return;

                // Solve
                try
                {
                    solver.Solve();
                }
                catch (Exception e)
                {
                    AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
                    return;
                }


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
