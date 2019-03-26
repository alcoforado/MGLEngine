#pragma once



#include <string>
class std::exception;

namespace MGLEngineCLR {
	ref class Mapper
	{


	public:
		static System::String^ Map(std::string str);

		static std::string Map(System::String^ str);

		static System::Exception^ Map(std::exception &e);


	};

}