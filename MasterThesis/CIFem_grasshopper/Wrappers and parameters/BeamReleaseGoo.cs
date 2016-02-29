using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_wrapper;
using Grasshopper.Kernel.Types;

namespace CIFem_grasshopper
{
    public class BeamReleaseGoo : Grasshopper.Kernel.Types.GH_Goo<WR_ReleaseBeam3d>
    {


        public BeamReleaseGoo()
        {
            m_value = new WR_ReleaseBeam3d();
        }

        public BeamReleaseGoo(WR_ReleaseBeam3d value)
        {
            m_value = value;
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
    }
}
