using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_wrapper;
using Grasshopper.Kernel.Types;

namespace CIFem_grasshopper
{
    public class LoadCombGoo : Grasshopper.Kernel.Types.GH_Goo<WR_LoadCombination>
    {

        public LoadCombGoo()
        {
            Value = null;
        }

        public LoadCombGoo(WR_LoadCombination comb)
        {
            Value = comb;
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
                return "A set of loads";
            }
        }

        public override string TypeName
        {
            get
            {
                return "Load Combination";
            }
        }

        public override IGH_Goo Duplicate()
        {
            return new LoadCombGoo(Value.Copy());
        }

        public override string ToString()
        {
            return "Load Combination";
        }

        #region casting methods

        public override bool CastTo<Q>(ref Q target)
        {
            //Cast to WR_LoadCombination.
            if (typeof(Q).IsAssignableFrom(typeof(WR_LoadCombination)))
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

            //Cast from WR_LoadCombination
            if (typeof(WR_LoadCombination).IsAssignableFrom(source.GetType()))
            {
                Value = (WR_LoadCombination)source;
                return true;
            }

            return false;
        }

        #endregion

    }
}
