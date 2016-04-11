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
        private List<Curve> secCrvs { get; set; }
        private List<Brep> breps { get; set; }

        public DisplayElementSectionsComponent(): base("DisplayElementSectionsComponent", "DES", "Displays the element sections", "CIFem", "Results")
        {
            _bb = new BoundingBox();
            secCrvs = new List<Curve>();
            breps = new List<Brep>();
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new ResultElementParam(), "Result Elements", "RE", "Result elements, storing results from the calculation", GH_ParamAccess.list);
            pManager.AddBooleanParameter("Show deflections", "def", "Enables or disables showing deformed sections", GH_ParamAccess.item);
            pManager.AddNumberParameter("ScalingFactor", "sfac", "Scaling factor for the drawing.", GH_ParamAccess.item, 1);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            //Do nothing
            //throw new NotImplementedException();
            pManager.AddCurveParameter("Sections", "S", "sections. debug", GH_ParamAccess.list);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            ////// INDATA //////
            List<ResultElement> re = new List<ResultElement>();
            bool deformed = false;
            double sfac = 0;

            if (!DA.GetDataList(0, re)) { return; }
            if (!DA.GetData(1, ref deformed)) { return; }
            if (!DA.GetData(2, ref sfac)) { return; }

            breps = CreateSectionSweeps(re);

            DA.SetDataList(0, secCrvs);
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
            secCrvs.Clear();
            breps.Clear();
            _bb = new BoundingBox();
        }

        private List<Brep> CreateSectionSweeps(List<ResultElement> res)
        {
            // Clear lists
            ResetDrawingData();

            List<Point3d> pts = new List<Point3d>();            // Points to create curve from
            List<Point3d> maxPtsForBB = new List<Point3d>();
            List<Brep> sSweeps = new List<Brep>(res.Count);

            foreach (ResultElement re in res)
            {
                Vector3d x = re.LocalX;
                Vector3d z = re.elNormal;
                Vector3d y = Vector3d.CrossProduct(z, x);
                y.Unitize();
                Line cl = new Line(re.sPos, x);
                List<Curve> crvs;

                pts.Clear();

                if (CrossSectionCasts.GetSectionPropertyCrvs(re.SectionPropertyString, out crvs))
                {
                    foreach (Curve crv in crvs)
                    {
                        for (int i = 0; i < re.pos.Count; i++)
                        {
                            Curve c = (Curve)crv.Duplicate();


                            Transform rotTrans = Transform.Rotation(Vector3d.XAxis, Vector3d.YAxis, Vector3d.ZAxis, re.LocalX, re.LocalY, re.elNormal);
                            c.Transform(rotTrans);

                            Point3d pt = re.CreateRhinoPt(re.pos[i]);
                            // Move curves to element origin
                            c.Translate((Vector3d)pt);


                            // Align curves to element
                            //Vector3d locComb = re.LocalX + re.LocalY + re.elNormal;
                            //Vector3d globComb = new Vector3d(1, 1, 1);
                            //Vector3d rotAxis = Vector3d.CrossProduct(globComb, locComb);


                            //if (rotAxis != Vector3d.Zero)
                            //{
                            //    double angle = Vector3d.VectorAngle(globComb, locComb);
                            //    c.Rotate(angle, rotAxis, pt);
                            //    
                            //}

                            /*
                            // Align curves to element
                            Vector3d rotX = Vector3d.CrossProduct(Vector3d.XAxis, re.LocalX);
                            if (rotX!=Vector3d.Zero)
                            {
                                double Xa = Vector3d.VectorAngle(Vector3d.XAxis, re.LocalX);
                                c.Rotate(Xa, rotX, pt);
                            }
                            

                            Vector3d rotY = Vector3d.CrossProduct(Vector3d.YAxis, re.LocalY);
                            double Ya = Vector3d.VectorAngle(Vector3d.YAxis, re.LocalY);
                            c.Rotate(Ya, rotY, pt);

                            Vector3d rotZ = Vector3d.CrossProduct(Vector3d.XAxis, re.elNormal);
                            double Za = Vector3d.VectorAngle(Vector3d.XAxis, re.elNormal);
                            c.Rotate(Za, rotZ, pt);
                            */
                            // Add curves
                            secCrvs.Add(c);
                        }
                    }
                }
            }

            _bb = new BoundingBox();

            

            return sSweeps;
        }


        public override void DrawViewportMeshes(IGH_PreviewArgs args)
        {
            DrawBreps(args, breps, System.Drawing.Color.DarkBlue);
            DrawCurves(args, secCrvs, System.Drawing.Color.DarkBlue);

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
