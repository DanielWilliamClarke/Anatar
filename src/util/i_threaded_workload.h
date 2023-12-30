#ifndef I_THREADED_WORKLOAD_H
#define I_THREADED_WORKLOAD_H


#include <memory>
#include <thread>
#include <functional>

class IThreadedWorkload : public std::enable_shared_from_this<IThreadedWorkload>
{
public:
	IThreadedWorkload() = default;
	virtual ~IThreadedWorkload() = default;
	virtual std::shared_ptr<IThreadedWorkload> AddTask(std::function<void(void)> task) = 0;
	virtual void Join() = 0;
};

#endif // I_THREADED_WORKLOAD_H