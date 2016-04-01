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
        private List<Brep> breps { get; set; }

        public DisplayElementSectionsComponent(): base("DisplayElementSectionsComponent", "DES", "Displays the element sections", "CIFem", "Results")
        {
            _bb = new BoundingBox();
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




        private List<Brep> CreateSectionSweeps(List<ResultElement> res)
        {
            List<Point3d> pts = new List<Point3d>();            // Points to create curve from
            List<Point3d> maxPtsForBB = new List<Point3d>();
            List<Brep> sSweeps = new List<Brep>(res.Count);

            foreach (ResultElement re in res)
            {
                Vector3d x = re.GetLocalXVec(false);
                Vector3d z = re.elNormal;
                Vector3d y = Vector3d.CrossProduct(z, x);
                y.Unitize();
                Line cl = new Line(re.sPos, x);

                pts.Clear();

                // Section curves to sweep (2 if hollow sections)
                Curve c1;
                Curve c2;

                // Cast section from string
                String xs = re.SectionPropertyString;

                Utilities.CrossSectionType wrXSec = Utilities.CrossSectionTypeFromString(xs);
                switch (wrXSec)
                {
                    case Utilities.CrossSectionType.RectangularSolid:
                        /*
                        double height = r.GetHeight() / Utilities.GetScalingFactorFromRhino();
                        double width = r.GetWidth() / Utilities.GetScalingFactorFromRhino();

                        pts.Add(re.sPos + z * height / 2 + y * width / 2);
                        pts.Add(re.sPos + z * height / 2 - y * width / 2);
                        pts.Add(re.sPos - z * height / 2 + y * width / 2);
                        pts.Add(re.sPos - z * height / 2 - y * width / 2);

                        pts.Add(re.sPos + z * height / 2 + y * width / 2); // Add first pt again to get closed curve

                        c1 = Curve.CreateInterpolatedCurve(pts, 1);
                        */
                        break;

                    case Utilities.CrossSectionType.RHS:
                        /*
                        double height = r.GetHeight() / Utilities.GetScalingFactorFromRhino();
                        double width = r.GetWidth() / Utilities.GetScalingFactorFromRhino();
                        double thickness = r.GetThickness() / Utilities.GetScalingFactorFromRhino();

                        // Outer curve 
                        pts.Add(re.sPos + z * height / 2 + y * width / 2);
                        pts.Add(re.sPos + z * height / 2 - y * width / 2);
                        pts.Add(re.sPos - z * height / 2 + y * width / 2);
                        pts.Add(re.sPos - z * height / 2 - y * width / 2);

                        // Add first pt again to get closed curve
                        pts.Add(re.sPos + z * height / 2 + y * width / 2);
                        maxPtsForBB.AddRange(pts);  // Add to maxpts

                        c1 = Curve.CreateInterpolatedCurve(pts, 1);
                        Brep[] b1 = Brep.CreateFromSweep(cl.ToNurbsCurve(), c1, false, Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance);
                        if (b1.Length > 0)
                            sSweeps.Add(b1[0]);

                        // Inner curve
                        maxPtsForBB.AddRange(pts);  // Add to maxpts
                        pts.Clear();
                        pts.Add(re.sPos + z * (height - 2 * thickness) / 2 + y * (width - 2 * thickness) / 2);
                        pts.Add(re.sPos + z * (height - 2 * thickness) / 2 - y * (width - 2 * thickness) / 2);
                        pts.Add(re.sPos - z * (height - 2 * thickness) / 2 + y * (width - 2 * thickness) / 2);
                        pts.Add(re.sPos - z * (height - 2 * thickness) / 2 - y * (width - 2 * thickness) / 2);

                        // Add first pt again to get closed curve
                        pts.Add(re.sPos + z * (height - 2 * thickness) / 2 + y * (width - 2 * thickness) / 2);
                        maxPtsForBB.AddRange(pts);  // Add to maxpts

                        c2 = Curve.CreateInterpolatedCurve(pts, 1);
                        Brep[] b2 = Brep.CreateFromSweep(cl.ToNurbsCurve(), c2, false, Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance);
                        if (b2.Length > 0)
                            sSweeps.Add(b2[0]);

                        sSweeps.Add(Brep.CreateEdgeSurface(new List<Curve> { c1, c2 }));
                        */
                        break;
                    case Utilities.CrossSectionType.CircularSolid:
                    case Utilities.CrossSectionType.CHS:
                    default:
                        throw new NotImplementedException("Error, section type not implemented for display");
                }
            }

            _bb = new BoundingBox(maxPtsForBB);

            return sSweeps;
        }


        public override void DrawViewportMeshes(IGH_PreviewArgs args)
        {
            DrawBreps(args, breps, System.Drawing.Color.DarkBlue);

            // Also, dont create objects, just get the data instead

            base.DrawViewportMeshes(args);
        }

        private void DrawBreps(IGH_PreviewArgs args, List<Brep> breps, System.Drawing.Color color)
        {
            for (int i = 0; i < breps.Count; i++)
                args.Display.DrawBrepWires(breps[i], color);
        }


    }
}
