#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/socket.h>
#include <wx/event.h> 
#include <wx/busyinfo.h>
#include <wx/utils.h>
#include <wx/process.h>
#include <wx/sstream.h>

#include "CMyFrame.h"
#include "ping.h"
#include "global.h"

class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};
wxIMPLEMENT_APP(MyApp);






DEFINE_EVENT_TYPE(ENUM_CUSTOMEVENT_PING)
DEFINE_EVENT_TYPE(ENUM_CUSTOMEVENT_PING_EXIT)
DEFINE_EVENT_TYPE(ENUM_CUSTOMEVENT_IPERF_EXIT)

static wxWindow *g_pWindow = NULL;
static wxString g_strIp;
static wxIPV4address *g_pIpAddress;

static unsigned long g_pingTotal,g_pingSend,g_pingLost;
static unsigned long g_pingDelayTotal, g_pingDelayMin, g_pingDelayMax;
#define  MIN(x,y) (x>y?y:x)
#define  MAX(x,y) (x>y?x:y)
static void ping_cb(BOOL bResult, CPingReply &pr1)
{
	wxString str;
	if (!g_pWindow)
		return;
	g_pingTotal++;

	if (bResult)
	{
		str = str.Format("   %s, replied in RTT:%sms PackageSize:%d TTL:%d\n", 
			g_strIp, pr1.RTT==0?"<1":wxString::Format("%d",pr1.RTT),
			pr1.PackageSize, pr1.TTL);
		g_pingSend++;
		g_pingDelayTotal+=pr1.RTT;
		if (g_pingDelayMin==-1)
		{
			g_pingDelayMin = pr1.RTT;
			g_pingDelayMax = pr1.RTT;
		}
		g_pingDelayMin = MIN(g_pingDelayMin, pr1.RTT);
		g_pingDelayMax = MAX(g_pingDelayMax, pr1.RTT);
	}
	else  {
		str = str.Format("Failed in call to ping, GetLastError returns: %d\n", GetLastError());
		g_pingLost++;
	}

	wxCommandEvent evt(ENUM_CUSTOMEVENT_PING);
	evt.SetString(str);
	wxPostEvent(g_pWindow->GetEventHandler(), evt);
}

class CPingThread :public wxThread
{
public:

	CPingThread(wxWindow *pWindow, wxString strOrigIp, int times=5)
		:m_pWindow(pWindow)
		,m_strOrigIp(strOrigIp)
		,m_times(times)
	{
		if (!g_pIpAddress)
			g_pIpAddress = new wxIPV4address;
		g_pWindow = m_pWindow;
		g_pingTotal=g_pingSend=g_pingLost=0;
		g_pingDelayTotal=0;
		g_pingDelayMin=g_pingDelayMax=-1;
		Create();
		Run();

	}

	virtual void * Entry() 
	{
		CPing ping;
		CPingReply pr1;

		g_pIpAddress->Hostname(m_strOrigIp);
		g_strIp = g_pIpAddress->IPAddress();
		ShowInfo(wxString::Format("[*] Ping (%s)%s\n", m_strOrigIp, g_strIp));

		ping.Ping1(g_strIp, pr1, ping_cb, m_times);

		return NULL;
	}

	virtual void OnExit() 
	{
		ShowInfo(wxString::Format("Send Total:%d Send Succ:%d Lost:%d(%.2f%%)\nMin Delay:%dms Max delay:%dms Average delay:%dms", 
			g_pingTotal, g_pingSend, g_pingLost, g_pingLost/(float)g_pingTotal*100,
			g_pingDelayMin, g_pingDelayMax, g_pingDelayTotal/g_pingTotal));
		
		wxCommandEvent evt(ENUM_CUSTOMEVENT_PING_EXIT);
		wxPostEvent(m_pWindow->GetEventHandler(), evt);
	}

	void ShowInfo(wxString str)
	{
		wxCommandEvent evt(ENUM_CUSTOMEVENT_PING);
		evt.SetString(str);
		wxPostEvent(m_pWindow->GetEventHandler(), evt);
	}

public:
	wxString  m_strOrigIp;
	wxWindow *m_pWindow;
	int       m_times;
};

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
			m_pThread = new CPingThread(this, m_textCtrlIP->GetValue(), wxAtoi(m_textCtrlTimes->GetValue()));
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
	CPingThread *m_pThread;

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
			m_pThread = new CPingThread(this, m_textCtrlIP->GetValue(), wxAtoi(m_textCtrlTimes->GetValue()));
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
	CPingThread *m_pThread;

private:
	DECLARE_EVENT_TABLE()
};

class CProcessIperf:public wxProcess
{
public:
	CProcessIperf(wxWindow *pWindow)
		:wxProcess(pWindow)
		,m_pWindow(pWindow)
	{
		Redirect();
	}

	virtual void OnTerminate (int pid, int status)
	{
		if (m_pWindow) 
		{
			wxCommandEvent evt(ENUM_CUSTOMEVENT_IPERF_EXIT);
			evt.SetString("* IPERF EXIT!\n");
			wxPostEvent(m_pWindow->GetEventHandler(), evt);
		}

	}

public:
	wxWindow *m_pWindow;
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
		//wxShell(strCmds);
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
		//wxKill(m_nPid, wxSIGKILL);
		//m_pProcess = NULL;
		//m_timerIdleWakeUp.Start(100);
	}

	virtual void OnBtnKillClick( wxCommandEvent& event ) 
	{
		if (m_pProcess) {
			m_pProcess->Kill(m_pProcess->GetPid(), wxSIGNONE);
			delete m_pProcess;
			m_pProcess = NULL;
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
				size_t length = 4096;//pInput->GetSize();
				wxCharBuffer buffer(length);
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
				size_t length = 4096;//pInput->GetSize();
				wxCharBuffer buffer(length);
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

class CAutoHidWindows
{
public:
	CAutoHidWindows(wxWindow *pDlg)
		:m_pDlg(pDlg)
	{
		m_pDlg->Show(false);
	}
	~CAutoHidWindows()
	{
		m_pDlg->Show(true);
	}
	wxWindow *m_pDlg;
};

class CMainFrame:public CMainFrameBase 
{
public:
	CMainFrame( wxWindow* parent=NULL)
		:CMainFrameBase(parent)
	{
		ShowIperfDialog();
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