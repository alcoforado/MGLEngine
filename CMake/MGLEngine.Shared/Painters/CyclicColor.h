#pragma once
#include <glm/detail/type_vec3.hpp>
#include <vector>
#include <MGLEngine.Shared/Interfaces/IShaderDataWriter.h>
#include "../Utils/Arrays/IArray.h"

template<class VerticeData>
class CyclicColor : public IShaderDataWriter<VerticeData>
{
protected:
	std::vector<glm::vec3> Colors;
public:
	virtual void Write(IArray<VerticeData> &array) override;
	CyclicColor(const std::vector<glm::vec3>& colors) { Colors = colors; };
	CyclicColor(){}
	virtual ~CyclicColor() override {}


	
};

template <class VerticeData>
void CyclicColor<VerticeData>::Write(IArray<VerticeData>& array)
{
	auto size = Colors.size();
	for (int i=0;i<array.size();i++)
	{
		array[i].Color = Colors[i%size];
	}
}

