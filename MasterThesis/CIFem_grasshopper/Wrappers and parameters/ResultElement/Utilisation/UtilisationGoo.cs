using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_wrapper;
using Grasshopper.Kernel.Types;

namespace CIFem_grasshopper
{
    public class UtilisationGoo : Grasshopper.Kernel.Types.GH_Goo<WR_Utilisation>
    {
        public UtilisationGoo()
        {
            Value = new WR_Utilisation();
        }


        public UtilisationGoo(WR_Utilisation util)
        {
            if (util == null)
                Value = new WR_Utilisation();
            else
                Value = util;
        }

        public override bool IsValid
        {
            get
            {
                //TODO: More Checks!

                if (Value == null)
                    return false;

                return true;
            }
        }

        public override string TypeDescription
        {
            get
            {
                return "A utilisation property";
            }
        }

        public override string TypeName
        {
            get
            {
                return "Material";
            }
        }

        public override IGH_Goo Duplicate()
        {
            if (Value == null)
                return new UtilisationGoo();

            return new UtilisationGoo(Value.Copy());
        }

        public override string ToString()
        {
            return Value.ToString();
        }




        #region casting methods

        public override bool CastTo<Q>(ref Q target)
        {
            //Cast to WR_Utilisation.
            if (typeof(Q).IsAssignableFrom(typeof(WR_Utilisation)))
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

            //Cast from WR_Utilisation
            if (typeof(WR_Utilisation).IsAssignableFrom(source.GetType()))
            {
                Value = (WR_Utilisation)source;
                return true;
            }

            return false;
        }

        #endregion
    }
}
