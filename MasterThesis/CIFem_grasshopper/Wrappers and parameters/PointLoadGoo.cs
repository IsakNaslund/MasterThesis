using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;
using Grasshopper.Kernel.Types;

namespace CIFem_grasshopper
{
    public class PointLoadGoo : GH_Goo<PointLoadCarrier>
    {

        public PointLoadGoo()
        {
            Value = new PointLoadCarrier();
        }

        public PointLoadGoo(PointLoadCarrier pl)
        {
            if (pl == null)
                Value = new PointLoadCarrier();
            else
                Value = pl;
        }

        public override bool IsValid
        {
            get
            {
                if (Value == null)
                    return false;

                if (!Value.IsValid)
                    return false;

                return true;
            }
        }

        public override string TypeDescription
        {
            get
            {
                return "Point Load";
            }
        }

        public override string TypeName
        {
            get
            {
                return "Point Load";
            }
        }

        public override IGH_Goo Duplicate()
        {
            return new PointLoadGoo(new PointLoadCarrier(Value.Pos, Value.Force, Value.Moment));
        }

        public override string ToString()
        {
            return "Point Load";
        }


        #region casting methods

        public override bool CastTo<Q>(ref Q target)
        {
            //Cast to PointLoadCarrier.
            if (typeof(Q).IsAssignableFrom(typeof(PointLoadCarrier)))
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

            //Cast from PointLoadCarrier
            if (typeof(PointLoadCarrier).IsAssignableFrom(source.GetType()))
            {
                Value = (PointLoadCarrier)source;
                return true;
            }

            return false;
        }

        #endregion
    }
}
