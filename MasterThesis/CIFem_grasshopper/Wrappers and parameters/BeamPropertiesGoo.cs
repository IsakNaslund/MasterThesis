using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Grasshopper.Kernel.Types;

namespace CIFem_grasshopper
{
    public class BeamPropertiesGoo : GH_Goo<BeamProperties>
    {

        public BeamPropertiesGoo()
        {
            m_value = new BeamProperties();
        }

        public BeamPropertiesGoo(BeamProperties value)
        {
            m_value = value;
        }

        public override bool IsValid
        {
            get
            {
                //TODO: implement more checks

                if (Value == null)
                    return false;

                return true;
            }
        }

        public override string TypeDescription
        {
            get
            {
                return "Releases, material properties and crosssection for a 3D beam";
            }
        }

        public override string TypeName
        {
            get
            {
                return "Beam properties";
            }
        }

        public override IGH_Goo Duplicate()
        {
            if (this.Value == null)
                return new BeamPropertiesGoo(new BeamProperties());

            return new BeamPropertiesGoo(new BeamProperties(m_value));
        }

        public override string ToString()
        {
            return Value.ToString();
        }

        #region casting methods

        public override bool CastTo<Q>(ref Q target)
        {
            //Cast to BeamProperties.
            if (typeof(Q).IsAssignableFrom(typeof(BeamProperties)))
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

            //Cast from BeamProperties
            if (typeof(BeamProperties).IsAssignableFrom(source.GetType()))
            {
                Value = (BeamProperties)source;
                return true;
            }

            return false;
        }
        #endregion
    }
}
