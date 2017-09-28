using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MGLEngine.Server.Models
{
    public class TypeViewModel
    {
        public string TypeName;
        public List<TypeMemberViewModel> Members;
        public string TypeLabel;
    }

    public class TypeMemberViewModel
    {
        public string FieldName { get; set; }
        public string LabelName { get; set; }
        public string DirectiveType { get; set; }
    }

    
}
