using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MGLEngine.Server.App_Start
{
    public class UserException : Exception
    {
        public List<string> Errors { get; private set; }

        UserException()
        {
            Errors = new List<string>();
        }

        UserException AddError(string error)
        {   
            Errors.Add(error);
            return this;
        }

        UserException AddErrors(List<string> error)
        {
            if (error != null)
                Errors.AddRange(error);
            return this;
        }


    }
}
