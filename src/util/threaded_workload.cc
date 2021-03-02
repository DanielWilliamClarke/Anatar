#include "threaded_workload.h"

std::shared_ptr<IThreadedWorkload> ThreadedWorkload::Reserve(size_t expectedThreads)
{
	this->threads.reserve(expectedThreads);
	return shared_from_this();
}

std::shared_ptr<IThreadedWorkload> ThreadedWorkload::AddThread(std::thread& thread)
{
	this->threads.emplace_back(std::move(thread));
	return shared_from_this();
}

void ThreadedWorkload::Join()
{
	for (auto& t : this->threads)
	{
		if (t.joinable()) {
			t.join();
		}
	}
	this->threads.clear();
}