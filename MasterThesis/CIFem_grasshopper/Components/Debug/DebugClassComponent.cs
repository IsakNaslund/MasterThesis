using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Grasshopper.Kernel;

namespace CIFem_grasshopper.Debug
{
    class DebugClassComponent : GH_Component
    {
        public DebugClassComponent(): base("Debug Class component", "Debug", "A component used for debugging", "CIFem", "Debug")
        { }

        public override Guid ComponentGuid
        {
            get
            {
                return new Guid("3ebc3951-6450-4b16-a44f-b6ade2bb4d75");
            }
        }

        protected override void RegisterInputParams(GH_InputParamManager pManager)
        {
            pManager.AddIntegerParameter("Integer", "I", "An integer", GH_ParamAccess.item);
            pManager.AddBooleanParameter("CrazyException", "Ex", "Throws an exception from C++", GH_ParamAccess.item);
            pManager.AddBooleanParameter("Boolean", "B", "A boolean", GH_ParamAccess.item);
        }

        protected override void RegisterOutputParams(GH_OutputParamManager pManager)
        {
            pManager.AddTextParameter("Message", "M", "Records messages from the component", GH_ParamAccess.item);
        }

        protected override void SolveInstance(IGH_DataAccess DA)
        {
            int i = -1;

            if (DA.GetData(0, ref i))
            {
                CIFem_wrapper.WR_DebugClass debug = new CIFem_wrapper.WR_DebugClass();

                try
                {
                    debug.DivByZero(i);
                }
                catch (DivideByZeroException e)
                {
                    string s = "gotcha!";
                    throw e;
                }
            }


            bool ce = false;
            if (DA.GetData(1, ref ce) && ce)
            {
                CIFem_wrapper.WR_DebugClass debug = new CIFem_wrapper.WR_DebugClass();

                try
                {
                    debug.ThrowCrazyException();
                }
                catch (Exception e)
                {
                    AddRuntimeMessage(GH_RuntimeMessageLevel.Error, e.Message);
                    //throw;
                }
            }

            bool b = false;
            if (DA.GetData(2, ref b) && b)
            {
                CIFem_wrapper.WR_DebugClass debug = new CIFem_wrapper.WR_DebugClass();

                debug.ThrowCrazyException();
            }
        }
    }
}
