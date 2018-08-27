using System;

namespace TestApp.Services.Interfaces
{
    public interface IAppStore : IDisposable
    {
        T LoadIfExists<T>(string section);
        void Open(string fileName);
        void Save(string section, object value);
    }
}