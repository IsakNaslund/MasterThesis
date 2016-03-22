using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_wrapper;
using Grasshopper.Kernel.Types;

namespace CIFem_grasshopper
{
    public class StructureGoo : GH_Goo<WR_Structure>
    {
        public StructureGoo()
        {
            this.Value = new WR_Structure();
        }

        public StructureGoo(WR_Structure value)
        {
            if (value == null)
                this.Value = new WR_Structure();
            else
                this.Value = value;
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
                return "Strcture. Contains a set of elements conected";
            }
        }

        public override string TypeName
        {
            get
            {
                return "Strcture";
            }
        }

        public override IGH_Goo Duplicate()
        {
            //Shallow copy of the goo atm. Might need to fix this
            return new StructureGoo(Value);
        }

        public override string ToString()
        {
            return "Structure";
        }

        #region casting methods

        public override bool CastTo<Q>(ref Q target)
        {
            //Cast to WR_Structure.
            if (typeof(Q).IsAssignableFrom(typeof(WR_Structure)))
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

            //Cast from WR_Structure
            if (typeof(WR_Structure).IsAssignableFrom(source.GetType()))
            {
                Value = (WR_Structure)source;
                return true;
            }

            return false;
        }

        #endregion
    }
}