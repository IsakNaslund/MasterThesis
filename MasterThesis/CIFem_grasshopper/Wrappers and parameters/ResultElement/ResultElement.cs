using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using CIFem_wrapper;

namespace CIFem_grasshopper
{
    public class ResultElement
    {


        public ResultElement()
        {
            
        }

        public ResultElement(WR_Element3d elem)
        {
            
        }

        public ResultElement Copy()
        {
            //TODO fix this
            return new ResultElement();
        }
    }
}
