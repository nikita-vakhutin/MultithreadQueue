#pragma once

#include"MsgQueue.h"

class MsgQueueImpl : public MsgQueue
{
protected:

	// Incoming message event.
	int OnMsg(void* pMsg) override;
};
