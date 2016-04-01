using Grasshopper.Kernel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_wrapper;

namespace CIFem_grasshopper.Components
{
    public class SectionGroupComponent : GH_Component
    {
        public SectionGroupComponent(): base("Section Group", "SG", "A group of sections to be used for optimisation for beams", "CIFem", "Elements")
        { }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("16f4869e-49ed-447a-a9cc-9ac6a8838d9d");
            }
        }

        public override GH_Exposure Exposure
        {
            get
            {
                return GH_Exposure.tertiary;
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new CrossSectionParameter(), "Cross Sections", "XS", "Cross sections to group. Used in optimisations procedures", GH_ParamAccess.list);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddParameter(new CrossSectionGroupParameter(), "Cross Section Group", "XSG", "Cross section group constructed. Used in optimisations procedures", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            List<WR_IXSec> crossSections = new List<WR_IXSec>();

            if(!DA.GetDataList(0, crossSections)) { return; }

            WR_SectionGroup group = new WR_SectionGroup();

            for (int i = 0; i < crossSections.Count; i++)
            {
                group.AddCrossSection(crossSections[i]);
            }

            DA.SetData(0, group);

        }
    }
}