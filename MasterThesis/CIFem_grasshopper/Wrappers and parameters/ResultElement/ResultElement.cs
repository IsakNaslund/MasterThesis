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
        public Dictionary<string, List<double>> N1 { get; private set; }
        public Dictionary<string, List<double>> Vy { get; private set; }
        public Dictionary<string, List<double>> Vz { get; private set; }
        public Dictionary<string, List<double>> T { get; private set; }
        public Dictionary<string, List<double>> My { get; private set; }
        public Dictionary<string, List<double>> Mz { get; private set; }

        // Displacements
        public Dictionary<string, List<double>> u { get; private set; }
        public Dictionary<string, List<double>> v { get; private set; }
        public Dictionary<string, List<double>> w { get; private set; }
        public Dictionary<string, List<double>> fi { get; private set; }

        // Utilisations
        public Dictionary<string, List<WR_Utilisation>> util { get; private set; }

        // Element data
        public Rhino.Geometry.Point3d sPos { get; private set; }
        public Rhino.Geometry.Point3d ePos { get; private set; }
        public double Length { get; private set; }
        public Rhino.Geometry.Vector3d LocalX { get; private set; }
        public Rhino.Geometry.Vector3d LocalY { get; private set; }
        public Rhino.Geometry.Vector3d elNormal { get; private set; }   // Local z vector
        public String SectionPropertyString { get; set; }

        public ResultElement()
        {
            
        }


        public ResultElement(WR_Element3d elem)
        {
            // Element data
            GetElementGeometricData(elem);

            // Positions
            ScalePositionList(elem);

            // Forces
            GetForces(elem);

            // Displacements
            GetDisplacements(elem);

            // Utilisations
            GetUtilisations(elem);
        }


        private void ScalePositionList(WR_Element3d elem)
        {
            pos = new List<double>();

            List<double> unScaled = elem.ResultPosition();
            double sFac = 1 / Utilities.GetScalingFactorFromRhino();

            for (int i = 0; i < unScaled.Count; i++)
                pos.Add(unScaled[i] * sFac);

        }


        private void GetForces(WR_Element3d elem)
        {
            // Initialise dictionaries
            N1 = elem.AllNormalForce();
            Vy = elem.AllShearForceY();
            Vz = elem.AllShearForceZ();
            T = elem.AllTorsionalForce();
            My = elem.AllMomentY();
            Mz = elem.AllMomentZ();

        }


        private void GetDisplacements(WR_Element3d elem)
        {
            u = elem.AllDisplacementX();
            v = elem.AllDisplacementY();
            w = elem.AllDisplacementZ();
            fi = elem.AllDisplacementTorsion();
        }

        private void GetUtilisations(WR_Element3d elem)
        {
            util = elem.AllUtilisations();
        }



        private void GetElementGeometricData(WR_Element3d elem)
        {
            // Node positions
            sPos = CreateRhinoPt(elem.GetStartPos());
            ePos = CreateRhinoPt(elem.GetEndPos());
            Length = sPos.DistanceTo(ePos);

            // Orientation
            elNormal = CreateRhinoVector(elem.GetElementNormal(), false);
            SetLocalVectors();

            // Section property string
            SectionPropertyString = elem.GetSectionString();
        }

        

        private void SetLocalVectors()
        {
            var tempX = new Rhino.Geometry.Vector3d(ePos.X - sPos.X, ePos.Y - sPos.Y, ePos.Z - sPos.Z);
            tempX.Unitize();
            LocalX = tempX;


            LocalY = Rhino.Geometry.Vector3d.CrossProduct(elNormal, LocalX);
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


        
        public Rhino.Geometry.Point3d CreateRhinoPt(double pos)
        {
            return sPos + LocalX * pos;
        }


        /// <summary>
        /// Takes a WR_Vector and creates a Rhino Vector3d
        /// </summary>
        /// <param name="vec"></param>
        /// <param name="scaleToRhinoUnits"></param>
        /// <returns></returns>
        private Rhino.Geometry.Vector3d CreateRhinoVector(WR_Vector vec, bool scaleToRhinoUnits)
        {
            double factor = 1;
            if (scaleToRhinoUnits)
                factor = Utilities.GetScalingFactorFromRhino();

            return new Rhino.Geometry.Vector3d(vec.X / factor, vec.Y / factor, vec.Z / factor);
        }

        public ResultElement Copy()
        {
            //TODO fix this
            return new ResultElement();
        }
    }
}
