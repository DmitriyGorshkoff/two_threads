#pragma once

#include <vector>
#include <memory>
#include <queue>
#include <mutex>

struct QueueElement
{
	std::shared_ptr< std::vector< char > > mDataPointer;
	size_t mSize;
};

struct LocalQueue
{
	LocalQueue(size_t aMaxSize = 256) : mMaxSize(aMaxSize), mSize(0) {}

	void push(QueueElement aElement) {
		if (mSize < mMaxSize)
		{
			mQueue.push(aElement);
			mSize += 1;
		}
		else
		{
			// Error!
		}
	};
	QueueElement pop()
	{
		if (mSize > 0 && !mQueue.empty())
		{
			QueueElement tmp = mQueue.front();
			mQueue.pop();
			return tmp;
			mSize -= 1;
		}
		else
		{
			// Error!
		}
	}

	bool Empty() { return mQueue.empty(); }

	std::queue< QueueElement > mQueue;
	size_t mSize;
	size_t mMaxSize;
	std::mutex mMutex;
};
