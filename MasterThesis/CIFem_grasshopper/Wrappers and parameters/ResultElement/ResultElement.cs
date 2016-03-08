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
        public Rhino.Geometry.Point3d sPos { get; private set; }
        public Rhino.Geometry.Point3d ePos { get; private set; }
        public Rhino.Geometry.Vector3d elNormal { get; private set; }

        public ResultElement()
        {
            
        }


        public ResultElement(WR_Element3d elem)
        {
            // Element data
            GetElementGeometricData(elem);

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

        private void GetElementGeometricData(WR_Element3d elem)
        {
            // Node positions
            sPos = CreateRhinoPt(elem.GetStartPos());
            ePos = CreateRhinoPt(elem.GetEndPos());

            // Orientation
            elNormal = CreateRhinoVector(elem.GetElementNormal());
        }

        /// <summary>
        /// Takes a WR_XYZ and creates a Rhino Point3d
        /// </summary>
        /// <param name="iPt"></param>
        /// <returns></returns>
        private Rhino.Geometry.Point3d CreateRhinoPt(WR_XYZ iPt)
        {
            double factor = Utilities.GetScalingFactorFromRhino();
            return new Rhino.Geometry.Point3d(iPt.X / factor, iPt.Y / factor, iPt.Z / factor);
        }


        /// <summary>
        /// Takes a WR_Vector and creates a Rhino Vector3d
        /// </summary>
        /// <param name="vec"></param>
        /// <returns></returns>
        private Rhino.Geometry.Vector3d CreateRhinoVector(WR_Vector vec)
        {
            double factor = Utilities.GetScalingFactorFromRhino();
            return new Rhino.Geometry.Vector3d(vec.X / factor, vec.Y / factor, vec.Z / factor);
        }

        public ResultElement Copy()
        {
            //TODO fix this
            return new ResultElement();
        }
    }
}
