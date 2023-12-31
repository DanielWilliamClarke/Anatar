#ifndef THREADED_WORKLOAD_H
#define THREADED_WORKLOAD_H

#include "i_threaded_workload.h"

#include <vector>

class ThreadedWorkload : public IThreadedWorkload
{
public:
	ThreadedWorkload() = default;
	~ThreadedWorkload() override = default;

	std::shared_ptr<IThreadedWorkload> AddTask(std::function<void(void)> task) override;
	void Join() override;

private:
	std::vector<std::function<void(void)>> tasks;
};

#endif // THREADED_WORKLOAD_H