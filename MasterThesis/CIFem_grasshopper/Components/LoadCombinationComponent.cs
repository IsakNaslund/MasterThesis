using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;

using Rhino.Geometry;

using CIFem_wrapper;
using System.Drawing;

namespace CIFem_grasshopper
{
    public class LoadCombinationComponent : GH_Component
    {
        public LoadCombinationComponent() : base("Load combination", "LC", "Constructs a loadcombination", "CIFem", "Loads")
        {
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("b358c6d4-7207-4ca4-a1c3-8a781eeb1750");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddTextParameter("Name", "N", "Name of the load combination", GH_ParamAccess.item);
            pManager.AddBooleanParameter("GravityOn", "GO", "Turns gravity on or off for the load case", GH_ParamAccess.item);
            pManager.AddVectorParameter("Gravity Field", "GF", "The driection and aplitude of the gravity. Deafault set to 9.82 m/s^2 in negative z-direction", GH_ParamAccess.item, new Rhino.Geometry.Vector3d(0, 0, -9.82));
            pManager.AddParameter(new PointLoadParameter(), "PointLoads", "PL", "A set of pointloads", GH_ParamAccess.list);

            pManager[3].Optional = true;

        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddParameter(new LoadCombParameter(), "Load combination", "LC", "Constructed load combination", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            string name = String.Empty;
            bool gravityOn = false;
            Vector3d gravField = Vector3d.Unset;
            List<PointLoadCarrier> ptLds = new List<PointLoadCarrier>();

            if (!DA.GetData(0, ref name)) { return; }
            if (!DA.GetData(1, ref gravityOn)) { return; }
            if (!DA.GetData(2, ref gravField)) { return; }

            if(!DA.GetDataList(3, ptLds))
            {
                AddRuntimeMessage(GH_RuntimeMessageLevel.Remark, "No pointloads provided");
            }

            WR_LoadCombination loadComb;

            if(gravityOn)
            {
                loadComb = new WR_LoadCombination(name, new WR_Vector(gravField.X, gravField.Y, gravField.Z));
            }
            else
            {
                loadComb = new WR_LoadCombination(name, gravityOn);
            }

            foreach (PointLoadCarrier plc in ptLds)
            {
                loadComb.AddPointLoad(plc.CIForce, plc.CIMoment, plc.CIPos);
            }

            DA.SetData(0, loadComb);

        }


        protected override Bitmap Icon
        {
            get
            {
                return Properties.Resources.LoadCombinationIcon;
            }
        }
    }
}
