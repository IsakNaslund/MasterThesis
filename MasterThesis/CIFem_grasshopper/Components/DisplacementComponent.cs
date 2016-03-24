using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;



using Grasshopper.Kernel;
using Rhino.Geometry;

namespace CIFem_grasshopper
{
    public class DisplacementComponent : GH_Component
    {

        List<Curve> _dispCrvs;
        BoundingBox _bb;

        public DisplacementComponent() : base("Element displacement", "eDisp", "Displays the displacement of the elements", "CIFem", "Results")
        {
            _dispCrvs = new List<Curve>();
            _bb = new BoundingBox();
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("ac587a53-5152-4af4-ae66-717af162a143");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddParameter(new ResultElementParam(), "Result Element", "RE", "Result element", GH_ParamAccess.list);
            pManager.AddNumberParameter("Scale factor", "s", "The displacement scale", GH_ParamAccess.item, 10);
            pManager.AddTextParameter("Load Comb", "LC", "Load combination to display results from", GH_ParamAccess.item);

            pManager[2].Optional = true;
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {

            pManager.AddCurveParameter("Displacement Curves", "C", "Displacement curve", GH_ParamAccess.list);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            List<ResultElement> res = new List<ResultElement>();
            double sFac = double.NaN;
            string name = null;

            if (!DA.GetDataList(0, res)) { return; }
            if (!DA.GetData(1, ref sFac)) { return; }
            if(!DA.GetData(2, ref name))
            {
                if(res.Count>0)
                {
                    name = res[0].N1.First().Key;
                }
            }

            _dispCrvs.Clear();

            Point3d stPos, enPos;
            Vector3d norm, tan, yDir;

            List<Point3d> allPts = new List<Point3d>();

            foreach (ResultElement re in res)
            {
                stPos = re.sPos;
                enPos = re.ePos;
                norm = re.elNormal;

                norm.Unitize();

                tan = enPos - stPos;
                tan.Unitize();

                yDir = Vector3d.CrossProduct(norm, tan);
                yDir.Unitize();

                List<Point3d> curvePts = new List<Point3d>();

                int nbEval = re.pos.Count;

                for (int i = 0; i < nbEval; i++)
                {
                    Point3d curvePt = stPos + tan * (re.pos[i]+re.u[name][i]* sFac) +norm*re.w[name][i]* sFac + yDir*re.v[name][i]* sFac;
                    curvePts.Add(curvePt);
                    allPts.Add(curvePt);
                }


                _dispCrvs.Add(Rhino.Geometry.Curve.CreateInterpolatedCurve(curvePts, 3));
            }

            _bb = new BoundingBox(allPts);

            DA.SetDataList(0, _dispCrvs);
        }


        /*public override void DrawViewportWires(IGH_PreviewArgs args)
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
                return base.ClippingBox;
            }
        }*/
    }
}
