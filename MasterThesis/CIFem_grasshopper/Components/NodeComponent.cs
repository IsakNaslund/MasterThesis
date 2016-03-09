using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;
using Rhino.Geometry;

using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class NodeComponent : GH_Component
    {
        public NodeComponent(): base("RestraintNode", "RNode", "Creates restraint nodes", "CIFem", "Nodes")
        {
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("e946fa47-6943-497a-896d-a51949f33377");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddPointParameter("Position", "P", "Node position", GH_ParamAccess.item);
            pManager.AddBooleanParameter("Releases", "R", "Releases for the restraint. Should be a list of 6 bools. True = Fixed, False = Free", GH_ParamAccess.list);
            pManager.AddVectorParameter("Point Load", "P", "Point load on the node in Newtons [N]", GH_ParamAccess.item);
            pManager.AddVectorParameter("Point Moment", "M", "Point moment on the node in Newton meter [Nm]", GH_ParamAccess.item);
            pManager.AddPlaneParameter("Orientation", "Pl", "Add an optional plane for node restraints", GH_ParamAccess.item, Plane.WorldXY);

            pManager[1].Optional = true;
            pManager[2].Optional = true;
            pManager[3].Optional = true;
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddParameter(new NodeParam(), "Node", "N", "Loaded or restrained node", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            ///// INPUTS /////
            Point3d pt = Point3d.Unset;
            List<bool> rels = new List<bool>();
            Vector3d ptLoad = Vector3d.Zero;
            Vector3d ptMoment = Vector3d.Zero;
            Plane pl = Plane.Unset;

            if (!DA.GetData(0, ref pt)) { return; }

            if (!DA.GetDataList<bool>(1, rels))
            {
                //Set as unrestrained if no release information is provided
                for (int i = 0; i < 6; i++)
                {
                    rels.Add(false);
                }
            }

            if (rels.Count != 6)
            {
                AddRuntimeMessage(GH_RuntimeMessageLevel.Error, "Number of bools in input should be 6");
                return;
            }

            //If no data is provided zero vectors will be used
            DA.GetData(2, ref ptLoad);
            DA.GetData(3, ref ptMoment);

            if(!ptLoad.IsValid)
            {
                AddRuntimeMessage(GH_RuntimeMessageLevel.Error, "Invalid point load provided");
                return;
            }

            if (!ptMoment.IsValid)
            {
                AddRuntimeMessage(GH_RuntimeMessageLevel.Error, "Invalid point moment provided");
                return;
            }


            if (!DA.GetData(4, ref pl))
            {
                // If no plane submitted, use global XY plane
                pl = new Rhino.Geometry.Plane(new Rhino.Geometry.Point3d(0,0,0), 
                    new Rhino.Geometry.Vector3d(1,0,0), new Rhino.Geometry.Vector3d(0,1,0));
            }


            ///// SOLVE /////

            double factor = Utilities.GetScalingFactorFromRhino();

            WR_XYZ wrXYZ = new WR_XYZ(pt.X * factor, pt.Y * factor, pt.Z * factor);
            WR_Vector wrX = GetUnitizedWR_Vector(pl.XAxis);
            WR_Vector wrY = GetUnitizedWR_Vector(pl.YAxis);
            WR_Vector wrZ = GetUnitizedWR_Vector(pl.ZAxis);

            WR_Plane wrPl = new WR_Plane(wrX, wrY, wrZ, wrXYZ);
            WR_Restraint rest = new WR_Restraint(wrPl, rels[0], rels[1], rels[2], rels[3], rels[4], rels[5]);

            WR_Vector ptL = new WR_Vector(ptLoad.X, ptLoad.Y, ptLoad.Z);
            WR_Vector ptM = new WR_Vector(ptMoment.X, ptMoment.Y, ptMoment.Z);

            


            WR_INode node = new WR_Node3d(pt.X * factor, pt.Y * factor, pt.Z * factor, rest, ptL, ptM);

            ///// OUTPUTS /////
            DA.SetData(0, node);
        }


        private WR_Vector GetUnitizedWR_Vector(Rhino.Geometry.Vector3d rhVec)
        {
            rhVec.Unitize();
            return new WR_Vector(rhVec.X, rhVec.Y, rhVec.Z);
        }
    }
}
