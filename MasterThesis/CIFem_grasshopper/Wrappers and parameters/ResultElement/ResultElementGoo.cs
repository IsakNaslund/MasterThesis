using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper;
using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

namespace CIFem_grasshopper
{
    public class ResultElementGoo : Grasshopper.Kernel.Types.GH_Goo<ResultElement>
    {
        public ResultElementGoo()
        {
            Value = new ResultElement();
        }

        public ResultElementGoo(ResultElement re)
        {
            if (re == null)
            {
                Value = new ResultElement();
            }
            else
                Value = re;
        }

        public override bool IsValid
        {
            get
            {
                //TODO inplement some kind of check to see if all wrappers work etc
                if (Value == null)
                    return false;

                return true;
            }
        }

        public override string TypeDescription
        {
            get
            {
                return "Result storage for a 3d element";
            }
        }

        public override string TypeName
        {
            get
            {
                return "Result Element";
            }
        }

        public override IGH_Goo Duplicate()
        {
            return new ResultElementGoo(Value.Copy());
        }

        public override string ToString()
        {
            return "Result Element";
        }


        #region casting methods

        public override bool CastTo<Q>(ref Q target)
        {
            //Cast to ResultElement.
            if (typeof(Q).IsAssignableFrom(typeof(ResultElement)))
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

            //Cast from ResultElement
            if (typeof(ResultElement).IsAssignableFrom(source.GetType()))
            {
                Value = (ResultElement)source;
                return true;
            }

            return false;
        }

        #endregion
    }
}

