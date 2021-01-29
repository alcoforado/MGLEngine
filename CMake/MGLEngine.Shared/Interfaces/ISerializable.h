#pragma once
#include <string>
#include <MGLEngine.Shared/Utils/JsonParser/mjson.h>
class ISerializable
{
public:
	virtual ~ISerializable() = default;
	virtual std::string Serialize()=0;
	virtual void Deserialize(std::string str) = 0;


};
