#ifndef __CTHREAD__
#define __CTHREAD__

class CThread {

	static DWORD WINAPI DefProc(void *parm);

protected:

	HANDLE handle;
	DWORD thread_id;

public:

	CThread();
virtual	~CThread();

	int CreateThread();
	void TerminateThread();

	virtual int OnInit() { return TRUE; }

	void SetThreadPriority(int i);
	virtual void ResumeThread();
	virtual void SuspendThread();
	virtual void ResetThread();

	virtual DWORD Proc() = 0;
};

inline CThread::CThread()
{
	handle = NULL;
}

inline CThread::~CThread()
{
	if(handle) {
		::TerminateThread(handle,0);
		CloseHandle(handle);
	}
}

inline void CThread::TerminateThread()
{
	if(handle) {
		::TerminateThread(handle,0);
		CloseHandle(handle);
		handle = NULL;
	}
}

inline int CThread::CreateThread()
{
	TerminateThread();
	handle = ::CreateThread(NULL,NULL,DefProc,this,CREATE_SUSPENDED,&thread_id);
//::SetThreadPriority( handle, THREAD_PRIORITY_ABOVE_NORMAL);
	if(handle)
		return TRUE;

	return FALSE;
}

inline void CThread::SetThreadPriority(int i)
{
	if(handle) {
		::SetThreadPriority(handle,i);
	}
}

inline void CThread::ResumeThread()
{
	if(handle) {
		::ResumeThread(handle);
	}
}

inline void CThread::SuspendThread()
{
	if(handle)
		::SuspendThread(handle);
}

inline void CThread::ResetThread()
{

}

inline DWORD WINAPI CThread::DefProc(void *parm)
{
	CThread *thread = (CThread*)parm;

	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	thread->Proc();

	CoUninitialize();

	ExitThread(0);
	return 0;
}

#endif // __CTHREAD__

