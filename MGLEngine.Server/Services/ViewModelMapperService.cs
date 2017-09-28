using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MGLEngine.Server.Models;
using MGLEngine.Server.Services.Interfaces;

namespace MGLEngine.Server.Services
{
    public class ViewModelMapperService : IViewModelMapperService
    {
        private Dictionary<string, string> typeMapping = new Dictionary<string, string>()
        {
            {"System.Single", "float"},
            {"System.Int32","int" },
            {"System.String","string" }
        };




        public string GetLabelNameFromFieldName(string fieldName)
        {


            var array = fieldName.ToCharArray();
            array[0] = Char.ToUpper(array[0]);
            var result = "";
            foreach (var ch in array)
            {
                if (Char.IsUpper(ch))
                {
                    result += ' ';

                }
                result += ch;

            }
            var str = result.Trim();
            return str;

        }

        public TypeViewModel ToUITypeDto(string name, Type type)
        {

            var tt = type.GetProperties().Select(p =>
                new TypeMemberViewModel()
                {
                    FieldName = p.Name,
                    LabelName = this.GetLabelNameFromFieldName(p.Name),
                    DirectiveType = this.MapTypeWithJavascriptRender(p.PropertyType)

                }
            ).ToList();
            return new TypeViewModel()
            {
                Members = tt,
                TypeName = name,
                TypeLabel = this.GetLabelNameFromFieldName(name)
            };

        }

        public string MapTypeWithJavascriptRender(Type propertyType)
        {
            if (typeMapping.ContainsKey(propertyType.FullName))
                return typeMapping[propertyType.FullName];
            else
                return propertyType.Name;

        }


    }
}
