using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper;
using Grasshopper.Kernel;

using CIFem_wrapper;
using Grasshopper.Kernel.Types;
using Rhino.Geometry;

namespace CIFem_grasshopper
{
    public class BeamGoo : Grasshopper.Kernel.Types.GH_Goo<WR_Elem3dRcp>, IGH_PreviewData
    {
        private Brep _extrusion;
        private Mesh _mesh;

        public BeamGoo()
        {
            this.Value = new WR_Elem3dRcp();
        }

        public BeamGoo(WR_Elem3dRcp value)
        {
            this.Value = value;

            _extrusion = null;
        }

        public override WR_Elem3dRcp Value
        {
            get
            {
                return base.Value;
            }

            set
            {
                base.Value = value;
                _mesh = null;
                _extrusion = null;
            }
        }

        public override bool IsValid
        {
            get
            {
                //TODO inplement some kind of check to see if all wrappers work etc
                if (Value == null)
                    return false;

                return true;
            }
        }

        public override string TypeDescription
        {
            get
            {
                return "3D beam element. Standard element used to build 3d frames";
            }
        }

        public override string TypeName
        {
            get
            {
                return "3d-Beam";
            }
        }

        public override IGH_Goo Duplicate()
        {
            return new BeamGoo(m_value.Copy());
        }

        public override string ToString()
        {
            return "Beam 3d element";
        }

        #region casting methods

        public override bool CastTo<Q>(ref Q target)
        {
            //Cast to WR_Elem3dRcp.
            if (typeof(Q).IsAssignableFrom(typeof(WR_Elem3dRcp)))
            {
                if (Value == null)
                    target = default(Q);
                else
                    target = (Q)(object)Value;
                return true;
            }

            target = default(Q);
            return false;
        }



        public override bool CastFrom(object source)
        {
            if (source == null) { return false; }

            //Cast from WR_Elem3dRcp
            if (typeof(WR_Elem3dRcp).IsAssignableFrom(source.GetType()))
            {
                Value = (WR_Elem3dRcp)source;
                return true;
            }

            return false;
        }

        #endregion


        public BoundingBox ClippingBox
        {
            get
            {
                return new BoundingBox(Value.GetStartPos().ConvertToRhinoPoint(), Value.GetEndPos().ConvertToRhinoPoint());
            }
        }

        public void DrawViewportWires(GH_PreviewWireArgs args)
        {
            // do nothing

            //throw new NotImplementedException();
        }

        public void DrawViewportMeshes(GH_PreviewMeshArgs args)
        {
            if (args.Pipeline.SupportsShading)
            {
                if (this._mesh == null)
                {
                    if (this.m_value == null)
                    {
                        return;
                    }
                    MeshingParameters @params = args.MeshingParameters;
                    if (@params == null)
                    {
                        return;
                    }
                    if (this._extrusion == null)
                    {
                        // Set extrusion
                        List<Brep> breps = Utilities.CreateSectionSweeps(this.Value);
                        _extrusion = Brep.JoinBreps(breps, Rhino.RhinoDoc.ActiveDoc.ModelAbsoluteTolerance)[0];
                    }
                    Mesh[] rc = Mesh.CreateFromBrep(this._extrusion, @params);
                    if (rc == null)
                    {
                        this._mesh = new Mesh();
                    }
                    else if (rc.Length == 1)
                    {
                        this._mesh = rc[0];
                    }
                    else
                    {
                        this._mesh = new Mesh();
                        Mesh[] array = rc;
                        for (int j = 0; j < array.Length; j++)
                        {
                            Mesh i = array[j];
                            this._mesh.Append(i);
                        }
                    }
                }
                if (this._mesh == null)
                {
                    return;
                }
                args.Pipeline.DrawMeshShaded(this._mesh, args.Material);
            }
        }
    }
}
