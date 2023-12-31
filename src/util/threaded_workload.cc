#include "threaded_workload.h"

std::shared_ptr<IThreadedWorkload> ThreadedWorkload::AddTask(std::function<void(void)> task)
{
	this->tasks.push_back(task);
	return shared_from_this();
}

void ThreadedWorkload::Join()
{
	// If only one task is available just run it in the same thread
	if (tasks.size() == 1) 
	{
		tasks.front()();
	}
	else if (tasks.size() > 1)
	{
		std::vector<std::thread> threads;
		threads.reserve(tasks.size());

        for (const auto& t : tasks)
		{
			threads.push_back(std::move(std::thread(t)));
		}

		for (auto& t : threads)
		{
			if (t.joinable())
			{
				t.join();
			}
		}
	}

	tasks.clear();
}