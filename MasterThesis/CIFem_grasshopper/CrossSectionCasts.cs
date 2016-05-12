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
            RHS,                            // Rectangular hollow section
            CSS,                            // Circular solid section
            CHS,                            // Circular hollow section
            Invalid,
        }




        /// <summary>
        /// Read a string and returns an enum of the CrossSectionType
        /// </summary>
        /// <param name="section">String to read</param>
        /// <returns></returns>
        internal static CrossSectionType CrossSectionTypeFromString(string section)
        {
            if (section.ToUpper().StartsWith("REC"))
                return CrossSectionType.RectangularSolid;

            else if (section.ToUpper().StartsWith("RHS"))
                return CrossSectionType.RHS;

            else if (section.ToUpper().StartsWith("CHS"))
                return CrossSectionType.CHS;

            else if (section.ToUpper().StartsWith("CSS"))
                return CrossSectionType.CSS;

            return CrossSectionType.Invalid;
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

                case CrossSectionType.CHS:
                    return CHSCrossSection(section, out xSec);

                case CrossSectionType.CSS: // Not implemented yet
                    return CSSCrossSection(section, out xSec);

                case CrossSectionType.Invalid:
                default:
                    {
                        xSec = null;
                        return false;
                    }
            }
        }


        /// <summary>
        /// Takes a section property string in meters and transforms it to mm
        /// </summary>
        /// <param name="section"></param>
        /// <returns></returns>
        static internal string GetRhinoString(string section)
        {
            // Find index of first number
            string id = "";
            char[] n = "0123456789".ToCharArray();
            int i = section.IndexOfAny(n);

            // Get start of string
            if (i > 0)
                id = section.Substring(0, i);

            // Get and multiply numbers
            double sfac = 1000;
            List<string> numbers = System.Text.RegularExpressions.Regex.Split(section, @"[^0-9\.]+").Where(c => c != "." && c.Trim() != "").ToList();

            double dim = double.NaN;

            // Add first number
            if (double.TryParse(numbers[0], out dim))
                id = id + dim * sfac;
            
            // Add all other numbers
            for (i = 1; i < numbers.Count; i++)
                if (double.TryParse(numbers[i], out dim))
                    id = id + "x" + dim * sfac;

            return id;
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

        static private bool CHSCrossSection(string section, out WR_IXSec xSec)
        {
            double radius, thickness;

            if (!GetDimensionsCHS(section, out radius, out thickness))
            {
                xSec = null;
                return false;
            }

            double factor = Utilities.GetScalingFactorFromRhino();
            radius *= factor;
            thickness *= factor;

            xSec = new WR_XSecCHS(radius, thickness);
            return true;
        }

        // Circular solid section
        static private bool CSSCrossSection(string section, out WR_IXSec xSec)
        {
            double radius;

            if (!GetDimensionsCSS(section, out radius))
            {
                xSec = null;
                return false;
            }

            double factor = Utilities.GetScalingFactorFromRhino();
            radius *= factor;

            xSec = new WR_XSecCSS(radius);
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

            //string[] numbers = System.Text.RegularExpressions.Regex.Split(section, @"\D+");
            List<string> numbers = System.Text.RegularExpressions.Regex.Split(section, @"[^0-9\.]+").Where(c => c != "." && c.Trim() != "").ToList();

            if (numbers.Count < 3 || !double.TryParse(numbers[0], out height) || !double.TryParse(numbers[1], out width) || !double.TryParse(numbers[2], out thickness))
                return false;

            return true;
        }


        static private bool GetDimensionsCHS(string section, out double radius, out double thickness)
        {
            radius = -1;
            thickness = -1;

            List<string> numbers = System.Text.RegularExpressions.Regex.Split(section, @"[^0-9\.]+").Where(c => c != "." && c.Trim() != "").ToList();

            if (numbers.Count < 2 || !double.TryParse(numbers[0], out radius) || !double.TryParse(numbers[1], out thickness))
                return false;

            return true;
        }

        //Circular solid section
        static private bool GetDimensionsCSS(string section, out double radius)
        {
            radius = -1;

            List<string> numbers = System.Text.RegularExpressions.Regex.Split(section, @"[^0-9\.]+").Where(c => c != "." && c.Trim() != "").ToList();

            if (numbers.Count < 1 || !double.TryParse(numbers[0], out radius))
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

                case CrossSectionType.CHS:
                    return GetCHSCurve(section, out crvs);

                case CrossSectionType.CSS:
                    return GetCSSCurve(section, out crvs);

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
            pts.Add((Point3d)(-Vector3d.ZAxis * height / 2 - Vector3d.YAxis * width / 2));
            pts.Add((Point3d)(-Vector3d.ZAxis * height / 2 + Vector3d.YAxis * width / 2));

            pts.Add((Point3d)(Vector3d.ZAxis * height / 2 + Vector3d.YAxis * width / 2)); // Add first pt again to get closed curve

            Polyline p1 = new Polyline(pts);
            crvs.Add(p1.ToNurbsCurve());

            // Inner curve
            pts.Clear();
            pts.Add((Point3d)(Vector3d.ZAxis * ((height / 2) - thickness) + Vector3d.YAxis * ((width / 2) - thickness)));
            pts.Add((Point3d)(Vector3d.ZAxis * ((height / 2) - thickness) - Vector3d.YAxis * ((width / 2) - thickness)));
            pts.Add((Point3d)(-Vector3d.ZAxis * ((height / 2) - thickness) - Vector3d.YAxis * ((width / 2) - thickness)));
            pts.Add((Point3d)(-Vector3d.ZAxis * ((height / 2) - thickness) + Vector3d.YAxis * ((width / 2) - thickness)));

            pts.Add((Point3d)(Vector3d.ZAxis * ((height / 2) - thickness) + Vector3d.YAxis * ((width / 2) - thickness))); // Add first pt again to get closed curve

            Polyline p2 = new Polyline(pts);
            crvs.Add(p2.ToNurbsCurve());

            return true;
        }


        static private bool GetCHSCurve(string section, out List<Curve> crvs)
        {
            crvs = new List<Curve>();
            double radius, thickness;

            if (!GetDimensionsCHS(section, out radius, out thickness))
                return false;

            radius /= Utilities.GetScalingFactorFromRhino();
            thickness /= Utilities.GetScalingFactorFromRhino();

            Curve co = (Curve)new Circle(Plane.WorldYZ, radius).ToNurbsCurve();
            Curve ci = (Curve)new Circle(Plane.WorldYZ, radius - thickness).ToNurbsCurve();

            crvs.Add(co);
            crvs.Add(ci);

            return true;
        }


        static private bool GetCSSCurve(string section, out List<Curve> crvs)
        {
            crvs = new List<Curve>();
            double radius;

            if (!GetDimensionsCSS(section, out radius))
                return false;

            radius /= Utilities.GetScalingFactorFromRhino();

            Curve c = (Curve)new Circle(Plane.WorldYZ, radius).ToNurbsCurve();

            crvs.Add(c);

            return true;
        }
    }
}
