using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel;
using Rhino.Geometry;

namespace CIFem_grasshopper.Components
{
    public class DisplayResultElementsComponent : GH_Component
    {
        BoundingBox _bb;
        List<Curve> _dispCrvs;

        public DisplayResultElementsComponent(): base("DisplayElementResults", "ER", "Displays the element results", "CIFem", "Results")
        {
            _bb = new BoundingBox();
            _dispCrvs = new List<Curve>();
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("22339b30-0e9d-4e5a-ba59-32e8e3652bd4");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new ResultElementParam(), "Result Element", "RE", "Result element", GH_ParamAccess.item);
            pManager.AddBooleanParameter("DisplayToggles", "DT", "Toggles the forces to display. Input should be a list of 6 booleans (N, Vy, Vz, T, Myy, Mzz). [Normal force, shear in weak axis, shear in strong axis, torsion, bending in strong direction, bending in weak direction]", GH_ParamAccess.list);
            pManager.AddNumberParameter("ScalingFactor", "sfac", "Scaling factor for the drawing. Input should be either one 'global' scaling factor or a list of 6 individual ones.", GH_ParamAccess.list);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            // do nothing, for now
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            _dispCrvs.Clear();

            ////// INDATA //////
            ResultElement re = null;
            List<bool> dispToggles = new List<bool>();
            List<double> sFacs = new List<double>();

            // Result element
            if (!DA.GetData(0, ref re)) { return; }
            _bb = new BoundingBox(re.sPos, re.ePos);

            // Display toggles
            if (!DA.GetDataList(1, dispToggles)) { return; }
            if (dispToggles.Count != 6)
            {
                AddRuntimeMessage(GH_RuntimeMessageLevel.Error, "Number of bools in input should be 6");
                return;
            }

            // Scaling factors
            if (!DA.GetDataList(2, sFacs)) { return; }
            bool sFacInputCorrect = false;
            if (sFacs.Count == 6)
                sFacInputCorrect = true;
            else if (sFacs.Count == 1)
            {
                sFacs.AddRange(new List<double> { sFacs[0], sFacs[0], sFacs[0], sFacs[0], sFacs[0] });
                sFacInputCorrect = true;
            }
            if (!sFacInputCorrect)
            {
                AddRuntimeMessage(GH_RuntimeMessageLevel.Error, "Number of scal in input should be 6");
                return;
            }

            // Now it is assumed that all inputs are correct

            // Get toggles and scaling factors
            bool bN = dispToggles[0];       double sfN = sFacs[0];
            bool bVy = dispToggles[1];      double sfVy = sFacs[1];
            bool bVz = dispToggles[2];      double sfVz = sFacs[2];
            bool bT = dispToggles[3];       double sfT = sFacs[3];
            bool bMyy = dispToggles[4];     double sfMyy = sFacs[4];
            bool bMzz = dispToggles[5];     double sfMzz = sFacs[5];

            // Get element information
            Rhino.Geometry.Vector3d normal = re.elNormal;



            ////// START DRAWING STUFF //////

            // Normal force
            if (bN)
                CreateCurvesFromResults(re, re.N1, normal, sfN);

            // Shear force in weak direction
            if (bVy)
            {


            }

            // Shear force in strong direction
            if (bVz)
            {


            }

            // Torsion
            if (bT)
            {


            }

            // Moment around minor axis (bending in strong direction)
            if (bMyy)
            {


            }

            // Moment around major axis (bending in weak direction)
            if (bMzz)
            {


            }

            
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="re">The result element containing the data</param>
        /// <param name="values">The values to be plotted</param>
        /// <param name="dir">The direction in which the plot should go</param>
        /// <param name="sFac">Scaling factor for the graph</param>
        private void CreateCurvesFromResults(ResultElement re, List<double> values, Vector3d dir, double sFac)
        {
            // Get points on original element
            List<Point3d> pts = new List<Point3d>();
            Rhino.Geometry.Vector3d elX = re.GetLocalXVec(true);
            List<double> lengths = re.pos;
            foreach (double l in lengths)
            {
                Vector3d vec = l * elX;
                Point3d pt = new Point3d(re.sPos.X + vec.X, re.sPos.Y + vec.Y, re.sPos.Z + vec.Z);
                pts.Add(pt);
            }

            // Move points to get curve points
            for (int i = 0; i < values.Count; i++)
                pts[i] = pts[i] + dir * sFac * values[i];

            // Create curve and add it to _dispCrvs
            _dispCrvs.Add(Rhino.Geometry.Curve.CreateInterpolatedCurve(pts, 3));
        }


        public override void DrawViewportWires(IGH_PreviewArgs args)
        {
            for (int i = 0; i < _dispCrvs.Count; i++)
            {
                args.Display.DrawCurve(_dispCrvs[i], System.Drawing.Color.BurlyWood);
            }

            base.DrawViewportWires(args);
        }

        public override BoundingBox ClippingBox
        {
            get
            {
                //return base.ClippingBox;
                return _bb;
            }
        }

        // Not really sure about this, but testing. /C
        public override bool IsPreviewCapable
        {
            get
            {
                return true;
            }
        }
    }
}
