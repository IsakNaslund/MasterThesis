using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class ResultElement
    {
        // Positions
        public List<double> pos { get; private set; }

        // Forces
        public List<double> N1 { get; private set; }
        public List<double> Vy { get; private set; }
        public List<double> Vz { get; private set; }
        public List<double> T { get; private set; }
        public List<double> My { get; private set; }
        public List<double> Mz { get; private set; }

        // Displacements
        public List<double> u { get; private set; }
        public List<double> v { get; private set; }
        public List<double> w { get; private set; }
        public List<double> fi { get; private set; }

        // Element data
        public WR_XYZ sPos { get; private set; }
        public WR_XYZ ePos { get; private set; }

        public ResultElement()
        {
            
        }

        public ResultElement(WR_Element3d elem)
        {
            // Element data
            GetElementData(elem);

            // Positions
            pos = elem.ResultPosition();

            // Forces
            GetForces(elem);

            // Displacements
            GetDisplacements(elem);
        }


        private void GetForces(WR_Element3d elem)
        {
            N1 = elem.NormalForce();
            Vy = elem.ShearForceY();
            Vz = elem.ShearForceZ();
            T = elem.TorsionalForce();
            My = elem.MomentY();
            Mz = elem.MomentZ();
        }


        private void GetDisplacements(WR_Element3d elem)
        {
            u = elem.DisplacementX();
            v = elem.DisplacementY();
            w = elem.DisplacementZ();
            fi = elem.DisplacementTorsion();
        }

        private void GetElementData(WR_Element3d elem)
        {
            // Node positions
            //sPos = elem.
        }

        public ResultElement Copy()
        {
            //TODO fix this
            return new ResultElement();
        }
    }
}
