#pragma once

#include <vector>
#include <memory>
#include <condition_variable>


#include "LocalQueue.h"

class FirstThreadClass
{
public:

	FirstThreadClass(unsigned int aDataStorageSize, unsigned int aDataPerSecond);

	void work( LocalQueue* aQueue, std::condition_variable* aCondVar);

private:

	using OneMBPtr = std::shared_ptr< std::vector< char > >;
	using StoragePtr = std::shared_ptr< std::vector< OneMBPtr > >;

private:

	std::shared_ptr< std::vector< char > > FillInOneMB(char aCounter);

	unsigned int mDataPerSecond;
	StoragePtr mDataStorage;

	unsigned int mCounter = 0;
};
