using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_wrapper;

namespace CS_Sandbox
{
    class Program
    {
        static void Main(string[] args)
        {
            WR_Structure structure = new WR_Structure();
         
            WR_XSecRect rect = new WR_XSecRect(0.1, 0.1);
            
            WR_ReleaseBeam3d rel = new WR_ReleaseBeam3d(true, true, true, true, true, true);

            WR_XYZ x1 = new WR_XYZ(0, 0, 0);
            WR_XYZ x2 = new WR_XYZ(0, 1, 0);
            WR_XYZ x3 = new WR_XYZ(1, 1, 0);
            WR_XYZ x4 = new WR_XYZ(1, 0, 0);

            WR_Elem3dRcp rcp1 = new WR_Elem3dRcp(x1, x2,rel,rel,rect,210000000000,0.1,new WR_Vector(0,1,0));
            WR_Elem3dRcp rcp2 = new WR_Elem3dRcp(x2, x3, rel, rel, rect, 210000000000, 0.1, new WR_Vector(0, 1, 0));
            WR_Elem3dRcp rcp3 = new WR_Elem3dRcp(x3, x4, rel, rel, rect, 210000000000, 0.1, new WR_Vector(0, 1, 0));

            WR_Node3d n1 = new WR_Node3d(0, 0, 0);
            WR_Node3d n2 = new WR_Node3d(0, 1, 0);
            WR_Node3d n3 = new WR_Node3d(1, 1, 0);
            WR_Node3d n4 = new WR_Node3d(1, 0, 0);


            structure.AddNode(n1);
            structure.AddNode(n2);
            structure.AddNode(n3);
            structure.AddNode(n4);

            structure.AddElementRcp(rcp1);
            structure.AddElementRcp(rcp2);
            structure.AddElementRcp(rcp3);
            
            structure.Solve();

        }
    }
}
