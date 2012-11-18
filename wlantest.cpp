#include "wlantest.h"
static CThreadIperf *g_pThreadIperf;
/************************************************************************/
/* Main Page                                                                     */
/************************************************************************/
static CDialogWlanTest *g_pDialogWlanTest;
static inline wxString GetInputIp()
{
	return g_pDialogWlanTest->m_textCtrlClientIp->GetValue();
}

CDialogWlanTest::CDialogWlanTest( wxWindow *parent/*=NULL */ ) :
CDialogWlanTestBase(parent)
{
	g_pDialogWlanTest = this;
	m_pBandwidth = new CPanelBandwidth(m_notebook);
	m_pDelay = new CPanelDelayBase(m_notebook);
	m_pJiffer = new CPanelJitterBase(m_notebook);
	m_pPacketDropRate = new CPanelPackaetDrogRate(m_notebook);
	m_notebook->AddPage(m_pBandwidth, "Bandwidth");
	m_notebook->AddPage(m_pDelay, "Delay");
	m_notebook->AddPage(m_pJiffer, "Jiffer");
	m_notebook->AddPage(m_pPacketDropRate, "Packet Drop Rate");
}

CDialogWlanTest::~CDialogWlanTest()
{
	g_pDialogWlanTest = NULL;
	delete m_pBandwidth;
	delete m_pDelay;
	delete m_pJiffer;
	delete m_pPacketDropRate;
}

/************************************************************************/
/* Bandwith                                                                      */
/************************************************************************/
CPanelBandwidth::CPanelBandwidth( wxWindow *parent/*=NULL*/ ) :
CPanelBandwidthBase(parent)
{

}

void CPanelBandwidth::OnTestButtonClick( wxCommandEvent& event )
{
	if (!g_pThreadIperf) {
		m_textCtrlInfo->Clear();
		wxString strcmd = GetIperfPath() + "-c 192.168.1.1\n";
		g_pThreadIperf = new CThreadIperf(this, strcmd);
		g_pThreadIperf->Run();
		m_buttonTest->Disable();
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

BEGIN_EVENT_TABLE(CDialogWlanTest, wxDialog)
END_EVENT_TABLE()

