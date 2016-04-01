using CIFem_wrapper;
using Grasshopper.Kernel.Types;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CIFem_grasshopper
{
    public class CrossSectionGroupGoo : GH_Goo<WR_SectionGroup>
    {

        public CrossSectionGroupGoo()
        {
            Value = new WR_SectionGroup();
        }

        public CrossSectionGroupGoo(WR_SectionGroup secGroup)
        {
            if(secGroup==null)
                Value = new WR_SectionGroup();
            else
                Value = secGroup;
        }

        public override bool IsValid
        {
            get
            {
                if (Value == null)
                    return false;

                return true;
            }
        }

        public override string TypeDescription
        {
            get
            {
                return "A collection of cross sections to be used for optimisers";
            }
        }

        public override string TypeName
        {
            get
            {
                return "Cross section Group";
            }
        }

        public override IGH_Goo Duplicate()
        {
            //No real duplication done here.....
            return new CrossSectionGroupGoo(Value);
        }

        public override string ToString()
        {
            return "Cross Section";
        }

        #region casting methods

        public override bool CastTo<Q>(ref Q target)
        {
            //Cast to WR_SectionGroup.
            if (typeof(Q).IsAssignableFrom(typeof(WR_SectionGroup)))
            {
                if (Value == null)
                    target = default(Q);
                else
                    target = (Q)(object)Value;
                return true;
            }

            target = default(Q);
            return false;
        }



        public override bool CastFrom(object source)
        {
            if (source == null) { return false; }

            //Cast from WR_IXSec
            if (typeof(WR_SectionGroup).IsAssignableFrom(source.GetType()))
            {
                Value = (WR_SectionGroup)source;
                return true;
            }

            return false;
        }

        #endregion

    }
}