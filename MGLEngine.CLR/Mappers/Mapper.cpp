#include "Mapper.h"


#include <msclr\marshal_cppstd.h>

using namespace System;
System::String^ Mapper::Map(std::string str)
{
	return gcnew System::String(str.c_str());
}

std::string Mapper::Map(System::String^ str)
{
	return msclr::interop::marshal_as<std::string>(str);
}

System::Exception^ Mapper::Map(std::exception &e)
{
	return gcnew System::Exception(gcnew System::String(e.what()));

}