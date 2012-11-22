#include "wlantest.h"
static CThreadIperf *g_pThreadIperf;
static CThreadPing *g_pThreadPing;
/************************************************************************/
/* Main Page                                                            */
/************************************************************************/
static CDialogWlanTest *g_pDialogWlanTest;
static inline wxString GetInputIp()
{
	return g_pDialogWlanTest->m_textCtrlClientIp->GetValue();
}

static inline bool IsUDPTest()
{
	return g_pDialogWlanTest->m_radioBox_TCPUDP->GetSelection()==1;
}

static inline void SetTestProtcol(bool bTCP)
{
	g_pDialogWlanTest->m_radioBox_TCPUDP->SetSelection(bTCP?0:1);
}

static inline int GetUDPSendSpeed()
{
	int v = wxAtoi(g_pDialogWlanTest->m_textCtrlUDPSpeed->GetValue());
	if (v<=0)
		return 10;
	else
		return v;
}

static inline int GetTestTimes()
{
	int v = wxAtoi(g_pDialogWlanTest->m_textCtrlTestTime->GetValue());
	if (v<=0)
		return 10;
	else
		return v;
}

static wxString GetIperfOptions()
{
	wxString strUDP;
	wxString ip = GetInputIp();
	wxString strTestTime;
	wxString strOptions;
	if (ip.Len()<7) {
		wxMessageBox("ip wrong:" + ip);
		return wxEmptyString;
	}
	if (IsUDPTest())
		strUDP.Printf(" -u -b %dK ", GetUDPSendSpeed());

	strTestTime.Printf(" -t %d", GetTestTimes());

	strOptions.Printf(" -c %s %s %s -i 1\n", GetInputIp(), strUDP, strTestTime);
	return strOptions;
}

/************************************************************************/
/* main Windows                                                                     */
/************************************************************************/
CDialogWlanTest::CDialogWlanTest( wxWindow *parent/*=NULL */ ) :
CDialogWlanTestBase(parent)
{
	Maximize(true);
	g_pDialogWlanTest = this;
	m_pBandwidth = new CPanelBandwidth(m_notebook);
	m_pDelay = new CPanelDelay(m_notebook);
	m_pJiffer = new CPanelJitter(m_notebook);
	m_pPacketDropRate = new CPanelPackaetDrogRate(m_notebook);
	m_notebook->AddPage(m_pBandwidth, "Bandwidth");
	m_notebook->AddPage(m_pDelay, "Ping Delay");
	m_notebook->AddPage(m_pJiffer, "Jiffer");
	m_notebook->AddPage(m_pPacketDropRate, "Packet Drop Rate");
	m_textCtrlClientIp->AppendText("192.168.1.205");
	m_textCtrlUDPSpeed->SetValue("10240");
	m_radioBox_TCPUDP->SetSelection(0);
	m_textCtrlUDPSpeed->Enable(false);
	m_icon.LoadFile(GetResPath() + "logo.png", wxBITMAP_TYPE_PNG, 32, 32 );
	SetIcon(m_icon);
}

CDialogWlanTest::~CDialogWlanTest()
{
	g_pDialogWlanTest = NULL;
	delete m_pBandwidth;
	delete m_pDelay;
	delete m_pJiffer;
	delete m_pPacketDropRate;
}

void CDialogWlanTest::TCPUDPOnRadioBox( wxCommandEvent& event )
{
	if (m_radioBox_TCPUDP->GetSelection()==0 || m_notebook->GetSelection()==1) {
		// tcp unshow
		m_textCtrlUDPSpeed->Enable(false);
	}
	else {
		// udp show
		m_textCtrlUDPSpeed->Enable(true);
	}
}

void CDialogWlanTest::OnNotebookPageChanged( wxNotebookEvent& event )
{
	if (g_pThreadIperf){
		static bool bSkip = false;
		if (!bSkip) {
			bSkip = true;
			m_notebook->SetSelection(event.GetOldSelection());
		}
		else
			bSkip = false;
	}
	else {
		switch(event.GetSelection()) {
			case 0:
				m_radioBox_TCPUDP->SetSelection(0);
				m_radioBox_TCPUDP->Enable();
				break;
			case 1:
				m_radioBox_TCPUDP->SetSelection(1);
				m_textCtrlUDPSpeed->Enable(false);
				break;
			case 2:
				m_radioBox_TCPUDP->SetSelection(1);
				m_radioBox_TCPUDP->Enable(false);
				break;
			case 3:
				m_radioBox_TCPUDP->SetSelection(1);
				m_radioBox_TCPUDP->Enable(false);
				break;
		}
		TCPUDPOnRadioBox(event);
	}
}

BEGIN_EVENT_TABLE(CDialogWlanTest, wxDialog)
END_EVENT_TABLE()
/************************************************************************/
/* Bandwith                                                             */
/************************************************************************/
CPanelBandwidth::CPanelBandwidth( wxWindow *parent/*=NULL*/ ) :
CPanelBandwidthBase(parent)
{

}

void CPanelBandwidth::OnTestButtonClick( wxCommandEvent& event )
{
	if (!g_pThreadIperf) {
		wxString strOption = GetIperfOptions();
		if (!strOption.IsEmpty()) {
			m_textCtrlInfo->Clear();

			wxString strcmd = GetIperfPath() + strOption;
			g_pThreadIperf = new CThreadIperf(this, strcmd);
			g_pThreadIperf->Run();
			m_buttonTest->Disable();
		}
	}
}

