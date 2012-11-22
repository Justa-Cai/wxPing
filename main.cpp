#include <wx/wx.h>
#include <wx/socket.h>
#include <wx/event.h> 
#include <wx/busyinfo.h>
#include <wx/utils.h>
#include <wx/process.h>
#include <wx/sstream.h>

#include "utils.h"
#include "CMyFrame.h"
#include "ping.h"
#include "global.h"
#include "wlantest.h"

class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};
wxIMPLEMENT_APP(MyApp);


class CPingFrame: public CMyFrame
{
public:
	CPingFrame( wxWindow* parent )
		:CMyFrame(parent),
		 m_pThread(NULL)
	{
		m_textCtrlIP->AppendText("192.168.1.1");
		m_textCtrlTimes->AppendText("5");
	}

	virtual void OnBtnPingClick( wxCommandEvent& event ) 
	{
		if (m_pThread==NULL) {
			m_textCtrlInfo->Clear();
			m_buttonPing->Enable(false);
			m_pThread = new CThreadPing(this, m_textCtrlIP->GetValue(), wxAtoi(m_textCtrlTimes->GetValue()));
		}
	}

	void OnShowPingInfo(wxCommandEvent& event) 
	{
		wxString str = event.GetString();
		m_textCtrlInfo->AppendText(str);
	}

	void OnPingThreadExit(wxCommandEvent& event) 
	{
		m_pThread = NULL;
		m_buttonPing->Enable(true);
	}

public:
	CThreadPing *m_pThread;

private:
	DECLARE_EVENT_TABLE()
};

class CDialogPing: public CDialogPingBase
{
public:
	CDialogPing( wxWindow* parent = NULL )
		:CDialogPingBase(parent),
		m_pThread(NULL)
	{
		m_textCtrlIP->AppendText("192.168.1.1");
		m_textCtrlTimes->AppendText("5");
	}

	virtual void OnBtnPingClick( wxCommandEvent& event ) 
	{
		if (m_pThread==NULL) {
			m_textCtrlInfo->Clear();
			m_buttonPing->Enable(false);
			m_pThread = new CThreadPing(this, m_textCtrlIP->GetValue(), wxAtoi(m_textCtrlTimes->GetValue()));
		}
	}

	void OnShowPingInfo(wxCommandEvent& event) 
	{
		wxString str = event.GetString();
		m_textCtrlInfo->AppendText(str);
	}

	void OnPingThreadExit(wxCommandEvent& event) 
	{
		m_pThread = NULL;
		m_buttonPing->Enable(true);
	}

public:
	CThreadPing *m_pThread;

private:
	DECLARE_EVENT_TABLE()
};

class CDialogIperf:public CDialogIperfBase
{
public:
	CDialogIperf( wxWindow* parent = NULL )
		:CDialogIperfBase(parent)
		,m_pProcess(NULL)
		,m_timerIdleWakeUp(this)
	{
	}

	virtual void OnBtnCreateClick( wxCommandEvent& event ) 
	{
		wxString strCmds = m_textCtrlCmds->GetValue();

		if (!m_pProcess)
			m_pProcess = new CProcessIperf(this);
		else {
			wxMessageBox("Program is running...!");
			return;
		}

		m_textCtrlInfo->SetValue("");

		m_nPid = wxExecute(strCmds, wxEXEC_ASYNC | wxEXEC_HIDE_CONSOLE, m_pProcess);
		if (m_nPid<=0)
		{
			wxMessageBox("Can't Create Process!\nCMDS:" + strCmds);
			delete m_pProcess;
			m_pProcess = NULL;
			return;
		}

	}

	virtual void OnBtnKillClick( wxCommandEvent& event ) 
	{
		if (m_pProcess) {
			wxProcess::Kill(m_pProcess->GetPid(), wxSIGKILL);
			delete m_pProcess;
			m_pProcess = NULL;
			m_textCtrlInfo->AppendText("Progress End....\n");
		}
	}

	virtual void OnInitDialog( wxInitDialogEvent& event ) 
	{
		m_textCtrlCmds->SetValue(wxGetCwd() + "/iperf/iperf.exe -s");
	}

	void OnIperfExit( wxCommandEvent& event )
	{
		m_textCtrlInfo->AppendText(event.GetString());
		m_timerIdleWakeUp.Stop();
		delete m_pProcess;
		m_pProcess = NULL;
	}

	void OnTimer(wxTimerEvent& WXUNUSED(event))
	{
		wxWakeUpIdle();
	}

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
public:
	CProcessIperf *m_pProcess;
	long m_nPid;

	// the idle event wake up timer
	wxTimer m_timerIdleWakeUp;
private:
	DECLARE_EVENT_TABLE()
};



class CMainFrame:public CMainFrameBase 
{
public:
	CMainFrame( wxWindow* parent=NULL)
		:CMainFrameBase(parent)
	{
		ShowWlanTestDialog();
		this->Close();
	}

	void ShowPingDialog()
	{
		CDialogPing *pDlg = new CDialogPing(this);
		pDlg->ShowModal();
		delete pDlg;
	}

	void ShowIperfDialog()
	{
		CDialogIperf *pDlg = new CDialogIperf(this);
		pDlg->ShowModal();
		delete pDlg;
	}

	void ShowWlanTestDialog()
	{
		CDialogWlanTest *pDlg = new CDialogWlanTest(this);
		pDlg->ShowModal();
		delete pDlg;
	}

	virtual void OnShowPingDialog( wxCommandEvent& event ) 
	{
		ShowPingDialog();
	}

	virtual void OnShowIperfDialog( wxCommandEvent& event ) 
	{
		ShowIperfDialog();
	}

	virtual void OnBtnPingClick( wxCommandEvent& event ) 
	{
		ShowPingDialog();
	}

	virtual void OnBtnIperfCllick( wxCommandEvent& event ) 
	{
		ShowIperfDialog();
	}

public:

};


bool MyApp::OnInit()
{
	wxInitAllImageHandlers();
	CMainFrame *pFrame = new CMainFrame();
	pFrame->Show();
	return true;
}

BEGIN_EVENT_TABLE(CPingFrame, wxFrame)
  EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_PING, CPingFrame::OnShowPingInfo)
  EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_PING_EXIT, CPingFrame::OnPingThreadExit)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(CDialogPing, wxDialog)
EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_PING, CDialogPing::OnShowPingInfo)
EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_PING_EXIT, CDialogPing::OnPingThreadExit)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(CDialogIperf, wxDialog)
EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_IPERF_EXIT, CDialogIperf::OnIperfExit)
EVT_TIMER(wxID_ANY, CDialogIperf::OnTimer)
END_EVENT_TABLE()