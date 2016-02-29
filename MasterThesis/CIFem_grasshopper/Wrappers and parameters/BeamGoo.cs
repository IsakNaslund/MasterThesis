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
            this.m_value = new WR_Elem3dRcp();
        }

        public BeamGoo(WR_Elem3dRcp value)
        {
            this.m_value = value;
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
    }
}
