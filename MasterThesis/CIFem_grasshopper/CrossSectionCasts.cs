using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_wrapper;
using Rhino.Geometry;

namespace CIFem_grasshopper
{
    internal static class CrossSectionCasts
    {
        internal enum CrossSectionType
        {
            RectangularSolid = 140000,
            RHS,
            CircularSolid,
            CHS,
        }


        internal static CrossSectionType CrossSectionTypeFromString(string section)
        {
            if (section.ToUpper().StartsWith("REC"))
            {
                return CrossSectionType.RectangularSolid;
            }
            else if (section.ToUpper().StartsWith("RHS"))
            {
                return CrossSectionType.RHS;
            }

            throw new NotImplementedException();
        }

        static internal bool CrossSectionFormString(string section, out WR_IXSec xSec)
        {
            CrossSectionType cst = CrossSectionTypeFromString(section);

            switch (cst)
            {
                case CrossSectionType.RectangularSolid:
                    return RectangularCrossSection(section, out xSec);

                case CrossSectionType.RHS:
                    return RHSCrossSection(section, out xSec);

                case CrossSectionType.CircularSolid:
                case CrossSectionType.CHS:
                default:
                    {
                        xSec = null;
                        return false;
                    }
            }
        }

        static private bool RHSCrossSection(string section, out WR_IXSec xSec)
        {
            double height, width, thickness;

            if (!GetDimensionsRHS(section, out height, out width, out thickness))
            {
                xSec = null;
                return false;
            }

            double factor = Utilities.GetScalingFactorFromRhino();
            height *= factor;
            width *= factor;
            thickness *= factor;

            xSec = new WR_XSecRHS(height, width, thickness);
            return true;
        }

        static private bool RectangularCrossSection(string section, out WR_IXSec xSec)
        {
            double height, width;

            if (!GetDimensionsRectangle(section, out height, out width))
            {
                xSec = null;
                return false;
            }

            double factor = Utilities.GetScalingFactorFromRhino();

            height *= factor;
            width *= factor;

            xSec = new WR_XSecRect(height, width);
            return true;

        }


        static private bool GetDimensionsRectangle(string section, out double height, out double width)
        {
            height = -1;
            width = -1;

            List<string> numbers = System.Text.RegularExpressions.Regex.Split(section, @"[^0-9\.]+").Where(c => c != "." && c.Trim() != "").ToList();
            
            if (numbers.Count < 2 || !double.TryParse(numbers[0], out height) || !double.TryParse(numbers[1], out width))
                return false;

            return true;
        }

        
        static private bool GetDimensionsRHS(string section, out double height, out double width, out double thickness)
        {
            height = -1;
            width = -1;
            thickness = -1;

            string[] numbers = System.Text.RegularExpressions.Regex.Split(section, @"\D+");

            if (numbers.Length < 4 || !double.TryParse(numbers[1], out height) || !double.TryParse(numbers[2], out width) || !double.TryParse(numbers[3], out thickness))
                return false;

            return true;
        }
        

        static internal bool GetSectionPropertyCrvs(string section, out List<Curve> crvs)
        {
            CrossSectionType cst = CrossSectionTypeFromString(section);

            switch (cst)
            {
                case CrossSectionType.RectangularSolid:
                    return GetRectangleCurve(section, out crvs);

                case CrossSectionType.RHS:
                    return GetRHSCurve(section, out crvs);

                case CrossSectionType.CircularSolid:
                case CrossSectionType.CHS:
                default:
                    break;
            }

            // If fails
            crvs = null;
            return false;
        }

        static private bool GetRectangleCurve(string section, out List<Curve> crvs)
        {
            crvs = new List<Curve>();
            double height, width;

            if (!GetDimensionsRectangle(section, out height, out width))
                return false;

            height /= Utilities.GetScalingFactorFromRhino();
            width /= Utilities.GetScalingFactorFromRhino();

            List<Point3d> pts = new List<Point3d>();
            pts.Add((Point3d)(Vector3d.ZAxis * height / 2 + Vector3d.YAxis * width / 2));
            pts.Add((Point3d)(Vector3d.ZAxis * height / 2 - Vector3d.YAxis * width / 2));
            pts.Add((Point3d)(-Vector3d.ZAxis * height / 2 - Vector3d.YAxis * width / 2));
            pts.Add((Point3d)(-Vector3d.ZAxis * height / 2 + Vector3d.YAxis * width / 2));


            pts.Add((Point3d)(Vector3d.ZAxis * height / 2 + Vector3d.YAxis * width / 2)); // Add first pt again to get closed curve

            Polyline p = new Polyline(pts);
            crvs.Add(p.ToNurbsCurve());

            return true;
        }


        static private bool GetRHSCurve(string section, out List<Curve> crvs)
        {
            crvs = new List<Curve>();
            double height, width, thickness;

            if (!GetDimensionsRHS(section, out height, out width, out thickness))
                return false;

            height /= Utilities.GetScalingFactorFromRhino();
            width /= Utilities.GetScalingFactorFromRhino();
            thickness /= Utilities.GetScalingFactorFromRhino();

            // Outer curve 
            List<Point3d> pts = new List<Point3d>();
            pts.Add((Point3d)(Vector3d.ZAxis * height / 2 + Vector3d.YAxis * width / 2));
            pts.Add((Point3d)(Vector3d.ZAxis * height / 2 - Vector3d.YAxis * width / 2));
            pts.Add((Point3d)(-Vector3d.ZAxis * height / 2 + Vector3d.YAxis * width / 2));
            pts.Add((Point3d)(-Vector3d.ZAxis * height / 2 - Vector3d.YAxis * width / 2));

            pts.Add((Point3d)(Vector3d.ZAxis * height / 2 + Vector3d.YAxis * width / 2)); // Add first pt again to get closed curve

            Polyline p1 = new Polyline(pts);
            crvs.Add(p1.ToNurbsCurve());

            // Inner curve
            pts.Clear();
            pts.Add((Point3d)(Vector3d.ZAxis * ((height / 2) - thickness) + Vector3d.YAxis * ((width / 2) - thickness)));
            pts.Add((Point3d)(Vector3d.ZAxis * ((height / 2) - thickness) - Vector3d.YAxis * ((width / 2) - thickness)));
            pts.Add((Point3d)(-Vector3d.ZAxis * ((height / 2) - thickness) + Vector3d.YAxis * ((width / 2) - thickness)));
            pts.Add((Point3d)(-Vector3d.ZAxis * ((height / 2) - thickness) - Vector3d.YAxis * ((width / 2) - thickness)));

            pts.Add((Point3d)(Vector3d.ZAxis * ((height / 2) - thickness) + Vector3d.YAxis * ((width / 2) - thickness))); // Add first pt again to get closed curve

            Polyline p2 = new Polyline(pts);
            crvs.Add(p2.ToNurbsCurve());

            return true;
        }
    }
}
