using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_wrapper;
using Grasshopper.Kernel.Types;

namespace CIFem_grasshopper
{
    public class NodeGoo : GH_Goo<WR_INode>
    {
        public NodeGoo()
        {
            this.Value = new WR_INode();
        }

        public NodeGoo(WR_INode value)
        {
            if (value == null)
                this.Value = new WR_INode();
            else
                this.Value = value;
        }


        public override bool IsValid
        {
            get
            {
                if (Value == null)
                    return false;

                return true;
            }
        }

        public override string TypeDescription
        {
            get
            {
                return "Contains a node";
            }
        }

        public override string TypeName
        {
            get
            {
                return "Node";
            }
        }

        public override IGH_Goo Duplicate()
        {
            return new NodeGoo(Value.Copy());
        }

        public override string ToString()
        {
            return "Node";
        }
    }
}
