using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Rhino;
using CIFem_wrapper;
using Rhino.Geometry;
using CIFem_grasshopper;

namespace CIFem_grasshopper
{
    static class Utilities
    {
        /// <summary>
        /// When reading inputs - Multiply with the factor 
        /// When writing outputs - Divide with the factor
        /// </summary>
        /// <returns></returns>
        public static double GetScalingFactorFromRhino()
        {
            double factor = 1;

            switch (RhinoDoc.ActiveDoc.ModelUnitSystem)
            {
                case UnitSystem.None:
                    break;
                case UnitSystem.Angstroms:
                    break;
                case UnitSystem.Nanometers:
                    break;
                case UnitSystem.Microns:
                    break;
                case UnitSystem.Millimeters:
                    factor = 0.001;
                    break;
                case UnitSystem.Centimeters:
                    factor = 0.01;
                    break;
                case UnitSystem.Decimeters:
                    factor = 0.1;
                    break;
                case UnitSystem.Meters:
                    break;
                case UnitSystem.Dekameters:
                    break;
                case UnitSystem.Hectometers:
                    break;
                case UnitSystem.Kilometers:
                    break;
                case UnitSystem.Megameters:
                    break;
                case UnitSystem.Gigameters:
                    break;
                case UnitSystem.Microinches:
                    break;
                case UnitSystem.Mils:
                    break;
                case UnitSystem.Inches:
                    break;
                case UnitSystem.Feet:
                    break;
                case UnitSystem.Yards:
                    break;
                case UnitSystem.Miles:
                    break;
                case UnitSystem.PrinterPoint:
                    break;
                case UnitSystem.PrinterPica:
                    break;
                case UnitSystem.NauticalMile:
                    break;
                case UnitSystem.Astronomical:
                    break;
                case UnitSystem.Lightyears:
                    break;
                case UnitSystem.Parsecs:
                    break;
                case UnitSystem.CustomUnitSystem:
                    break;
                default:
                    break;
            }

            return factor;
        }

        public static Point3d ConvertToRhinoPoint(this WR_XYZ wrPt)
        {
            return new Point3d(wrPt.X, wrPt.Y, wrPt.Z);
        }

        public static WR_XYZ ConvertToWrapperPoint(this Point3d rPt)
        {
            return new WR_XYZ(rPt.X, rPt.Y, rPt.Z);
        }

        static public List<List<Brep>> CreateSectionSweeps(List<WR_Elem3dRcp> elemsRcp)
        {
            List<List<Brep>> sBreps = new List<List<Brep>>();

            foreach (WR_Elem3dRcp er in elemsRcp)
            {
                List<Curve> crvs;
                List<Brep> eSBreps = new List<Brep>();

                // Start and end caps
                List<Curve> sCap = new List<Curve>();
                List<Curve> eCap = new List<Curve>();

                if (CrossSectionCasts.GetSectionPropertyCrvs(er.GetSectionString(), out crvs))
                {
                    // Get x vector
                    WR_XYZ sPos = er.GetStartPos();
                    WR_XYZ ePos = er.GetEndPos();
                    Vector3d elX = new Vector3d(ePos.X - sPos.X, ePos.Y - sPos.Y, ePos.Z - sPos.Z);

                    // Get normal (z vector)
                    WR_Vector elWrZ = er.GetElementNormal();
                    Vector3d elZ = new Vector3d(elWrZ.X, elWrZ.Y, elWrZ.Z);

                    // Get y vector
                    Vector3d elY = Vector3d.CrossProduct(elZ, elX);

                    // Rotation to local coordinates
                    Transform rotTrans = Transform.Rotation(Vector3d.XAxis, Vector3d.YAxis, Vector3d.ZAxis, elX, elY, elZ);

                    // Add start and end point to a list
                    List<Point3d> endPts = new List<Point3d> { new Point3d(sPos.X, sPos.Y, sPos.Z), new Point3d(sPos.X, sPos.Y, sPos.Z) };

                    foreach (Curve crv in crvs)
                    {
                        // Rotate to local coordinates
                        crv.Transform(rotTrans);

                        // Create and add extrusion
                        Brep extrusion = Extrusion.CreateExtrusion(crv, elX).ToBrep();
                        eSBreps.Add(extrusion);

                        // Add curve to cap list
                        sCap.Add(crv);

                        Curve eCrv = (Curve)crv.Duplicate();
                        eCrv.Translate(elX);
                    }

                    // Cap sections
                    eSBreps.Add(CapSections(sCap));

                    // Add breps to list of list of breps
                    sBreps.Add(eSBreps);
                }
            }

            return sBreps;
        }


        /// <summary>
        /// Caps planar curves
        /// </summary>
        /// <param name="capCrvs">A list of planar curves (can be one or several) to cap</param>
        /// <returns>A brep</returns>
        static public Brep CapSections(List<Curve> capCrvs)
        {
            Brep cap = new Brep();

            // For one curve, i.e. solid sections
            if (capCrvs.Count == 1)
                cap = Brep.CreatePlanarBreps(capCrvs[0])[0];

            // For two curves, i.e. hollow sections
            else if (capCrvs.Count == 2)
                cap = Brep.CreatePlanarBreps(capCrvs)[0];

            // Error handling (for development)
            else
                throw new NotImplementedException("Capping of sections consisting of other than 1 or 2 curves not implemented.");

            return cap;
        }
    }
}