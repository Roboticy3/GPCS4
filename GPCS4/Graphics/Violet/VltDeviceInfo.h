#pragma once

#include "VltCommon.h"

namespace sce::vlt
{
	/**
     * \brief Device info
     * 
     * Stores core properties and a bunch of extension-specific
     * properties, if the respective extensions are available.
     * Structures for unsupported extensions will be undefined,
     * so before using them, check whether they are supported.
     */
	struct VltDeviceInfo
	{
		VkPhysicalDeviceProperties2                            core;
		VkPhysicalDeviceIDProperties                           coreDeviceId;
		VkPhysicalDeviceSubgroupProperties                     coreSubgroup;
		VkPhysicalDeviceConservativeRasterizationPropertiesEXT extConservativeRasterization;
		VkPhysicalDeviceCustomBorderColorPropertiesEXT         extCustomBorderColor;
		VkPhysicalDeviceRobustness2PropertiesEXT               extRobustness2;
		VkPhysicalDeviceTransformFeedbackPropertiesEXT         extTransformFeedback;
		VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT    extVertexAttributeDivisor;
		VkPhysicalDeviceDepthStencilResolvePropertiesKHR       khrDepthStencilResolve;
		VkPhysicalDeviceDriverPropertiesKHR                    khrDeviceDriverProperties;
		VkPhysicalDeviceFloatControlsPropertiesKHR             khrShaderFloatControls;
	};

	/**
     * \brief Device features
     * 
     * Stores core features and extension-specific features.
     * If the respective extensions are not available, the
     * extended features will be marked as unsupported.
     */
	struct VltDeviceFeatures
	{
		VkPhysicalDeviceFeatures2                                 core;
		VkPhysicalDeviceVulkan11Features                          vk11;
		VkPhysicalDeviceVulkan12Features                          vk12;
		VkPhysicalDeviceVulkan13Features                          vk13;
		VkPhysicalDevice4444FormatsFeaturesEXT                    ext4444Formats;
		VkPhysicalDeviceCustomBorderColorFeaturesEXT              extCustomBorderColor;
		VkPhysicalDeviceDepthClipEnableFeaturesEXT                extDepthClipEnable;
		VkPhysicalDeviceExtendedDynamicStateFeaturesEXT           extExtendedDynamicState;
		VkPhysicalDeviceHostQueryResetFeaturesEXT                 extHostQueryReset;
		VkPhysicalDeviceMemoryPriorityFeaturesEXT                 extMemoryPriority;
		VkPhysicalDeviceRobustness2FeaturesEXT                    extRobustness2;
		VkPhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT extShaderDemoteToHelperInvocation;
		VkPhysicalDeviceTransformFeedbackFeaturesEXT              extTransformFeedback;
		VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT         extVertexAttributeDivisor;
		VkPhysicalDeviceBufferDeviceAddressFeaturesKHR            khrBufferDeviceAddress;
	};
}  // namespace sce::vlt