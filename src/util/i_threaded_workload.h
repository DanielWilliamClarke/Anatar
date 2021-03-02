#ifndef I_THREADED_WORKLOAD_H
#define I_THREADED_WORKLOAD_H
#pragma once

#include <memory>
#include <thread>

class IThreadedWorkload : public std::enable_shared_from_this<IThreadedWorkload>
{
public:
	IThreadedWorkload() = default;
	virtual ~IThreadedWorkload() = default;
	virtual std::shared_ptr<IThreadedWorkload> Reserve(size_t expectedThreads) = 0;
	virtual std::shared_ptr<IThreadedWorkload> AddThread(std::thread& thread) = 0;
	virtual void Join() = 0;
};

#endif // I_THREADED_WORKLOAD_H