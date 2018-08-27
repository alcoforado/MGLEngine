using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using TestApp.Services.Interfaces;

namespace MGLEngine.Server.Services
{
    public class JsonFileStore : IAppStore
    {
        private JObject _store;
        private JsonSerializer _serializer;
        private JsonSerializerSettings _settings;
            
        private string _fileName;
        public JsonFileStore()
        {
            _store = null;
            _settings = new JsonSerializerSettings()
            {
                TypeNameHandling = TypeNameHandling.Objects
            };
            _serializer = JsonSerializer.Create(_settings);
        }

        public void Open(string fileName)
        {
            _fileName = fileName;
            string content = "";

            content = !File.Exists(fileName) ? "{}" : File.ReadAllText(fileName);
        
            _store=JObject.Parse(content);


        }

        private void AssertStoreWasOpenned()
        {
            if (_store == null)
            {
                throw new Exception("Store not opened");
            }
        }


        public void Save(string section, object value)
        {

            AssertStoreWasOpenned();
            var sectionToken = _store[section];
            _store[section] = JToken.FromObject(value, _serializer);
        }

        public T LoadIfExists<T>(string section)
        {
            AssertStoreWasOpenned();
            var sectionToken = _store[section];
            if (sectionToken == null)
                return default(T);
            var obj = JsonConvert.DeserializeObject<T>(sectionToken.ToString(),_settings);
            return obj;
        }

        public JObject GetRoot()
        {
            return _store;
        }
       

        public void Dispose()
        {
            if (_store != null)
            {
                var json = _store.ToString();
                File.WriteAllText(_fileName,json);
            }
        }
    }
}
