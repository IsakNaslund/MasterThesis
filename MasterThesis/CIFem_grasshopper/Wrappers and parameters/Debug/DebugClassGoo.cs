using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel.Types;


namespace CIFem_grasshopper.Debug
{
    public class DebugClassGoo : GH_Goo<CIFem_wrapper.WR_DebugClass>
    {
        public DebugClassGoo()
        {
            Value = null;
        }

        public DebugClassGoo(CIFem_wrapper.WR_DebugClass dc)
        {
            Value = dc;
        }

        public override bool IsValid
        {
            get
            {
                if (Value == null)
                    return false;

                else
                    return true;
            }
        }

        public override string TypeDescription
        {
            get
            {
                return "A class solely for debug purposes";
            }
        }

        public override string TypeName
        {
            get
            {
                return "Debug Class Goo";
            }
        }

        public override IGH_Goo Duplicate()
        {
            throw new NotImplementedException();
        }

        public override string ToString()
        {
            return TypeDescription;
        }



        #region casting methods

        public override bool CastTo<Q>(ref Q target)
        {
            //Cast to CIFem_wrapper.WR_DebugClass.
            if (typeof(Q).IsAssignableFrom(typeof(CIFem_wrapper.WR_DebugClass)))
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

            //Cast from CIFem_wrapper.WR_DebugClass
            if (typeof(CIFem_wrapper.WR_DebugClass).IsAssignableFrom(source.GetType()))
            {
                Value = (CIFem_wrapper.WR_DebugClass)source;
                return true;
            }

            return false;
        }

        #endregion
    }
}
