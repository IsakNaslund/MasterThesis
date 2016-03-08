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
        public List<double> N1 { get; private set; }
        public List<double> Vy { get; private set; }
        public List<double> Vz { get; private set; }
        public List<double> T { get; private set; }
        public List<double> My { get; private set; }
        public List<double> Mz { get; private set; }

        public List<double> u { get; private set; }
        public List<double> v { get; private set; }
        public List<double> w { get; private set; }
        public List<double> fi { get; private set; }
        public List<int> pos { get; private set; }

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
