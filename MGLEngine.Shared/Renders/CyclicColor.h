#pragma once
#include <glm/detail/type_vec3.hpp>
#include <vector>
#include "../Shapes/IRender.h"
#include "../Utils/Arrays/IArray.h"

template<class VerticeData>
class CyclicColor : public IRender<VerticeData>
{
	std::vector<glm::vec3> _colors;
public:
	virtual void Write(IArray<VerticeData> &array) override;
	CyclicColor(const std::vector<glm::vec3>& colors) { _colors = colors; };
	virtual ~CyclicColor() override {};
};

template <class VerticeData>
void CyclicColor<VerticeData>::Write(IArray<VerticeData>& array)
{
	auto size = _colors.size();
	for (int i=0;i<array.size();i++)
	{
		array[i].Color = _colors[i%size];
	}
}

