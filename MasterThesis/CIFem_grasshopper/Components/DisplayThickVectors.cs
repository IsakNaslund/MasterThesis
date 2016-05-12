using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using Grasshopper.Kernel;
using Rhino.Geometry;


namespace CIFem_grasshopper.Components
{
    class DisplayThickVectors : GH_Component
    {

        private struct DisplayVector
        {
            public Point3d Point;

            public Vector3d Vector;

            public System.Drawing.Color Colour;

            public int Width;
        }

        private List<DisplayVector> _vectors;

        private BoundingBox _bounds;

        public DisplayThickVectors():base("VectorDisplay", "VDisp", "Displays a vector with set thickness", "CIFem", "Utilities")
        {
            //_vectors = new List<Vector3d>();
            _vectors = new List<DisplayVector>();
            _bounds = BoundingBox.Unset;
        }


        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("56d1f0ff-f40f-4abe-b525-58eb7090fdc3");
            }
        }

        public override BoundingBox ClippingBox
        {
            get
            {
                return _bounds;
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddPointParameter("Anchor Point", "A", "Anchor point for preview vector", GH_ParamAccess.item);
            pManager.AddVectorParameter("Vector", "V", "Vector to display", GH_ParamAccess.item);
            pManager.AddColourParameter("Colour", "C", "Colour of vector", GH_ParamAccess.item, Color.Black);
            pManager.AddIntegerParameter("Thickness", "T", "Thickness of display vector", GH_ParamAccess.item, 1);
        }

        public override bool IsPreviewCapable
        {
            get
            {
                return true;
            }
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            if (DA.Iteration == 0)
            {
                _vectors = new List<DisplayVector>();
                _bounds = BoundingBox.Unset;
            }

            Point3d point = Point3d.Unset;
            Vector3d vector = Vector3d.Unset;
            Color colour = Color.Black;
            int width = 1;

            if (!DA.GetData(0, ref point)) { return; }
            if (!DA.GetData(1, ref vector)) { return; }
            if (!DA.GetData(2, ref colour)) { return; }
            if (!DA.GetData(3, ref width)) { return; }

            DisplayVector dispVec = new DisplayVector();
            dispVec.Colour = colour;
            dispVec.Point = point;
            dispVec.Vector = vector;
            dispVec.Width = width;


            _vectors.Add(dispVec);
            _bounds.Union(point);
            _bounds.Union((Point3d)(point + vector));
            
        }


        public override void DrawViewportWires(IGH_PreviewArgs args)
        {
            if (Locked)
                return;

            if (_vectors == null)
                return;

            for (int i = 0; i < _vectors.Count; i++)
            {

            }

            
        }

        public override void DrawViewportMeshes(IGH_PreviewArgs args)
        {
        }
    }
}
