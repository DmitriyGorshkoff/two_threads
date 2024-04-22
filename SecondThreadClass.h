#pragma once

#include <vector>
#include <memory>
#include <condition_variable>

#include "LocalQueue.h"

class SecondThreadClass
{
public:

	void work( LocalQueue* aQueue, std::condition_variable* aCondVar );

private:

	using OneMBPtr = std::shared_ptr< std::vector< char > >;
	using StoragePtr = std::shared_ptr< std::vector< OneMBPtr > >;

private:

	void SaveIntoFile( std::shared_ptr< std::vector< char > > aDataPtr, size_t aDataSize );
};
