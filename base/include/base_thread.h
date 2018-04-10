#ifndef _BASE_THREAD_H
#define _BASE_THREAD_H

#include"base_util.h"

typedef void*(*tThreadPoc)(void*);

class BaseThread
{
public:
	BaseThread();
	~BaseThread();
	
	virtual int Run() = 0;
	int Stop();   //结束一个线程
	bool Start();
	inline bool& GetbActive(){return bActive;}
private:
	static void* BaseThreadPoc(void* param);
	int CreatTheard(tThreadPoc fn);      //创建一个线程
	pthread_t tid;  //线程id
	bool bActive;
};

#endif