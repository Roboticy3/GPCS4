#pragma once

#include "VltCommon.h"
#include "VltCmdList.h"
#include "VltBarrier.h"
#include "VltContextState.h"

namespace sce::vlt
{
	class VltDevice;
	class VltImage;
	class VltObjects;

	/**
     * \brief DXVk context
     * 
     * Tracks pipeline state and records command lists.
     * This is where the actual rendering commands are
     * recorded.
     */
	class VltContext : public RcObject
	{
	public:
		VltContext(VltDevice* device);
		virtual ~VltContext();

	    /**
         * \brief Begins command buffer recording
         * 
         * Begins recording a command list. This does
         * not alter any context state other than the
         * active command list.
         * \param [in] cmdList Target command list
         */
		void beginRecording(
			const Rc<VltCommandList>& cmdList);

		/**
         * \brief Ends command buffer recording
         * 
         * Finishes recording the active command list.
         * The command list can then be submitted to
         * the device.
         * 
         * This will not change any context state
         * other than the active command list.
         * \returns Active command list
         */
		Rc<VltCommandList> endRecording();


        /**
         * \brief Sets render targets
         * 
         * \param [in] slot Slot number
         * \param [in] targets Render targets to bind
         */
		void bindRenderTarget(
			uint32_t             slot,
			const VltAttachment& target);

        /**
         * \brief Sets depth render targets
         * 
         * \param [in] targets Render targets to bind
         */
		void bindDepthRenderTarget(
			const VltAttachment& depthTarget);


        /**
         * \brief Binds a shader to a given state
         * 
         * \param [in] stage Target shader stage
         * \param [in] shader The shader to bind
         */
		void bindShader(
			VkShaderStageFlagBits stage,
			const Rc<VltShader>&  shader);

        /**
         * \brief Transforms image subresource layouts
         * 
         * \param [in] dstImage Image to transform
         * \param [in] dstSubresources Subresources
         * \param [in] srcLayout Current layout
         * \param [in] dstLayout Desired layout
         */
		void transformImage(
			const Rc<VltImage>&            dstImage,
			const VkImageSubresourceRange& dstSubresources,
			VkImageLayout                  srcLayout,
			VkImageLayout                  dstLayout);

        /**
         * \brief Transforms image subresource layouts
         */
		void transformImage(
			const Rc<VltImage>&            dstImage,
			const VkImageSubresourceRange& dstSubresources,
			VkImageLayout                  srcLayout,
			VkPipelineStageFlags2          srcStages,
			VkAccessFlags2                 srcAccess,
			VkImageLayout                  dstLayout,
			VkPipelineStageFlags2          dstStages,
			VkAccessFlags2                 dstAccess);


        /**
         * \brief Sets viewports
         * 
         * \param [in] viewportCount Number of viewports
         * \param [in] viewports The viewports
         * \param [in] scissorRects Schissor rectangles
         */
		void setViewports(
			uint32_t          viewportCount,
			const VkViewport* viewports);

        /**
         * \brief Sets viewports
         * 
         * \param [in] scissorCount Number of schissor rectangles
         * \param [in] scissorRects Schissor rectangles
         */
		void setScissors(
			uint32_t        scissorCount,
			const VkRect2D* scissorRects);


    private:
		VltGraphicsPipeline* lookupGraphicsPipeline(
			const VltGraphicsPipelineShaders& shaders);

		bool updateGraphicsPipeline();

		template <bool Indexed, bool Indirect>
		bool commitGraphicsState();

	private:
		VltDevice*  m_device;
		VltObjects* m_common;

        Rc<VltCommandList> m_cmd;

        VltContextFlags m_flags;
		VltContextState m_state;

        VltBarrierSet m_execBarriers;

        std::array<VltGraphicsPipeline*, 4096> m_gpLookupCache = {};
	};


}  // namespace sce::vlt