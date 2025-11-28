#include <vulkan/vulkan.h>




class VulkanSurfaceCapability : VkSurfaceCapabilitiesKHR
{
	ImageUsage imageUsagesCapabilities;
	SurfaceTransforms surfaceTransformsCapabilities;
	CompositeAlpha compositeAlphaCapabilities;

	VulkanSurfaceCapability(const VkSurfaceCapabilitiesKHR& vk)
		:imageUsagesCapabilities(vk.supportedUsageFlags),
		 surfaceTransformsCapabilities(vk.supportedTransforms),
		 compositeAlphaCapabilities(vk.supportedCompositeAlpha)
	{
		*this = vk;
	}
};

struct ImageUsage {
	bool TransferSrc;
	bool TransferDst;
	bool Sampled;
	bool Storage;
	bool ColorAttachment;
	bool DepthStencil;
	bool TransientAttachment;
	bool InputAttachment;
	bool HostTransfer;
	bool VideoDecodeDst;
	bool VideoDecodeSrc;
	bool VideoDecodeDpb;
	bool FragmentDensityMap;
	bool FragmentShadingRateAttachment;
	bool VideoEncodeDst;
	bool VideoEncodeSrc;
	bool VideoEncodeDpb;
	bool AttachmentFeedbackLoop;
	bool InvocationMaskHuawei;
	bool SampleWeightQCom;
	bool SampleBlockMatch;
	bool TensorAliasingArm;
	bool TileMemoryQCom;
	bool EncodeQuantizationMap;
	bool VideoEncodeEmphasisMap;
	bool ShadingRateImage;
	bool HostTransfer;

	ImageUsage(VkImageUsageFlags flags)
	{
		TransferSrc = (VK_IMAGE_USAGE_TRANSFER_SRC_BIT & flags) == VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
		TransferDst = (VK_IMAGE_USAGE_TRANSFER_DST_BIT & flags) == VK_IMAGE_USAGE_TRANSFER_DST_BIT;
		Sampled = (VK_IMAGE_USAGE_SAMPLED_BIT & flags) == VK_IMAGE_USAGE_SAMPLED_BIT;
		Storage = (VK_IMAGE_USAGE_STORAGE_BIT & flags) == VK_IMAGE_USAGE_STORAGE_BIT;
		ColorAttachment = (VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT & flags) == VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		DepthStencil = (VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT & flags) == VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
		TransientAttachment = (VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT & flags) == VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT;
		InputAttachment = (VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT & flags) == VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;
		HostTransfer = (VK_IMAGE_USAGE_HOST_TRANSFER_BIT & flags) == VK_IMAGE_USAGE_HOST_TRANSFER_BIT;
		VideoDecodeDst = (VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR & flags) == VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR;
		VideoDecodeSrc = (VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR & flags) == VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR;
		VideoDecodeDpb = (VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR & flags)  ==VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR;
		FragmentDensityMap = (VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT & flags) == VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT;
		FragmentShadingRateAttachment = (VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR & flags) == VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR;
		VideoEncodeDst = (VK_IMAGE_USAGE_VIDEO_ENCODE_DST_BIT_KHR & flags) == VK_IMAGE_USAGE_VIDEO_ENCODE_DST_BIT_KHR;
		VideoEncodeSrc = (VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR & flags) == VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR;
		VideoEncodeDpb = (VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR & flags) == VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR;
		AttachmentFeedbackLoop = (VK_IMAGE_USAGE_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT & flags) == VK_IMAGE_USAGE_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT;
		InvocationMaskHuawei = (VK_IMAGE_USAGE_INVOCATION_MASK_BIT_HUAWEI & flags) == VK_IMAGE_USAGE_INVOCATION_MASK_BIT_HUAWEI;
		SampleWeightQCom = (VK_IMAGE_USAGE_SAMPLE_WEIGHT_BIT_QCOM & flags) == VK_IMAGE_USAGE_SAMPLE_WEIGHT_BIT_QCOM;
		SampleBlockMatch = (VK_IMAGE_USAGE_SAMPLE_BLOCK_MATCH_BIT_QCOM & flags) == VK_IMAGE_USAGE_SAMPLE_BLOCK_MATCH_BIT_QCOM;
		TensorAliasingArm = (VK_IMAGE_USAGE_TENSOR_ALIASING_BIT_ARM & flags) == VK_IMAGE_USAGE_TENSOR_ALIASING_BIT_ARM;
		TileMemoryQCom = (VK_IMAGE_USAGE_TILE_MEMORY_BIT_QCOM & flags) == VK_IMAGE_USAGE_TILE_MEMORY_BIT_QCOM;
		EncodeQuantizationMap = (VK_IMAGE_USAGE_VIDEO_ENCODE_QUANTIZATION_DELTA_MAP_BIT_KHR & flags) == VK_IMAGE_USAGE_VIDEO_ENCODE_QUANTIZATION_DELTA_MAP_BIT_KHR;
		VideoEncodeEmphasisMap = (VK_IMAGE_USAGE_VIDEO_ENCODE_EMPHASIS_MAP_BIT_KHR & flags) == VK_IMAGE_USAGE_VIDEO_ENCODE_EMPHASIS_MAP_BIT_KHR;
		ShadingRateImage = (VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV & flags) == VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV;
		HostTransfer = (VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT & flags) == VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT;
	}
};

struct SurfaceTransforms
{
	bool Identity;
	bool Rotate90;
	bool Rotate180;
	bool Rotate270;
	bool HorizontalMirror;
	bool HorizontalMirrorRotate90;
	bool HorizontalMirrorRotate180;
	bool HorizontalMirrorRotate270;
	bool Inherit;

	VkSurfaceTransformFlagsKHR flag;
	SurfaceTransforms(VkSurfaceTransformFlagsKHR flag)
	{
		Identity = (VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR & flag) != VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		Rotate90 = (VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR & flag) != VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR;
		Rotate180 = (VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR & flag) != VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR;
		Rotate270 = (VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR & flag) != VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR;
		HorizontalMirror = (VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR & flag) != VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR;
		HorizontalMirrorRotate90 = (VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR & flag) != VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR;
		HorizontalMirrorRotate180 = (VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR & flag) != VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR;
		HorizontalMirrorRotate270 = (VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR & flag) != VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR;
		Inherit = (VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR & flag) != VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR;
	}
};

struct CompositeAlpha {
	bool Opaque;
	bool PreMultiplied;
	bool PostMultiplied;
	bool Inherit;
	CompositeAlpha(VkCompositeAlphaFlagsKHR flags)
	{
		Opaque = (flags & VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR) == VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		PreMultiplied = (flags & VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR) == VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR;
		PostMultiplied = (flags & VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR) == VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR;
		Inherit = (flags & VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR) == VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;
	}
};
