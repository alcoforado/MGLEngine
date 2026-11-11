#pragma once
#include "Std140Types.h"
#include <MGLEngine.Shared/Shaders/ShaderConfiguration.h>
enum Bindings {

COLOR2D_MATRIX=6,
CAMERA_TRANSFORM=7


};



class UboBindingCollection
{
public:
	static inline  StaticUboConfig<Std140Mat2> Mat2Transform = {
		.binding = 6,
		.name = "Transform2D",
		.frequency = FrequencyUsage::PER_FRAME,
		.stage=ShaderStage::VERTEX_STAGE
	};

	static inline  StaticUboConfig<Std140Mat4> CameraTransform = {
		.binding = 7,
		.name = "CameraTransform",
		.frequency = FrequencyUsage::PER_FRAME,
		.stage = ShaderStage::VERTEX_STAGE
	};

	


};




