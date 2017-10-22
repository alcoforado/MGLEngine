using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace MUtils.Reflection
{
    static public class Extension
    {
        //Go throw all public properties of src and assign to dst
        //if the values are not null.
        public static void CopyPublicPropertiesFrom(this object dst, object src)
        {

            var srcProperties = TypeDescriptor.GetProperties(src.GetType()).Cast<PropertyDescriptor>();
            var dstProperties = TypeDescriptor.GetProperties(dst.GetType()).Cast<PropertyDescriptor>();

            foreach (var dstP in dstProperties)
            {
                var srcP = srcProperties.FirstOrDefault(prop => prop.Name == dstP.Name);
               
                if (srcP != null )
                {
                    var value = srcP.GetValue(src);
                    if (value!=null)
                        dstP.SetValue(dst, Convert.ChangeType(value, dstP.PropertyType));
                }
            
            }

        }

        public static List<Type>  GetImplementationsInCurrentAssembly(this Type type)
        {
            
            var result = new List<Type>();
            foreach (var t in Assembly.GetCallingAssembly().GetTypes())
            {
                if (!t.IsAbstract && !t.IsInterface && type.IsAssignableFrom(t))
                {
                    result.Add(t);
                }
            }
            return result;
        }

        public static List<Type> GetImplementationsInAssembly(this Type type,Assembly assembly)
        {

            var result = new List<Type>();
            foreach (var t in assembly.GetTypes())
            {
                if (!t.IsAbstract && !t.IsInterface && type.IsAssignableFrom(t))
                {
                    result.Add(t);
                }
            }
            return result;
        }


        public static List<Type> GetTypesInNamespace(this Assembly assembly,string nameSpace)
        {

            var result = new List<Type>();
            foreach (var t in assembly.GetTypes())
            {
                if (!t.IsAbstract && !t.IsInterface && t.Namespace == nameSpace)
                {
                    result.Add(t);
                }
            }
            return result;
        }

    }
}
