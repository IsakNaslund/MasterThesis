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
        public SectionGroupComponent(): base("Element Optimization Properties", "EOP", "Sets up properties for optimization proceduers", "CIFem", "Elements")
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
            pManager.AddBooleanParameter("Allow Rotation", "R", "Boolean to set if rotation of the section around its own axis should be alowed or not", GH_ParamAccess.item);
            pManager.AddIntegerParameter("Section Chooser Procedure", "SCP", "Choose wich method to use in sectionsizer. 0= check all, bottom up, 1= choose between one bigger and smaller, 2 = step up one", GH_ParamAccess.item, 0);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddParameter(new Element3dOptPropParameter(), "Optimization Properies", "OP", "Data used for optimization proceduers", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            List<WR_IXSec> crossSections = new List<WR_IXSec>();
            bool allowRotation = false;
            int sectionChangeType = 0;

            if(!DA.GetDataList(0, crossSections)) { return; }
            if(!DA.GetData(1, ref allowRotation)) { return; }
            if (!DA.GetData(2, ref sectionChangeType)) { return; }

            WR_Element3dOptProp optProp = new WR_Element3dOptProp(allowRotation, sectionChangeType);

            for (int i = 0; i < crossSections.Count; i++)
            {
                optProp.AddCrossSection(crossSections[i]);
            }

            DA.SetData(0, optProp);

        }
    }
}