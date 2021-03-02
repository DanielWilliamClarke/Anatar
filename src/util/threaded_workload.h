#ifndef THREADED_WORKLOAD_H
#define THREADED_WORKLOAD_H
#pragma once

#include "i_threaded_workload.h"

#include <vector>

class ThreadedWorkload : public IThreadedWorkload
{
public:
	ThreadedWorkload() = default;
	virtual ~ThreadedWorkload() = default;
	virtual std::shared_ptr<IThreadedWorkload> Reserve(size_t expectedThreads) override;
	virtual std::shared_ptr<IThreadedWorkload> AddThread(std::thread& thread) override;
	virtual void Join() override;
private:
	std::vector<std::thread> threads;
};

#endif // THREADED_WORKLOAD_H