﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MGLEngine.Managed.Renders
{
    public interface IRender2D
    {
        void Validate(List<string> errors);
    }
}
