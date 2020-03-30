#pragma once
#include <string>

class ISerializable
{
public:
	virtual ~ISerializable() = default;
	virtual std::string Serialize()=0;
	virtual void Deserialize(std::string str) = 0;


};
