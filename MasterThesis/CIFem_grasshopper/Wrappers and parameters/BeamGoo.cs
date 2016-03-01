using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper;
using Grasshopper.Kernel;

using CIFem_wrapper;
using Grasshopper.Kernel.Types;

namespace CIFem_grasshopper
{
    public class BeamGoo : Grasshopper.Kernel.Types.GH_Goo<WR_Elem3dRcp>
    {

        public BeamGoo()
        {
            this.Value = new WR_Elem3dRcp();
        }

        public BeamGoo(WR_Elem3dRcp value)
        {
            this.Value = value;
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
                return "3D beam element. Standard element used to build 3d frames";
            }
        }

        public override string TypeName
        {
            get
            {
                return "3d-Beam";
            }
        }

        public override IGH_Goo Duplicate()
        {
            return new BeamGoo(m_value.Copy());
        }

        public override string ToString()
        {
            return "Beam 3d element";
        }

        #region casting methods

        public override bool CastTo<Q>(ref Q target)
        {
            //Cast to WR_Elem3dRcp.
            if (typeof(Q).IsAssignableFrom(typeof(WR_Elem3dRcp)))
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

            //Cast from WR_Elem3dRcp
            if (typeof(WR_Elem3dRcp).IsAssignableFrom(source.GetType()))
            {
                Value = (WR_Elem3dRcp)source;
                return true;
            }

            return false;
        }

        #endregion
    }
}
