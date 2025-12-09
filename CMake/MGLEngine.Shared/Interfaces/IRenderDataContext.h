#pragma once
#include <map>
#include <string>
#include <MGLEngine.Shared/Utils/Arrays/InterleavedMemoryStream.h>
#include <MGLEngine.Shared/Utils/Arrays/IndicesMemoryStream.h>
class IRenderDataContext
{
public:
	 virtual InterleavedMemoryStream& GetVerticeAttribute(std::string name)=0;
	 virtual IndicesMemoryStream& GetIndicesStream()=0;

};