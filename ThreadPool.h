#pragma once
#include<vector>
#include<thread>
#include<queue>
#include<functional>
#include<mutex>
class ThreadPool
{
public:
	ThreadPool(unsigned int threadCount);
	~ThreadPool();

	void WorkerThread();

private:
	std::vector<std::thread> mThreads;
	unsigned int mThreadCount;
	std::queue<std::function<void()>> mTasks;

	std::condition_variable mCondition;
	std::mutex mMutex;
};

