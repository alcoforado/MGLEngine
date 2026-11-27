#include <exception>
#include <iostream>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Shared/Mesh/OrthoRect2D.h>
#include <MGLEngine.Shared/Shaders/Color2D/VertexColor2D.h>
#include <MGLEngine.Shared/Shaders/Texture2D/Sprite2D.h>
#include <MGLEngine.Shared/Shaders/TextBox/TextBox.h>
#include <MGLEngine.Shared/Utils/Exception.h>
#include <MGLEngine.Shared/AppBuilder.h>
#include <MGLEngine.Shared/Utils/glm_extensions.h>
#include <MGLEngine.Shared/Utils/math.h>
#include <MGLEngine.Shared/Shaders/BindingConstants.h>
#include <MGLEngine.Shared/Mesh/OrthoBox3D.h>
#include <MGLEngine.Shared/Shaders/Color3D/VertexColor3D.h>
#include <MGLEngine.Shared/Shaders/ColorPalette.h>
#include <MGLEngine.Shared/Shaders/PhongLight/PhongLight.h>
#include <MGLEngine.Shared/Mesh/OrthoBox3DN.h>

void Example6(MGLEngine& engine)
{
	auto cube = OrthoBox3DN(1, 1, 1);
	auto rectDraw = PhongLight(engine, cube, { 
		ColorPalette::Green,ColorPalette::Green,ColorPalette::Green,ColorPalette::Green,
		ColorPalette::Red,ColorPalette::Red,ColorPalette::Red,ColorPalette::Red,
		ColorPalette::Blue,ColorPalette::Blue,ColorPalette::Blue,ColorPalette::Blue,
		ColorPalette::Purple,ColorPalette::Purple,ColorPalette::Purple,ColorPalette::Purple,
		ColorPalette::Yellow,ColorPalette::Yellow,ColorPalette::Yellow,ColorPalette::Yellow,
		ColorPalette::Orange,ColorPalette::Orange,ColorPalette::Orange,ColorPalette::Orange
		});

	engine.Run();
}
