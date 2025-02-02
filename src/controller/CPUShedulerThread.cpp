#include "controller/CPUShedulerThread.h"
#include "controller/CPUSheduler.h"
#include "controller/Task.h"
#include "debug/CPUSchedulerTasksLog.h"

#ifdef _UNI_LIB_DEBUG
#include "lib/TimeCounter.h"
#endif //_UNI_LIB_DEBUG


namespace UniLib {
	namespace controller {
		CPUShedulerThread::CPUShedulerThread(CPUSheduler* parent, const char* name)
			: Thread(name), mParent(parent)
		{
#ifdef _UNI_LIB_DEBUG
			mName = name;
#endif
			mWaitingTask = mParent->getNextUndoneTask(this);

		}

		CPUShedulerThread::~CPUShedulerThread()
		{
		}

		int CPUShedulerThread::ThreadFunction()
		{
			while(mWaitingTask.getResourcePtrHolder()) 
			{
				
#ifdef _UNI_LIB_DEBUG
				lib::TimeCounter counter;
				debug::CPUShedulerTasksLog* l = debug::CPUShedulerTasksLog::getInstance();
				const char* name = mWaitingTask->getName();
				l->addTaskLogEntry(mWaitingTask.getResourcePtrHolder(), mWaitingTask->getResourceType(), mName.data(), name);
#endif 
				mWaitingTask->run();
#ifdef _UNI_LIB_DEBUG
				l->removeTaskLogEntry(mWaitingTask.getResourcePtrHolder());
				SpeedLog.writeToLog("%s used on thread: %s by Task: %s of: %s",
					counter.string().data(), mName.data(), mWaitingTask->getResourceType(), name);
#endif
				mWaitingTask = mParent->getNextUndoneTask(this);
			}
			return 0;
		}

		void CPUShedulerThread::setNewTask(TaskPtr cpuTask)
		{
			threadLock();
			mWaitingTask = cpuTask;
			threadUnlock();
			condSignal();
		}
	}
}