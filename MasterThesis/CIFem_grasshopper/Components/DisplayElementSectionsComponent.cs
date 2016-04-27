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

        public DisplayElementSectionsComponent(): base("DisplayElementSectionsComponent", "DES", "Displays the element sections", "CIFem", "Results")
        {
            _bb = new BoundingBox();
            _secCrvs = new List<Curve>();
            _breps = new List<Brep>();
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new ResultElementParam(), "Result Elements", "RE", "Result elements, storing results from the calculation", GH_ParamAccess.list);
            pManager.AddTextParameter("Load Comb", "LC", "Load combination to display results from", GH_ParamAccess.item);
            pManager.AddBooleanParameter("Show deflections", "def", "Enables or disables showing deformed sections", GH_ParamAccess.item, false);
            pManager.AddNumberParameter("ScalingFactor", "sfac", "Scaling factor for the drawing.", GH_ParamAccess.item, 1);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            //Do nothing
            //throw new NotImplementedException();
            pManager.AddCurveParameter("Sections", "S", "sections. debug", GH_ParamAccess.list);
            pManager.AddBrepParameter("Breps", "B", "breps debug", GH_ParamAccess.list);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            ////// INDATA //////
            List<ResultElement> re = new List<ResultElement>();
            string loadComb = "";
            bool deformed = false;
            double sfac = 0;

            if (!DA.GetDataList(0, re)) { return; }
            if (!DA.GetData(2, ref deformed)) { return; }
            if (deformed)
            {
                if (!DA.GetData(1, ref loadComb)) { return; }
                if (!DA.GetData(3, ref sfac)) { return; }
            }
            else
            {
                sfac = 1;
            }

            CreateSectionSweeps(re, loadComb, deformed, sfac);

            DA.SetDataList(0, _secCrvs);
            DA.SetDataList(1, _breps);
        }

        /*public override BoundingBox ClippingBox
        {
            get
            {
                //return base.ClippingBox;
                return _bb;
            }
        }*/

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
            List<Brep> sSweeps = new List<Brep>(res.Count);

            foreach (ResultElement re in res)
            {
                List<Curve> crvs;
                List<Curve> sweepCrvs = new List<Curve>();

                // Start and end caps
                List<Curve> sCap = new List<Curve>();
                List<Curve> eCap = new List<Curve>();

                if (CrossSectionCasts.GetSectionPropertyCrvs(re.SectionPropertyString, out crvs))
                {
                    pts.Clear();

                    // Create rail
                    Curve rail;
                    if (showDeformed)
                    {
                        for (int i = 0; i < re.pos.Count; i++)
                        {
                            Point3d pt = CalcDeformedPosition(re, i, loadComb, sFac);

                            // Add points to list
                            pts.Add(pt);
                        }

                        rail = Curve.CreateInterpolatedCurve(pts, 3);
                    }
                    else
                    {
                        // Add points to list for transform of curves to positions
                        for (int i = 0; i < re.pos.Count; i++)
                            pts.Add(CalcUndeformedPosition(re, i));

                        rail = (Curve)new Line(re.sPos, re.ePos).ToNurbsCurve();
                    }

                    foreach (Curve crv in crvs)
                    {
                        // Rotation to local coordinates
                        Transform rotTrans = Transform.Rotation(Vector3d.XAxis, Vector3d.YAxis, Vector3d.ZAxis, re.LocalX, re.LocalY, re.elNormal);
                        crv.Transform(rotTrans);

                        sweepCrvs.Clear();

                        for (int i = 0; i < re.pos.Count; i++)
                        {
                            Curve c = (Curve)crv.Duplicate();

                            Transform defTrans;
                            if (showDeformed)
                            {
                                // Rotation to deformed shape
                                Vector3d defTan = CalcDeformedTangent(rail, pts[i]);
                                defTrans = GetDeformationTransform(re, defTan, i, loadComb, sFac);
                            }
                            else
                                defTrans = Transform.Identity;

                            // Calculate move to element positions
                            Transform tTrans = Transform.Translation((Vector3d)pts[i]);

                            // Perform transformation
                            c.Transform(defTrans);
                            c.Transform(tTrans);

                            // Add curves
                            _secCrvs.Add(c);
                            sweepCrvs.Add(c);
                        }

                        //Add curves to cap curves
                        if (sweepCrvs.Count > 0)
                        {
                            sCap.Add(sweepCrvs[0]);
                            eCap.Add(sweepCrvs[sweepCrvs.Count-1]);
                        }

                        //Create sweep
                        Brep[] b = Brep.CreateFromSweep(rail, sweepCrvs, true, Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance);
                        _breps.AddRange(b);
                    }

                    // Cap sections
                    _breps.Add(Utilities.CapSections(sCap));
                    _breps.Add(Utilities.CapSections(eCap));
                }
            }

            _bb = new BoundingBox(pts);

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

        public Point3d CalcUndeformedPosition(ResultElement re, int pos)
        {
            return re.CreateRhinoPt(re.pos[pos]);
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
            // Rotate tangent
            Transform t1;
            double angle = Vector3d.VectorAngle(re.LocalX, defTan);
            if (Math.Abs(angle) >= Rhino.RhinoDoc.ActiveDoc.PageAngleToleranceRadians)
                t1 = Transform.Rotation(angle, Vector3d.CrossProduct(re.LocalX, defTan), Point3d.Origin);
            else
                t1 = Transform.Identity;

            // Rotate in plane
            Transform t2 = Transform.Rotation(re.fi[loadComb][pos]*sFac, defTan, Point3d.Origin);

            return t1 *t2;
        }


        public override void DrawViewportMeshes(IGH_PreviewArgs args)
        {
            // Dont do this, results are strange. Instead output the breps and curves

            //DrawBreps(args, _breps, System.Drawing.Color.DarkBlue);
            //DrawCurves(args, _secCrvs, System.Drawing.Color.DarkBlue);

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
