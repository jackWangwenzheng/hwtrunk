#include "base_include.h"

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
		return false;
	}
	bActive = true;
	return true;
}

int BaseThread::Stop()
{
   bActive = false;
   pthread_join(tid, NULL);
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