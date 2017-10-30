#include "stdafx.h"

#include "MsgQueueImpl.h"
#include <thread>
#include <iostream>

#define PRODUCER_THREAD_COUNT 10
#define PRODUCER_THREAD_MESSAGES_COUNT 10000

void ConsumerThreadRoutine(MsgQueueImpl* msgQueueImpl)
{
	while (true)
	{
		msgQueueImpl->Wait(10000);
		msgQueueImpl->ProcessMessages();
	}
}

void ProducerThreadRoutine(int internalThreadId, MsgQueueImpl* msgQueueImpl)
{
	for (int i = 0; i < PRODUCER_THREAD_MESSAGES_COUNT; ++i)
	{
		msgQueueImpl->Post(new int(internalThreadId));
	}
	int rc = msgQueueImpl->Send(new int(internalThreadId));
}

int main()
{
	MsgQueueImpl msgQueueImpl;

	std::unique_ptr<std::thread> pCosumerThread(new std::thread(&ConsumerThreadRoutine, &msgQueueImpl));

	std::vector<std::unique_ptr<std::thread>> vThreads;
	for (int i = 0; i < PRODUCER_THREAD_COUNT; ++i)
	{
		vThreads.push_back(std::unique_ptr<std::thread>(new std::thread(&ProducerThreadRoutine, i+1, &msgQueueImpl)));
	}

	system("pause");
	for (auto& thread : vThreads)
	{
		thread->join();
	}
	pCosumerThread->detach();

    return 0;
}

