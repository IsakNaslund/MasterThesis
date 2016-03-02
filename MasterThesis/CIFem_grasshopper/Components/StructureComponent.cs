using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;

using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class StructureComponent : GH_Component
    {
        public List<string> log { get; set; }

        public StructureComponent(): base("Structure", "Structure", "A structure to hold beams, releases, forces etc.", "CIFem", "Structure")
        {
            log = new List<string>();
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("feed2e3f-eea8-498b-8b78-10223628593a");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(
                new BeamParam(), "Beams", "B", "Beams that the structure should consist of", GH_ParamAccess.list);

            // Woops, should be restraints!
            //pManager.AddParameter(
            //    new BeamReleaseParameter(), "Releases", "R", "Releases for the structure", GH_ParamAccess.list);

            pManager.AddBooleanParameter("Solve", "Go", "Toggle the solver", GH_ParamAccess.item);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            // Add displacements, reactions, element forces etc

            pManager.AddTextParameter(
                "Messageboard", "log", "Outputs a log of the performed calculation", GH_ParamAccess.list);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            bool go = false;
            List<WR_IElemRcp> beams = null;

            if (!DA.GetData(0, ref beams)) { return; }
            if (!DA.GetData(1, ref go)) { return; }

            if (go)
            {
                log.Clear();
                log.Add("Structure invokation started");

                // Create structure wrapper
                WR_Structure structure = new WR_Structure();

                // Add restraints
                for (int i = 0; i < beams.Count; i++)
                {
                //    structure.AddElementRcp(beams[i].)
                }

                // Add elements

                // Add forces

                // Solve
            }

            DA.SetData(0, log);
        }
    }
}
