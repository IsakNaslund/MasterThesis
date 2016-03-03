using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class BeamProperties
    {
        private WR_IXSec _section;
        private WR_ReleaseBeam3d _stRel, _enRel;
        private WR_Material _mat;

        public BeamProperties()
        {
            _section = null;
            _stRel = null;
            _enRel = null;
            _mat = null;

        }

        //public BeamProperties(double matStiff, double poison, string section, WR_ReleaseBeam3d stRel, WR_ReleaseBeam3d enRel)
        //{
//
 //           _stRel = stRel;
 //           _enRel = enRel;
 //           _section = CrossSectionFormString(section);
 //       }

        public BeamProperties(BeamProperties other)
        {
            _mat = other._mat.Copy();
            _section = other._section;
            _stRel = other._stRel.Copy();
            _enRel = other._enRel.Copy();

        }

        public BeamProperties(WR_Material mat, string section, WR_ReleaseBeam3d stRel, WR_ReleaseBeam3d enRel)
        {
            _mat = mat;
            _stRel = stRel;
            _enRel = enRel;
            _section = CrossSectionFormString(section);
        }

        private WR_IXSec CrossSectionFormString(string section)
        {
            if (section.ToUpper().StartsWith("REC"))
            {
                return RectangularCrossSection(section);
            }

            

            throw new NotImplementedException();

            return null;
        }

        private WR_IXSec RectangularCrossSection(string section)
        {
            string[] numbers = System.Text.RegularExpressions.Regex.Split(section, @"\D+");

            double height, width;

            if (numbers.Length < 3 || !double.TryParse(numbers[1], out height) || !double.TryParse(numbers[2], out width))
            {
                throw new Exception("Wrong string format for cross section");
            }

            double factor = Utilities.GetScalingFactorFromRhino();

            return new WR_XSecRect(height* factor, width* factor);

        }

        public override string ToString()
        {
            //string str = "Stiffness:" + _matStiff + "\n";
            //str += "Poissons Ratio:" + _poison + "\n";
            string str = _section.ToString() + "\n";
            str += "Start release:" + _stRel.ToString() + "\n";
            str += "End release" + _enRel.ToString();





            return str;
        }


        //Getters

        /*public double MaterialStiffness
        { get { return _matStiff; } }

        public double PoissonsRatio
        { get { return _poison; } }*/

        public WR_Material Material
        { get { return _mat; } }

        public WR_IXSec CrossSection
        { get { return _section; } }

        public WR_ReleaseBeam3d StartRelease
        { get { return _stRel; } }

        public WR_ReleaseBeam3d EndRelease
        { get { return _enRel; } }
    }
}
