
#ifndef __CUNK_H__
#define __CUNK_H__

class CUnk : public IUnknown
{
	long m_cRef;
public:
	CUnk():m_cRef(1){};
	virtual ~CUnk(){};

	ULONG STDMETHODCALLTYPE  AddRef(){ATLASSERT(m_cRef>0); long lRef = InterlockedIncrement(&m_cRef); return (ULONG)max(m_cRef, 1ul);};
	ULONG STDMETHODCALLTYPE Release(){long lRef = InterlockedDecrement(&m_cRef); ATLASSERT(lRef >= 0); if(lRef==0){m_cRef++; delete this; return 0;} return (ULONG)max(m_cRef, 1ul);};
	HRESULT STDMETHODCALLTYPE QueryInterface( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
	{
		if(!ppvObject) return E_POINTER;
		*ppvObject = NULL;
		if(riid != IID_IUnknown) 
			return E_NOINTERFACE;
		*ppvObject = this;
		AddRef();
		return S_OK;
	}
};

#endif //__CUNK_H__
