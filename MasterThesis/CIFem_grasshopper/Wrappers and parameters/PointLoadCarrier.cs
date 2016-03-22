using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Rhino.Geometry;
using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class PointLoadCarrier
    {
        public Point3d Pos { get; private set; }
        public Vector3d Force { get; private set; }
        public Vector3d Moment { get; private set; }

        public PointLoadCarrier()
        {
            Pos = Point3d.Unset;
            Force = Vector3d.Unset;
            Moment = Vector3d.Unset;
        }

        public PointLoadCarrier(Point3d pos, Vector3d force, Vector3d moment)
        {
            Pos = pos;
            Force = force;
            Moment = moment;
        }

        public WR_XYZ CIPos
        {
            get
            {
                double sfac = Utilities.GetScalingFactorFromRhino();
                return new WR_XYZ(Pos.X* sfac, Pos.Y* sfac, Pos.Z* sfac);
            }
        }

        public WR_Vector CIForce
        {
            get
            {
                return new WR_Vector(Force.X, Force.Y, Force.Z);
            }
        }

        public WR_Vector CIMoment
        {
            get
            {
                return new WR_Vector(Moment.X, Moment.Y, Moment.Z);
            }
        }

        public static PointLoadCarrier operator *(PointLoadCarrier pl,double t)
        {
            return new PointLoadCarrier(pl.Pos, pl.Force * t, pl.Moment * t);
        }

        public static PointLoadCarrier operator /(PointLoadCarrier pl, double t)
        {
            return new PointLoadCarrier(pl.Pos, pl.Force / t, pl.Moment / t);
        }

        public bool IsValid
        {
            get
            {
                if (!Pos.IsValid)
                    return false;
                if (!Force.IsValid)
                    return false;
                if (!Moment.IsValid)
                    return false;
                return true;

            }
        }
    }
}
