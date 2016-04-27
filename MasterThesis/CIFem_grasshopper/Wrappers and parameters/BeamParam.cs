using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel.Types;
using Grasshopper.Kernel;
using Rhino.Geometry;

namespace CIFem_grasshopper
{
    public class BeamParam : Grasshopper.Kernel.GH_Param<BeamGoo>, IGH_PreviewObject
    {

        private bool _hidden;

        public BeamParam():base(new GH_InstanceDescription("3d beam", "3db", "3d beam used in frame structures","CIFem","Elements"))
        {
            _hidden = false;
        }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("71f3db8f-7b0d-4b3e-9b36-9f6d25766712");
            }
        }

        public BoundingBox ClippingBox
        {
            get
            {
                return Preview_ComputeClippingBox();
            }
        }

        public override GH_Exposure Exposure
        {
            get
            {
                return GH_Exposure.hidden;
            }
        }

        public bool Hidden
        {
            get
            {
                return this._hidden;
            }

            set
            {
                _hidden = value;
            }
        }

        public bool IsPreviewCapable
        {
            get
            {
                return true;
            }
        }

        public void DrawViewportMeshes(IGH_PreviewArgs args)
        {
            if (args.Document.PreviewMode == GH_PreviewMode.Shaded && args.Display.SupportsShading)
            {
                this.Preview_DrawMeshes(args);
            }
        }

        public void DrawViewportWires(IGH_PreviewArgs args)
        {
            switch (args.Document.PreviewMode)
            {
                case GH_PreviewMode.Wireframe:
                    this.Preview_DrawWires(args);
                    break;
                case GH_PreviewMode.Shaded:
                    if (Grasshopper.CentralSettings.PreviewMeshEdges)
                    {
                        this.Preview_DrawWires(args);
                    }
                    break;
            }
        }
    }
}
