#include <cstdint>
class IDrawingObject
{
	public:
		virtual uint32_t numberOfVertices() = 0;
		virtual uint32_t numberOfIndices() = 0;

		virtual ~IDrawingObject() {}
	virtual void Draw() = 0;
};