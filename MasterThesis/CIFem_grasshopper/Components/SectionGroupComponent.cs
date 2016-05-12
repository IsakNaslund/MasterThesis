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
            pManager.AddIntegerParameter("Section Chooser Procedure", "SCP", "Choose wich method to use in sectionsizer." +
                " \n 0= check all, bottom up. Allways checks smallest to largest\n 1 = Step to one larger when overutilized \n 2= Sted up if overutilized, down if underutilized. \n 3 = Search all from current ", GH_ParamAccess.item, 0);
            pManager.AddNumberParameter("Minimum Utilization", "minU", "The minimum utilization allowed before the elementis set to converged in optimization", GH_ParamAccess.item, 0.8);
            pManager.AddNumberParameter("Maximum Utilization", "maxU", "The maximum utilization allowed before the elementis set to converged in optimization", GH_ParamAccess.item, 1);
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
            double minUtil = 0;
            double maxUtil = 1;

            if(!DA.GetDataList(0, crossSections)) { return; }
            if(!DA.GetData(1, ref allowRotation)) { return; }
            if (!DA.GetData(2, ref sectionChangeType)) { return; }
            if (!DA.GetData(3, ref minUtil)) { return; }
            if (!DA.GetData(4, ref maxUtil)) { return; }

            WR_Element3dOptProp optProp = new WR_Element3dOptProp(allowRotation, sectionChangeType, minUtil,maxUtil);

            for (int i = 0; i < crossSections.Count; i++)
            {
                optProp.AddCrossSection(crossSections[i]);
            }

            DA.SetData(0, optProp);

        }
    }
}