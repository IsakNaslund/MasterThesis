using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel.Types;
using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class CrossSectionGoo : GH_Goo<WR_IXSec>
    {

        public CrossSectionGoo()
        {
            Value = null;
        }

        public CrossSectionGoo(WR_IXSec xSec)
        {
            Value = xSec;
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
                return "A cross section";
            }
        }

        public override string TypeName
        {
            get
            {
                return "Cross section";
            }
        }

        public override IGH_Goo Duplicate()
        {
            return new CrossSectionGoo(Value);
        }

        public override string ToString()
        {
            return "Cross Section";
        }

        #region casting methods

        public override bool CastTo<Q>(ref Q target)
        {
            //Cast to WR_IXSec.
            if (typeof(Q).IsAssignableFrom(typeof(WR_IXSec)))
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
            if (typeof(WR_IXSec).IsAssignableFrom(source.GetType()))
            {
                Value = (WR_IXSec)source;
                return true;
            }


            //Cast from String
            if (typeof(string).IsAssignableFrom(source.GetType()))
            {
                WR_IXSec xSec;
                if (CrossSectionCasts.CrossSectionFormString((string)source, out xSec))
                {
                    Value = xSec;
                    return true;
                }
            }

            //Cast from GH_String
            if (typeof(GH_String).IsAssignableFrom(source.GetType()))
            {
                WR_IXSec xSec;
                if (CrossSectionCasts.CrossSectionFormString(((GH_String)source).Value, out xSec))
                {
                    Value = xSec;
                    return true;
                }
            }

            return false;
        }

        #endregion

    }
}