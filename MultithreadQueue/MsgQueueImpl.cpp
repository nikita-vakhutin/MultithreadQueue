#include "stdafx.h"
#include "MsgQueueImpl.h"

int MsgQueueImpl::OnMsg(void* pMsg)
{
	int returnCode = (reinterpret_cast<size_t>(pMsg) % 10);
	delete pMsg;
	return returnCode;
}