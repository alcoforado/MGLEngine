#pragma once
struct ArrayLocation
{
	size_t OffI;
	size_t SizeI;
	size_t OffV;
	size_t SizeV;
};


class DrawInfo
{
public:
	
	ArrayLocation Current;
	ArrayLocation Future;
	bool NeedRedraw;
	

	DrawInfo();
	~DrawInfo();
};

