#include "stdafx.h"
#include "MsgQueue.h"

#include <chrono>

void MsgQueue::Post(void* pMsg)
{
	std::lock_guard<std::mutex> autoLock(m_Lock);

	m_qInternalQueue.push(pMsg);
	m_ConditionalVariable.notify_one();
}

int MsgQueue::Send(void* pMsg)
{
	return OnMsg(pMsg);
}

void MsgQueue::Wait(int nMilliseconds)
{
	if (!IsEmpty())
	{
		return;
	}

	std::unique_lock<std::mutex> lock(m_Lock);
	m_ConditionalVariable.wait_for(lock, std::chrono::milliseconds(nMilliseconds));
}

void MsgQueue::ProcessMessages()
{
	while (true)
	{
		void* pMsg = nullptr;

		{
			std::lock_guard<std::mutex> autoLock(m_Lock);

			if (!m_qInternalQueue.empty())
			{
				pMsg = m_qInternalQueue.front();
				m_qInternalQueue.pop();
			}
			else
			{
				return;
			}
		}

		// 
		// MESSAGE PROCESSING
		//

		if (pMsg != nullptr)
		{
			delete pMsg;
		}
	}
}

bool MsgQueue::IsEmpty() const
{
	std::lock_guard<std::mutex> autoLock(m_Lock);
	return m_qInternalQueue.empty();
}