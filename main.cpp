#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/socket.h>
#include <wx/event.h> 

#include "CMyFrame.h"
#include "ping.h"

class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};
wxIMPLEMENT_APP(MyApp);


enum CustomEventId
{
	ENUM_CUSTOMEVENT_ID_PING=7000,
	ENUM_CUSTOMEVENT_ID_PING_EXIT,

};

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(ENUM_CUSTOMEVENT_PING, ENUM_CUSTOMEVENT_ID_PING)
DECLARE_EVENT_TYPE(ENUM_CUSTOMEVENT_PING_EXIT, ENUM_CUSTOMEVENT_ID_PING_EXIT)
END_DECLARE_EVENT_TYPES()

DEFINE_EVENT_TYPE(ENUM_CUSTOMEVENT_PING)
DEFINE_EVENT_TYPE(ENUM_CUSTOMEVENT_PING_EXIT)

static wxFrame *g_pFrame = NULL;
static wxString g_strIp;
static wxIPV4address *g_pIpAddress;

static unsigned long g_pingTotal,g_pingSend,g_pingLost;
static unsigned long g_pingDelayTotal, g_pingDelayMin, g_pingDelayMax;
#define  MIN(x,y) (x>y?y:x)
#define  MAX(x,y) (x>y?x:y)
static void ping_cb(BOOL bResult, CPingReply &pr1)
{
	wxString str;
	if (!g_pFrame)
		return;
	g_pingTotal++;

	if (bResult)
	{
		str = str.Format("   %s [%s], replied in RTT:%sms PackageSize:%d TTL:%d\n", 
			g_strIp, g_pIpAddress->Hostname(), pr1.RTT==0?"<1":wxString::Format("%s",pr1.RTT),
			pr1.PackageSize, pr1.TTL);
		g_pingSend++;
		g_pingDelayTotal+=pr1.RTT;
		g_pingDelayMin = MIN(g_pingDelayMin, pr1.RTT);
		g_pingDelayMax = MAX(g_pingDelayMin, pr1.RTT);
	}
	else  {
		str = str.Format("Failed in call to ping, GetLastError returns: %d\n", GetLastError());
		g_pingLost++;
	}

	wxCommandEvent evt(ENUM_CUSTOMEVENT_PING);
	evt.SetString(str);
	wxPostEvent(g_pFrame->GetEventHandler(), evt);
}

class CPingThread :public wxThread
{
public:

	CPingThread(wxFrame *pFrame, wxString strOrigIp, int times=5)
		:m_pFrame(pFrame)
		,m_strOrigIp(strOrigIp)
		,m_times(times)
	{
		if (!g_pIpAddress)
			g_pIpAddress = new wxIPV4address;
		g_pFrame = m_pFrame;
		g_pingTotal=g_pingSend=g_pingLost=0;
		g_pingDelayTotal=g_pingDelayMin=g_pingDelayMax=0;
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
		wxPostEvent(m_pFrame->GetEventHandler(), evt);
	}

	void ShowInfo(wxString str)
	{
		wxCommandEvent evt(ENUM_CUSTOMEVENT_PING);
		evt.SetString(str);
		wxPostEvent(m_pFrame->GetEventHandler(), evt);
	}

public:
	wxString  m_strOrigIp;
	wxFrame  *m_pFrame;
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

bool MyApp::OnInit()
{
	CPingFrame *frame = new CPingFrame(NULL);
	frame->Show( true );
	return true;
}

BEGIN_EVENT_TABLE(CPingFrame, wxFrame)
  EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_PING, CPingFrame::OnShowPingInfo)
  EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_PING_EXIT, CPingFrame::OnPingThreadExit)
END_EVENT_TABLE()