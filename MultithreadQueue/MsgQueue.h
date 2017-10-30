#pragma once

#include "stdafx.h"
#include <queue>
#include <mutex>

class MsgQueue
{
public:

	// Send async message.
	void Post(void* pMsg);

	// Send sync message.
	int Send(void* pMsg);

	// Wait message with specified timeout.
	void Wait(int nMilliseconds);

	// Process all messages from the queue.
	void ProcessMessages();

	// Returns whether queue is empty.
	bool IsEmpty() const;

protected:

	// Incoming message event.
	virtual int OnMsg(void* pMsg) = 0;

protected:

	std::queue<void *> m_qInternalQueue;

	mutable std::mutex m_Lock;
	std::condition_variable m_ConditionalVariable;
};