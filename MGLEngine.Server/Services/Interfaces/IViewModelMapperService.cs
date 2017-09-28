using System;
using MGLEngine.Server.Models;

namespace MGLEngine.Server.Services.Interfaces
{
    public interface IViewModelMapperService
    {
        string GetLabelNameFromFieldName(string fieldName);
        string MapTypeWithJavascriptRender(Type propertyType);
        TypeViewModel ToUITypeDto(string name, Type type);
    }
}