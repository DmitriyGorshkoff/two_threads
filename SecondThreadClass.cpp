#include <thread>
#include <mutex>
#include <chrono>

#include "LocalQueue.h"
#include "SecondThreadClass.h"

void SecondThreadClass::SaveIntoFile(std::shared_ptr< std::vector< char > > aDataPtr, size_t aDataSize)
{
	
}

void SecondThreadClass::work(LocalQueue* aQueue, std::condition_variable* aCondVar)
{
	while (1)
	{
		std::unique_lock<std::mutex> QueueLock(aQueue->mMutex);
		aCondVar->wait(QueueLock);
		auto Element = aQueue->pop();
		QueueLock.unlock();
		aCondVar->notify_one();

		SaveIntoFile(Element.mDataPointer, Element.mSize);

	}

	
}