void CPanelBandwidth::OnIperfInfo( wxCommandEvent& event )
{
	m_textCtrlInfo->AppendText(event.GetString());
}

void CPanelBandwidth::OnIperfExit( wxCommandEvent& event )
{
	if (g_pThreadIperf)
	{
		g_pThreadIperf->Delete();
		delete g_pThreadIperf;
		g_pThreadIperf = NULL;
		m_buttonTest->Enable();
	}
}
BEGIN_EVENT_TABLE(CPanelBandwidth, wxPanel)
EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_IPERF_EXIT, CPanelBandwidth::OnIperfExit)
EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_IPERF_INFO, CPanelBandwidth::OnIperfInfo)
END_EVENT_TABLE()

/************************************************************************/
/* Jitter                                                               */
/************************************************************************/
CPanelJitter::CPanelJitter( wxWindow *parent/*=NULL*/ ) :
CPanelJitterBase(parent)
{
	SetTestProtcol(false);
}

void CPanelJitter::OnTestButtonClick( wxCommandEvent& event )
{
	wxString strUDP; 
	if (!g_pThreadIperf) {
		m_textCtrlInfo->Clear();
		wxString ip = GetInputIp();
		if (ip.Len()<7) {
			wxMessageBox("ip wrong:" + ip);
			return;
		}
		if (IsUDPTest())
			strUDP.Printf(" -u -b %dK ", GetUDPSendSpeed());

		wxString strcmd = GetIperfPath() + "-c " + GetInputIp() + strUDP + " -i 1\n";
		g_pThreadIperf = new CThreadIperf(this, strcmd);
		g_pThreadIperf->Run();
		m_buttonTest->Disable();
	}
}

void CPanelJitter::OnIperfInfo( wxCommandEvent& event )
{
	m_textCtrlInfo->AppendText(event.GetString());
}

void CPanelJitter::OnIperfExit( wxCommandEvent& event )
{
	if (g_pThreadIperf)
	{
		g_pThreadIperf->Delete();
		delete g_pThreadIperf;
		g_pThreadIperf = NULL;
		m_buttonTest->Enable();
	}
}
BEGIN_EVENT_TABLE(CPanelJitter, wxPanel)
EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_IPERF_EXIT, CPanelJitter::OnIperfExit)
EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_IPERF_INFO, CPanelJitter::OnIperfInfo)
END_EVENT_TABLE()



/************************************************************************/
/*  Drop Rate                                                              */
/************************************************************************/
CPanelPackaetDrogRate::CPanelPackaetDrogRate( wxWindow *parent/*=NULL*/ ) :
CPanelPackaetDrogRateBase(parent)
{
	SetTestProtcol(false);
}

void CPanelPackaetDrogRate::OnTestButtonClick( wxCommandEvent& event )
{
	wxString strUDP; 
	if (!g_pThreadIperf) {
		m_textCtrlInfo->Clear();
		wxString ip = GetInputIp();
		if (ip.Len()<7) {
			wxMessageBox("ip wrong:" + ip);
			return;
		}
		if (IsUDPTest())
			strUDP.Printf(" -u -b %dK ", GetUDPSendSpeed());

		wxString strcmd = GetIperfPath() + "-c " + GetInputIp() + strUDP + " -i 1\n";
		g_pThreadIperf = new CThreadIperf(this, strcmd);
		g_pThreadIperf->Run();
		m_buttonTest->Disable();
	}
}

void CPanelPackaetDrogRate::OnIperfInfo( wxCommandEvent& event )
{
	m_textCtrlInfo->AppendText(event.GetString());
}

void CPanelPackaetDrogRate::OnIperfExit( wxCommandEvent& event )
{
	if (g_pThreadIperf)
	{
		g_pThreadIperf->Delete();
		delete g_pThreadIperf;
		g_pThreadIperf = NULL;
		m_buttonTest->Enable();
	}
}
BEGIN_EVENT_TABLE(CPanelPackaetDrogRate, wxPanel)
EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_IPERF_EXIT, CPanelPackaetDrogRate::OnIperfExit)
EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_IPERF_INFO, CPanelPackaetDrogRate::OnIperfInfo)
END_EVENT_TABLE()



/************************************************************************/
/*  Delay                                                              */
/************************************************************************/
CPanelDelay::CPanelDelay( wxWindow *parent/*=NULL*/ ) :
CPanelDelayBase(parent)
{
}

void CPanelDelay::OnTestButtonClick( wxCommandEvent& event )
{
	if (g_pThreadPing==NULL) {
		m_textCtrlInfo->Clear();
		m_buttonTest->Enable(false);
		g_pThreadPing = new CThreadPing(this, GetInputIp(), GetTestTimes());
		g_pThreadPing->Run();
	}
}

void CPanelDelay::OnPingInfo( wxCommandEvent& event )
{
	wxString str = event.GetString();
	m_textCtrlInfo->AppendText(str);
}

void CPanelDelay::OnPingExit( wxCommandEvent& event )
{
	g_pThreadPing = NULL;
	m_buttonTest->Enable();
}
BEGIN_EVENT_TABLE(CPanelDelay, wxPanel)
EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_PING_EXIT, CPanelDelay::OnPingExit)
EVT_COMMAND(wxID_ANY, ENUM_CUSTOMEVENT_PING, CPanelDelay::OnPingInfo)
END_EVENT_TABLE()


