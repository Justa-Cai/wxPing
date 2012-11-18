#ifndef _UTILS_H_
#define _UTILS_H_
#include <wx/wx.h>
#include <wx/socket.h>
#include <wx/process.h>
#include "global.h"
#include "ping.h"

#define  MIN(x,y) (x>y?y:x)
#define  MAX(x,y) (x>y?x:y)

wxString GetIperfPath();


class CPingThread :public wxThread
{
public:
	CPingThread(wxWindow *pWindow, wxString strOrigIp, int times=5);

	virtual void * Entry();

	virtual void OnExit();

	void ShowInfo(wxString str);

public:
	wxString  m_strOrigIp;
	wxWindow *m_pWindow;
	int       m_times;
};

/** @class CProcessIperf
  * @brief Iperf cmds process
  * @note {
  you can read process output in dialog OnIdle function
  	virtual void OnIdle( wxIdleEvent& event ) 
	{
		if (m_pProcess) {
			if (m_pProcess->IsErrorAvailable()) {
				wxInputStream *pInput = m_pProcess->GetErrorStream();
				wxCharBuffer buffer(4096);
				size_t offset = 0;
				while(pInput->CanRead())
				{
					pInput->Read(buffer.data()+offset, 1);
					offset++;
				}
				buffer.shrink(offset);

				m_textCtrlInfo->AppendText(buffer);

			}

			if (m_pProcess->IsInputAvailable()) {
				wxInputStream *pInput = m_pProcess->GetInputStream();
				wxCharBuffer buffer(4096);
				size_t offset = 0;
				while(pInput->CanRead())
				{
					pInput->Read(buffer.data()+offset, 1);
					offset++;
				}
				buffer.shrink(offset);

				m_textCtrlInfo->AppendText(buffer);
			}

		}
	}
  * @}
  */
class CProcessIperf:public wxProcess
{
public:
	CProcessIperf(wxWindow *pWindow);
	virtual void OnTerminate (int pid, int status);
public:
	wxWindow *m_pWindow;
};

/** 
  * @note {
  * ENUM_CUSTOMEVENT_IPERF_INFO
  * @}
  */
class CThreadIperf:public wxThread
{
public:
	CThreadIperf(wxWindow *pWindows, wxString strCmds);
	virtual void *Entry();

	void SendInfo(wxString str);

	virtual void OnExit();

protected:
	wxWindow *m_pWindow;
	CProcessIperf *m_pProcessIperf;
	wxString m_strCmds;
	long m_nPid;
};
#endif