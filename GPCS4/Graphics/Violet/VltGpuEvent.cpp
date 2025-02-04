#include "VltGpuEvent.h"

#include "VltDevice.h"

namespace sce::vlt
{

	VltGpuEvent::VltGpuEvent(VltDevice*        device,
							 VltGpuEventHandle handle) :
		m_device(device),
		m_handle(handle)
	{
	}

	VltGpuEvent::~VltGpuEvent()
	{
		if (m_handle.pool && m_handle.event)
			m_handle.pool->freeEvent(m_handle.event);
	}

	VltGpuEventStatus VltGpuEvent::test() const
	{
		if (!m_handle.event)
			return VltGpuEventStatus::Invalid;

		VkResult status = vkGetEventStatus(
			m_device->handle(), m_handle.event);

		switch (status)
		{
		case VK_EVENT_SET:
			return VltGpuEventStatus::Signaled;
		case VK_EVENT_RESET:
			return VltGpuEventStatus::UnSignaled;
		default:
			return VltGpuEventStatus::Invalid;
		}
	}

	VkEvent VltGpuEvent::handle() const
	{
		return m_handle.event;
	}

	void VltGpuEvent::signal()
	{
		vkSetEvent(m_device->handle(), m_handle.event);
	}

	void VltGpuEvent::reset()
	{
		vkResetEvent(m_device->handle(), m_handle.event);
	}


	VltGpuEventPool::VltGpuEventPool(VltDevice* device) :
		m_device(device)
	{
	}

	VltGpuEventPool::~VltGpuEventPool()
	{
		for (VkEvent ev : m_events)
			vkDestroyEvent(m_device->handle(), ev, nullptr);
	}

	VltGpuEventHandle VltGpuEventPool::allocEvent()
	{
		VkEvent event = VK_NULL_HANDLE;

		{
			std::lock_guard<util::sync::Spinlock> lock(m_mutex);

			if (m_events.size() > 0)
			{
				event = m_events.back();
				m_events.pop_back();
			}
		}

		if (!event)
		{
			VkEventCreateInfo info;
			info.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
			info.pNext = nullptr;
			info.flags = 0;

			VkResult status = vkCreateEvent(
				m_device->handle(), &info, nullptr, &event);

			if (status != VK_SUCCESS)
			{
				Logger::err("DXVK: Failed to create GPU event");
				return VltGpuEventHandle();
			}
		}

		return { this, event };
	}

	void VltGpuEventPool::freeEvent(VkEvent event)
	{
		std::lock_guard<util::sync::Spinlock> lock(m_mutex);
		m_events.push_back(event);
	}
}  // namespace sce::vlt