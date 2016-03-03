﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Rhino;

namespace CIFem_grasshopper
{
    static class Utilities
    {

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


    }
}
