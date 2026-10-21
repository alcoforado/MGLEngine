#include <vector>
#include <array>

template<typename T,size_t N>
void add_offset(std::array<T, N>& v,T offset)
{
	for (auto it = v.begin();it!=v.end();it++)
	{
		*it+=offset;
	}
}