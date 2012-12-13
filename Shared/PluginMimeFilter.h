// AidOnlineMimeFilter.h : Declaration of the CAdPluginMimeFilter
// http://msdn.microsoft.com/en-us/library/aa767916(VS.85).aspx

#pragma once

#ifdef  NO_DUMPMEMORY
 #define _CRTDBG_MAP_ALLOC
 #include <crtdbg.h>
#endif

#ifdef PRODUCT_AIDONLINE
 #include "../AidOnline/AidOnline.h"
 #include "../AidOnline/AdRequest.h"
#else
 #include "../AdBlocker/AdBlocker.h"
#endif

#define INTERNET_OPTION_URL                     34

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
 #error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif


class LocalClient;
class ByteBuffer;

class ATL_NO_VTABLE CAdPluginMimeFilter :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAdPluginMimeFilter, &CLSID_AdPluginMimeFilter>,
	public IInternetProtocol,
	public IInternetProtocolSink,
	public IDispatchImpl<IAdPluginMimeFilter, &IID_IAdPluginMimeFilter, &LIBID_AdPluginLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IInternetProtocolInfo,
	public IHttpNegotiate
{

public:

    CAdPluginMimeFilter();
	~CAdPluginMimeFilter();

DECLARE_REGISTRY_RESOURCEID(IDR_ADPLUGIN_MIMEFILTER)

BEGIN_COM_MAP(CAdPluginMimeFilter)
	COM_INTERFACE_ENTRY(IAdPluginMimeFilter)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IID(IID_IInternetProtocol, IInternetProtocol)
	COM_INTERFACE_ENTRY_IID(IID_IInternetProtocolRoot, IInternetProtocol)
	COM_INTERFACE_ENTRY_IID(IID_IInternetProtocolSink, IInternetProtocolSink)
	COM_INTERFACE_ENTRY_IID(IID_IInternetProtocolInfo, IInternetProtocolInfo)
	COM_INTERFACE_ENTRY(IHttpNegotiate)
END_COM_MAP()

BEGIN_SERVICE_MAP(CAdPluginMimeFilter)
	SERVICE_ENTRY(IID_IHttpNegotiate)
END_SERVICE_MAP()

	// IInternetProtocolInfo
	HRESULT STDMETHODCALLTYPE CombineUrl(
		/* [in] */LPCWSTR pwzBaseUrl,
		/* [in] */LPCWSTR pwzRelativeUrl,
		/* [in] */DWORD dwCombineFlags,
		/* [out] */ LPWSTR pwzResult,
		/* [in] */DWORD cchResult,
		/* [out] */ DWORD *pcchResult,
		/* [in] */DWORD dwReserved);


	HRESULT STDMETHODCALLTYPE CompareUrl(
		/* [in] */ LPCWSTR pwzUrl1,
		/* [in] */ LPCWSTR pwzUrl2,
		/* [in] */ DWORD dwCompareFlags
	);

	HRESULT STDMETHODCALLTYPE ParseUrl(
		/* [in] */ LPCWSTR pwzUrl,
		/* [in] */ PARSEACTION ParseAction,
		/* [in] */ DWORD dwParseFlags,
		/* [out] */ LPWSTR pwzResult,
		/* [in] */ DWORD cchResult,
		/* [out] */ DWORD *pcchResult,
		/* [in] */ DWORD dwReserved
	);

	HRESULT STDMETHODCALLTYPE QueryInfo(
		/* [in] */ LPCWSTR pwzUrl,
		/* [in] */ QUERYOPTION OueryOption,
		/* [in] */ DWORD dwQueryFlags,
		/* [in] */ LPVOID pBuffer,
		/* [in] */ DWORD cbBuffer,
		/* [in] */ DWORD *pcbBuf,
		/* [in] */ DWORD dwReserved
	);

	// IInternetProtocolRoot
	HRESULT STDMETHODCALLTYPE Start(
        /* [in] */ LPCWSTR szUrl,
        /* [in] */ IInternetProtocolSink __RPC_FAR *pOIProtSink,
        /* [in] */ IInternetBindInfo __RPC_FAR *pOIBindInfo,
        /* [in] */ DWORD grfPI,
        /* [in] */ DWORD dwReserved);

    HRESULT STDMETHODCALLTYPE Continue(
        /* [in] */ PROTOCOLDATA __RPC_FAR *pProtocolData);

    HRESULT STDMETHODCALLTYPE Abort(
        /* [in] */ HRESULT hrReason,
        /* [in] */ DWORD dwOptions);

    HRESULT STDMETHODCALLTYPE Terminate(
        /* [in] */ DWORD dwOptions);

	HRESULT STDMETHODCALLTYPE Suspend(void) {return E_NOTIMPL;}		// Not implemented

    HRESULT STDMETHODCALLTYPE Resume(void) {return E_NOTIMPL;}		// Not implemented


	// IInternetProtocol based on IInternetProtocolRoot

	HRESULT STDMETHODCALLTYPE Read(
        /* [length_is][size_is][out][in] */ void __RPC_FAR *pv,
        /* [in] */ ULONG cb,
        /* [out] */ ULONG __RPC_FAR *pcbRead);

    HRESULT STDMETHODCALLTYPE Seek(
        /* [in] */ LARGE_INTEGER dlibMove,
        /* [in] */ DWORD dwOrigin,
        /* [out] */ ULARGE_INTEGER __RPC_FAR *plibNewPosition);

    HRESULT STDMETHODCALLTYPE LockRequest(
        /* [in] */ DWORD dwOptions);

    HRESULT STDMETHODCALLTYPE UnlockRequest(void);

	STDMETHODIMP BeginningTransaction(
		/* [in] */ LPCWSTR szURL,
		/* [in] */ LPCWSTR szHeaders,
		/* [in] */ DWORD dwReserved,
		/* [out] */ LPWSTR *pszAdditionalHeaders);

	STDMETHODIMP OnResponse(
		/* [in] */ DWORD dwResponseCode,
		/* [in] */ LPCWSTR szResponseHeaders,
		/* [in] */ LPCWSTR szRequestHeaders,
		/* [out] */ LPWSTR *pszAdditionalRequestHeaders);

public:

	// IInternetProtocolSink interface
	STDMETHOD(Switch)(PROTOCOLDATA __RPC_FAR *pProtocolData);
    STDMETHOD(ReportProgress)(ULONG ulStatusCode, LPCWSTR szStatusText);
    STDMETHOD(ReportData)(DWORD grfBSCF, ULONG ulProgress, ULONG ulProgressMax);
    STDMETHOD(ReportResult)(HRESULT hrResult, DWORD dwError, LPCWSTR szResult);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	// Implementation
	STDMETHODIMP CreateParser(IHTMLDocument2** parser, IAdPluginListener** container);
	STDMETHODIMP WriteToParser(CStringW& html, IHTMLDocument2* parser);
	STDMETHODIMP ParseHtml();
    STDMETHODIMP ParseHtmlElement(IHTMLElement* pElement, IHTMLElement* pParent, const CString& url, bool isNoScript);
	STDMETHODIMP GetParsedHtml(CString *html, IHTMLDocument2* parser);
	STDMETHODIMP RemoveElement(IHTMLElement* pElement, IHTMLElement* pParent, IHTMLElement** elementInstead, int divid);

#ifdef PRODUCT_AIDONLINE
    static void GetAdSize(IHTMLElement* pElement, CString srcUrl, CString& width, CString& height);
	static CString GetZoneID(CString width, CString height);
#endif // PRODUCT_AIDONLINE

    void HandleScript(IHTMLElement* pElement, CString script, const CString& url);
	void HandleHtmlElement(IHTMLElement* pElement, IHTMLElement* pParent, CComBSTR tag, const CString& url, bool isNoScript);
	STDMETHODIMP Cleanup(IHTMLDocument2* parser, IAdPluginListener* container);

	STDMETHODIMP DetectCharset(CString& input);
	STDMETHODIMP DeleteStringPreamble(CString& input);
	STDMETHODIMP ConvertToUnicode(CString& input);

protected:

    // Whether we're starting the conversion so we can output html start
    bool m_bFirstRead;

	IInternetProtocolSink* m_pOutgoingProtSink;
	IInternetProtocol* m_pIncomingProt;
	CComPtr<IInternetBindInfo> m_pOIBindInfo;
	IInternetProtocolInfo* m_pIncomingInfo;

	CStringW m_dataBuffer;
	CString m_parsedBuffer;
	UINT m_posPointer;
	bool m_bParsed;
    bool m_bIsActive;
	int m_adsReplaced;
	CString m_curUrl;
	CString m_curDomain;
	bool m_disableFilter;
	ByteBuffer* m_byteBuffer;
	bool m_isHTML;
	bool m_isPending;
	BINDINFO m_bindInfo;
	CComPtr<IMultiLanguage> m_multiLanguage;

private:

	CString m_detectedCharset;

#ifdef PRODUCT_AIDONLINE
	AdRequests m_adRequests;
#endif // PRODUCT_AIDONLINE

	LocalClient* m_localClient;
};

OBJECT_ENTRY_AUTO(__uuidof(AdPluginMimeFilter), CAdPluginMimeFilter)
