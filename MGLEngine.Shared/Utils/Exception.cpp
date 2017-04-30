#include "Exception.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


Exception::Exception(const char *format,...)
{
  char str[2000];
  va_list vl;
  va_start(vl,format);
  vsprintf_s(str,format,vl);
  va_end(vl);
  m_error = str;



}


