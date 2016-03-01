using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_wrapper;
using Grasshopper.Kernel.Types;

namespace CIFem_grasshopper
{
    public class BeamReleaseGoo : GH_Goo<WR_ReleaseBeam3d>
    {

        public BeamReleaseGoo()
        {
            this.Value = new WR_ReleaseBeam3d();
        }

        public BeamReleaseGoo(WR_ReleaseBeam3d value)
        {
            if (value == null)
                this.Value = new WR_ReleaseBeam3d();
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
                return "Constains information of how the beam is fixed at its end nodes";
            }
        }

        public override string TypeName
        {
            get
            {
                return "Beam release";
            }
        }

        public override IGH_Goo Duplicate()
        {
            return new BeamReleaseGoo(Value.Copy());
        }

        public override string ToString()
        {
            return Value.ToString();
        }

        #region casting methods

        public override bool CastTo<Q>(ref Q target)
        {
            //Cast to WR_ReleaseBeam3d.
            if (typeof(Q).IsAssignableFrom(typeof(WR_ReleaseBeam3d)))
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

            //Cast from WR_ReleaseBeam3d
            if (typeof(WR_ReleaseBeam3d).IsAssignableFrom(source.GetType()))
            {
                Value = (WR_ReleaseBeam3d)source;
                return true;
            }

            return false;
        }
        #endregion

    }

}
