#include "pch.h"
#include "ThreadPool.h"

ThreadPool::ThreadPool(unsigned int threadCount) : mThreadCount(threadCount)
{
	mThreads.reserve(threadCount);
	for (unsigned int i = 0; i < threadCount; i++)
	{
		mThreads.emplace_back([this]()) {this->}
	}
	
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::WorkerThread()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(mMutex);
		mCondition.wait(lock, [this](){ return !this->mTasks.empty() || //stop_all}

	}
}
