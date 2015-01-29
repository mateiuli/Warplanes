#include "ParallelTask.hpp"

ParallelTask::ParallelTask()
:	mThread(&ParallelTask::runTask, this),
	mFinished(false)
{
}

void ParallelTask::execute()
{
	mFinished = false;
	mElapsedTime.restart();
	mThread.launch();
}

bool ParallelTask::isFinished()
{
	// Every read/write to the class's members
	// is done safely using locks and mutexes
	sf::Lock lock(mMutex);
	return mFinished;
}

float ParallelTask::getCompletion()
{
	sf::Lock lock(mMutex);

	// 100% at 4 seconds of elapsed time
	return mElapsedTime.getElapsedTime().asSeconds() / 4.f;
}

void ParallelTask::runTask()
{
	// Dummy task, stall 10 seconds
	bool ended = false;
	while(!ended) {
		// Protect the clock
		sf::Lock lock(mMutex);
		if(mElapsedTime.getElapsedTime().asSeconds() >= 4.f)
			ended = true;
	}

	// mFinished may be accessed from multiple threads, protect it
	{
		sf::Lock lock(mMutex);
		mFinished = true;
	}
}
