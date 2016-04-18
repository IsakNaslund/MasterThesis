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
        List<Point3d> _bbPts;
        List<Curve> _dispCrvN;
        List<Curve> _dispCrvVy;
        List<Curve> _dispCrvVz;
        List<Curve> _dispCrvT;
        List<Curve> _dispCrvMyy;
        List<Curve> _dispCrvMzz;

        public DisplayResultElementsComponent(): base("DisplayElementResults", "ER", "Displays the element results", "CIFem", "Results")
        {
            _bb = new BoundingBox();
            _bbPts = new List<Point3d>();
            _dispCrvN = new List<Curve>();
            _dispCrvVy = new List<Curve>();
            _dispCrvVz = new List<Curve>();
            _dispCrvT = new List<Curve>();
            _dispCrvMyy = new List<Curve>();
            _dispCrvMzz = new List<Curve>();
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
            pManager.AddParameter(new ResultElementParam(), "Result Element", "RE", "Result element", GH_ParamAccess.list);
            pManager.AddBooleanParameter("DisplayToggles", "DT", "Toggles the forces to display. Input should be a list of 6 booleans (N, Vy, Vz, T, Myy, Mzz). [Normal force, shear in weak axis, shear in strong axis, torsion, bending in strong direction, bending in weak direction]", GH_ParamAccess.list);
            pManager.AddNumberParameter("ScalingFactor", "sfac", "Scaling factor for the drawing. Input should be either one 'global' scaling factor or a list of 6 individual ones.", GH_ParamAccess.list, 1);
            pManager.AddTextParameter("Load Comb", "LC", "Load combination to display results from", GH_ParamAccess.item);

            pManager[3].Optional = true;
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            // do nothing, for now
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            // Clear lists
            _dispCrvN.Clear();
            _dispCrvVy.Clear();
            _dispCrvVz.Clear();
            _dispCrvT.Clear();
            _dispCrvMyy.Clear();
            _dispCrvMzz.Clear();
            _bbPts.Clear();

            ////// INDATA //////
            List<ResultElement> res = new List<ResultElement>();
            List<bool> dispToggles = new List<bool>();
            List<double> sFacs = new List<double>();
            string name = null;
            // Result element
            if (!DA.GetDataList(0, res)) { return; }

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
                AddRuntimeMessage(GH_RuntimeMessageLevel.Error, "Number of scale factors in input should be 1 or 6");
                return;
            }

            if (!DA.GetData(3, ref name))
            {
                if (res.Count > 0)
                {
                    name = res[0].N1.First().Key;
                }
            }


            // Now it is assumed that all inputs are correct

            // Get toggles and scaling factors
            bool bN = dispToggles[0];       double sfN = sFacs[0];
            bool bVy = dispToggles[1];      double sfVy = sFacs[1];
            bool bVz = dispToggles[2];      double sfVz = sFacs[2];
            bool bT = dispToggles[3];       double sfT = sFacs[3];
            bool bMyy = dispToggles[4];     double sfMyy = sFacs[4];
            bool bMzz = dispToggles[5];     double sfMzz = sFacs[5];


            foreach (ResultElement re in res)
            {
                // Get element orientation
                Vector3d elX = re.LocalX;
                Vector3d elY = re.LocalY;
                Vector3d elZ = re.elNormal;

                ////// START DRAWING STUFF //////

                // Normal force
                if (bN)
                    _dispCrvN.AddRange(CreateCurvesFromResults(re, re.N1[name], elZ, sfN));

                // Shear force in weak direction
                if (bVy)
                    _dispCrvVy.AddRange(CreateCurvesFromResults(re, re.Vy[name], elY, sfVy));

                // Shear force in strong direction
                if (bVz)
                    _dispCrvVz.AddRange(CreateCurvesFromResults(re, re.Vz[name], elZ, sfVz));

                // Torsion
                if (bT)
                    _dispCrvT.AddRange(CreateCurvesFromResults(re, re.T[name], elZ, sfT));

                // Moment around minor axis (bending in strong direction)
                if (bMyy)
                    _dispCrvMyy.AddRange(CreateCurvesFromResults(re, re.My[name], elZ, sfMyy));

                // Moment around major axis (bending in weak direction)
                if (bMzz)
                    _dispCrvMzz.AddRange(CreateCurvesFromResults(re, re.Mz[name], elY, sfMzz));
            }

            // Set bounding box
            _bb = new BoundingBox(_bbPts);
            _bb.Inflate(1.2); //Increase size by 20% to include all parts of all curves
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="re">The result element containing the data</param>
        /// <param name="values">The values to be plotted</param>
        /// <param name="dir">The direction in which the plot should go</param>
        /// <param name="sFac">Scaling factor for the graph</param>
        private List<Curve> CreateCurvesFromResults(ResultElement re, List<double> values, Vector3d dir, double sFac)
        {
            List<Curve> crvs = new List<Curve>();

            // Get points on original element
            List<Point3d> basePts = new List<Point3d>();
            List<Point3d> pts = new List<Point3d>();
            Rhino.Geometry.Vector3d elX = re.LocalX;
            List<double> lengths = re.pos;
            foreach (double l in lengths)
            {
                Vector3d vec = l * elX;
                Point3d pt = new Point3d(re.sPos.X + vec.X, re.sPos.Y + vec.Y, re.sPos.Z + vec.Z);
                pts.Add(pt);
                basePts.Add(pt);
            }

            // Move points to get curve points
            for (int i = 0; i < values.Count; i++)
                pts[i] = pts[i] + dir * sFac * values[i];

            // Create curve and add it to _dispCrvs
            crvs.Add(Rhino.Geometry.Curve.CreateInterpolatedCurve(pts, 3));
            crvs.Add(Rhino.Geometry.Curve.CreateInterpolatedCurve(basePts, 1));
            for (int i = 0; i < pts.Count; i++)
                crvs.Add(new Rhino.Geometry.Line(basePts[i], pts[i]).ToNurbsCurve());

            // Add points to bounding box
            _bbPts.AddRange(pts);

            return crvs;
        }


        public override void DrawViewportWires(IGH_PreviewArgs args)
        {
            DrawCurves(args, _dispCrvN, System.Drawing.Color.Blue);
            DrawCurves(args, _dispCrvVy, System.Drawing.Color.OldLace);
            DrawCurves(args, _dispCrvVz, System.Drawing.Color.Black);
            DrawCurves(args, _dispCrvT, System.Drawing.Color.Brown);
            DrawCurves(args, _dispCrvMyy, System.Drawing.Color.DarkOrange);
            DrawCurves(args, _dispCrvMzz, System.Drawing.Color.Purple);

            base.DrawViewportWires(args);
        }

        private void DrawCurves(IGH_PreviewArgs args, List<Curve> crvs, System.Drawing.Color color)
        {
            for (int i = 0; i < crvs.Count; i++)
                args.Display.DrawCurve(crvs[i], color);
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
