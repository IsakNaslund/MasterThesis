using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_wrapper;

namespace CIFem_grasshopper
{
    internal static class CrossSectionCasts
    {
        static internal bool CrossSectionFormString(string section, out WR_IXSec xSec)
        {
            if (section.ToUpper().StartsWith("REC"))
            {
                return RectangularCrossSection(section, out xSec);
            }
            else if (section.ToUpper().StartsWith("RHS"))
            {
                return RHSCrossSection(section, out xSec);
            }

            xSec = null;

            return false;
        }

        static private bool RHSCrossSection(string section, out WR_IXSec xSec)
        {
            string[] numbers = System.Text.RegularExpressions.Regex.Split(section, @"\D+");

            double height, width, thickness;

            if (numbers.Length < 4 || !double.TryParse(numbers[1], out height) || !double.TryParse(numbers[2], out width) || !double.TryParse(numbers[3], out thickness))
            {
                xSec = null;
                return false;
            }

            double factor = Utilities.GetScalingFactorFromRhino();
            xSec = new WR_XSecRHS(height * factor, width * factor, thickness * factor);
            return true;
        }

        static private bool RectangularCrossSection(string section, out WR_IXSec xSec)
        {
            string[] numbers = System.Text.RegularExpressions.Regex.Split(section, @"\D+");

            double height, width;

            if (numbers.Length < 3 || !double.TryParse(numbers[1], out height) || !double.TryParse(numbers[2], out width))
            {
                xSec = null;
                return false;
            }

            double factor = Utilities.GetScalingFactorFromRhino();

            xSec = new WR_XSecRect(height * factor, width * factor);
            return true;

        }
    }
}
