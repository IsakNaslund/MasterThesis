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
    public class DisplayElementSectionsComponent : GH_Component
    {
        BoundingBox _bb;
        List<Curve> _secCrvs;
        List<Brep> _breps;

        //DEBUG
        List<Point3d> outPts;
        List<Vector3d> outVecs;

        public DisplayElementSectionsComponent(): base("DisplayElementSectionsComponent", "DES", "Displays the element sections", "CIFem", "Results")
        {
            _bb = new BoundingBox();
            _secCrvs = new List<Curve>();
            _breps = new List<Brep>();
            outPts = new List<Point3d>();
            outVecs = new List<Vector3d>();
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new ResultElementParam(), "Result Elements", "RE", "Result elements, storing results from the calculation", GH_ParamAccess.list);
            pManager.AddTextParameter("Load Comb", "LC", "Load combination to display results from", GH_ParamAccess.item);
            pManager.AddBooleanParameter("Show deflections", "def", "Enables or disables showing deformed sections", GH_ParamAccess.item);
            pManager.AddNumberParameter("ScalingFactor", "sfac", "Scaling factor for the drawing.", GH_ParamAccess.item, 1);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            //Do nothing
            //throw new NotImplementedException();
            pManager.AddCurveParameter("Sections", "S", "sections. debug", GH_ParamAccess.list);
            pManager.AddBrepParameter("Breps", "B", "breps debug", GH_ParamAccess.list);
            pManager.AddVectorParameter("Vc", "v", "v debug", GH_ParamAccess.list);
            pManager.AddPointParameter("Pts", "p", "p debug", GH_ParamAccess.list);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            ////// INDATA //////
            List<ResultElement> re = new List<ResultElement>();
            string loadComb = "";
            bool deformed = false;
            double sfac = 0;

            if (!DA.GetDataList(0, re)) { return; }
            if (!DA.GetData(1, ref loadComb)) { return; }
            if (!DA.GetData(2, ref deformed)) { return; }
            if (!DA.GetData(3, ref sfac)) { return; }

            CreateSectionSweeps(re, loadComb, deformed, sfac);

            DA.SetDataList(0, _secCrvs);
            DA.SetDataList(1, _breps);
            DA.SetDataList(2, outVecs);
            DA.SetDataList(3, outPts);
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

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("e41da4d0-cc09-4629-9ff7-8b2f75b127fc");
            }
        }


        private void ResetDrawingData()
        {
            _secCrvs.Clear();
            _breps.Clear();
            _bb = new BoundingBox();
        }


        private bool CreateSectionSweeps(List<ResultElement> res, string loadComb, bool showDeformed, double sFac)
        {
            // Clear lists
            ResetDrawingData();

            List<Point3d> pts = new List<Point3d>();            // Points to create curve from
            List<Point3d> maxPtsForBB = new List<Point3d>();
            List<Brep> sSweeps = new List<Brep>(res.Count);

            //DEBUG
            outPts.Clear();
            outVecs.Clear();

            foreach (ResultElement re in res)
            {
                Vector3d x = re.LocalX;
                Vector3d z = re.elNormal;
                Vector3d y = Vector3d.CrossProduct(z, x);
                y.Unitize();
                Line cl = new Line(re.sPos, x);
                List<Curve> crvs;
                List<Curve> sweepCrvs = new List<Curve>();

                if (CrossSectionCasts.GetSectionPropertyCrvs(re.SectionPropertyString, out crvs))
                {
                    pts.Clear();

                    // Create rail
                    for (int i = 0; i < re.pos.Count; i++)
                    {
                        Point3d pt = CalcDeformedPosition(re, i, loadComb, sFac);

                        // Add points
                        pts.Add(pt);
                    }

                    Curve rail = Curve.CreateInterpolatedCurve(pts, 3);

                    foreach (Curve crv in crvs)
                    {
                        sweepCrvs.Clear();

                        for (int i = 0; i < re.pos.Count; i++)
                        {
                            Curve c = (Curve)crv.Duplicate();

                            Transform rotTrans = Transform.Rotation(Vector3d.XAxis, Vector3d.YAxis, Vector3d.ZAxis, re.LocalX, re.LocalY, re.elNormal);
                            c.Transform(rotTrans);

                            Vector3d defTan = CalcDeformedTangent(rail, pts[i]);
                            outVecs.Add(defTan);
                            outPts.Add(pts[i]);
                            Transform t = GetDeformationTransform(re, defTan, i, loadComb, sFac);
                            c.Transform(t);

                            // Move curves to element positions
                            c.Translate((Vector3d)pts[i]);

                            // Add curves
                            _secCrvs.Add(c);
                            sweepCrvs.Add(c);
                        }

                        Brep[] b = Brep.CreateFromSweep(rail, sweepCrvs, false, Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance);
                        _breps.AddRange(b);
                    }
                }
            }

            _bb = new BoundingBox();

            return true;
        }


        public Point3d CalcDeformedPosition(ResultElement re, int pos, string loadComb, double sFac)
        {
            Point3d pt = re.CreateRhinoPt(re.pos[pos]);

            Vector3d norm = re.elNormal;
            Vector3d tan = re.LocalX;
            Vector3d yDir = re.LocalY;

            Point3d curvePt = pt + tan * (re.u[loadComb][pos] * sFac) + norm * re.w[loadComb][pos] * sFac + yDir * re.v[loadComb][pos] * sFac;

            return curvePt;
        }


        private Vector3d CalcDeformedTangent(Curve c, Point3d pt)
        {
            double t;
            if (!c.ClosestPoint(pt, out t))
                throw new Exception();

            else
                return c.TangentAt(t);
        }

        private Transform GetDeformationTransform(ResultElement re, Vector3d defTan, int pos, string loadComb, double sFac)
        {
            // Rotate normal vector
            Transform t1 = Transform.Rotation(re.fi[loadComb][pos], re.LocalX, Point3d.Origin);
            Vector3d rotY = re.elNormal;
            Vector3d rotZ = re.elNormal;
            rotY.Transform(t1);
            rotZ.Transform(t1);

            //DEBUG, trying to sort out tangent rotation first

            Transform t = Transform.Rotation(re.LocalX, re.LocalY, re.elNormal, defTan, re.LocalY, re.elNormal);

            return t;
        }


        public override void DrawViewportMeshes(IGH_PreviewArgs args)
        {
            DrawBreps(args, _breps, System.Drawing.Color.DarkBlue);
            DrawCurves(args, _secCrvs, System.Drawing.Color.DarkBlue);

            base.DrawViewportMeshes(args);
        }

        private void DrawBreps(IGH_PreviewArgs args, List<Brep> breps, System.Drawing.Color color)
        {
            for (int i = 0; i < breps.Count; i++)
                args.Display.DrawBrepWires(breps[i], color);
        }

        private void DrawCurves(IGH_PreviewArgs args, List<Curve> crvs, System.Drawing.Color color)
        {
            for (int i = 0; i < crvs.Count; i++)
                args.Display.DrawCurve(crvs[i], color);
        }


    }
}
