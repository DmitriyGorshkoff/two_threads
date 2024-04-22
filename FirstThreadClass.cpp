#include <thread>
#include <mutex>
#include <chrono>

#include "LocalQueue.h"
#include "FirstThreadClass.h"

FirstThreadClass::FirstThreadClass(unsigned int aDataStorageSize, unsigned int aDataPerSecond)
{
	aDataStorageSize = 256;

	int mb = 1048576;

	mDataStorage = std::make_shared< std::vector< OneMBPtr > >(std::vector<OneMBPtr>(aDataStorageSize));

	mDataPerSecond = aDataPerSecond;
}

std::shared_ptr< std::vector< char > > FirstThreadClass::FillInOneMB(char aCounter)
{
	int mb = 1048576;

	mDataStorage->at(aCounter) = std::make_shared< std::vector< char > >(std::vector<char>(mb));

	for (int j = 0; j < mb; ++j)
	{
		mDataStorage->at(aCounter)->at(j) = aCounter;
	}

	return mDataStorage->at(aCounter);
}

void FirstThreadClass::work(LocalQueue* aQueue, std::condition_variable* aCondVar)
{
	std::chrono::duration<long long> sec10{ 10 };

	std::this_thread::sleep_for(sec10);

	while ( mCounter < 256)
	{
		auto DataPtr = FillInOneMB( static_cast<char>(mCounter) );

		std::unique_lock<std::mutex> QueueLock(aQueue->mMutex);
		aCondVar->wait(QueueLock);
		aQueue->push({ DataPtr, DataPtr->size() });
		QueueLock.unlock();
		aCondVar->notify_one();
		mCounter += 1;

		std::this_thread::sleep_for( sec10 );
	}
}

