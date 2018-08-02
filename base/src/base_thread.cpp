#include "base_thread.h"

BaseThread::BaseThread()
{
    tid = 0;
}

BaseThread::~BaseThread()
{
}

bool BaseThread::Start()
{
	int err = CreatTheard(BaseThreadPoc);
	if (err < 0)
	{
		printf("start error\n");
		return false;
	}
	GetbActive() = true;
	return true;
}

int BaseThread::Stop()
{
   pthread_join(tid, NULL);
   GetbActive() = false;
   tid = 0;
}

int BaseThread::CreatTheard(tThreadPoc fn)
{
	int err;
	err = pthread_create(&tid, NULL, fn, this);
	return err;
}

void* BaseThread::BaseThreadPoc(void* param)
{
	BaseThread* pThread = (BaseThread*)param;
	if (pThread != NULL)
	{
		pThread->Run();
	}
}