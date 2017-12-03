using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Security.AccessControl;
using System.Text;
using System.Threading.Tasks;

namespace MUtils.Reflection
{
    public class DynamicCaller<T>
    {
        static Dictionary<string,MethodInfo> _reflectionDictionary = new Dictionary<string, MethodInfo>();
        public DynamicCaller()
        {
            

            if (_reflectionDictionary.Count() == 0)
            {
                lock (_reflectionDictionary)
                {
                    if (_reflectionDictionary.Count != 0)
                        return;
                    foreach (var f in typeof(T).GetMethods())
                    {
                        string str = GetMethodHash(f);
                        _reflectionDictionary[str]=f;
                    }
                }
            }
        }

       



        private string GetMethodHash(MethodInfo methodInfo)
        {
            var str = $"{methodInfo.Name}";
            foreach (var param in methodInfo.GetParameters())
            {
                str += "#" + param.ParameterType.Name;
            }
            return str;

        }
    }
}
