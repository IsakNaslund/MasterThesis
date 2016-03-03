using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_wrapper;
using Grasshopper.Kernel.Types;

namespace CIFem_grasshopper
{
    public class MaterialGoo : GH_Goo<WR_Material>
    {

        public MaterialGoo()
        {
            Value = new WR_Material();
        }

        public MaterialGoo(WR_Material mat)
        {
            if (mat == null)
                Value = new WR_Material();
            else
                Value = mat;

        }

        public override bool IsValid
        {
            get
            {
                //TODO: More Checks!

                if (Value == null)
                    return false;


                return true;
            }
        }

        public override string TypeDescription
        {
            get
            {
                return "A material";
            }
        }

        public override string TypeName
        {
            get
            {
                return "Material";
            }
        }

        public override IGH_Goo Duplicate()
        {
            if (Value == null)
                return new MaterialGoo();

            return new MaterialGoo(Value.Copy());
        }

        public override string ToString()
        {
            return Value.ToString();
        }


        #region casting methods

        public override bool CastTo<Q>(ref Q target)
        {
            //Cast to WR_Material.
            if (typeof(Q).IsAssignableFrom(typeof(WR_Material)))
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

            //Cast from WR_Material
            if (typeof(WR_Material).IsAssignableFrom(source.GetType()))
            {
                Value = (WR_Material)source;
                return true;
            }

            return false;
        }

        #endregion
    }
}
