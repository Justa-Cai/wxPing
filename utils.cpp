#include "utils.h"
/************************************************************************/
/* Static Func                                                                     */
/************************************************************************/
wxString GetIperfPath()
{
	return wxGetCwd() + "/iperf/iperf.exe ";
}

/************************************************************************/
/* ping                                                                     */
/************************************************************************/
static wxWindow *g_pWindow = NULL;
static wxIPV4address *g_pIpAddress;
static wxString g_strIp;
static unsigned long g_pingTotal,g_pingSend,g_pingLost;
static unsigned long g_pingDelayTotal, g_pingDelayMin, g_pingDelayMax;

DEFINE_EVENT_TYPE(ENUM_CUSTOMEVENT_PING)
DEFINE_EVENT_TYPE(ENUM_CUSTOMEVENT_PING_EXIT)

DEFINE_EVENT_TYPE(ENUM_CUSTOMEVENT_IPERF_INFO)
DEFINE_EVENT_TYPE(ENUM_CUSTOMEVENT_IPERF_EXIT)

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

CPingThread::CPingThread( wxWindow *pWindow, wxString strOrigIp, int times/*=5*/ ) :m_pWindow(pWindow)
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

void * CPingThread::Entry()
{
	CPing ping;
	CPingReply pr1;

	g_pIpAddress->Hostname(m_strOrigIp);
	g_strIp = g_pIpAddress->IPAddress();
	ShowInfo(wxString::Format("[*] Ping (%s)%s\n", m_strOrigIp, g_strIp));

	ping.Ping1(g_strIp, pr1, ping_cb, m_times);

	return NULL;
}

void CPingThread::OnExit()
{
	ShowInfo(wxString::Format("Send Total:%d Send Succ:%d Lost:%d(%.2f%%)\nMin Delay:%dms Max delay:%dms Average delay:%dms", 
		g_pingTotal, g_pingSend, g_pingLost, g_pingLost/(float)g_pingTotal*100,
		g_pingDelayMin, g_pingDelayMax, g_pingDelayTotal/g_pingTotal));

	wxCommandEvent evt(ENUM_CUSTOMEVENT_PING_EXIT);
	wxPostEvent(m_pWindow->GetEventHandler(), evt);
}

void CPingThread::ShowInfo( wxString str )
{
	wxCommandEvent evt(ENUM_CUSTOMEVENT_PING);
	evt.SetString(str);
	wxPostEvent(m_pWindow->GetEventHandler(), evt);
}

/************************************************************************/
/* IPERF Process                                                                     */
/************************************************************************/
CProcessIperf::CProcessIperf( wxWindow *pWindow ) :wxProcess(pWindow)
,m_pWindow(pWindow)
{
	Redirect();
}

void CProcessIperf::OnTerminate( int pid, int status )
{
	if (m_pWindow) 
	{
		wxCommandEvent evt(ENUM_CUSTOMEVENT_IPERF_INFO);
		evt.SetString("* IPERF EXIT!\n");
		wxPostEvent(m_pWindow->GetEventHandler(), evt);
	}
}

/************************************************************************/
/* IPERF THREAD                                                                     */
/************************************************************************/

CThreadIperf::CThreadIperf( wxWindow *pWindow, wxString strCmds ):
wxThread(wxTHREAD_JOINABLE)
{
	Create();
	m_pWindow = pWindow;
	m_strCmds = strCmds;
	m_pProcessIperf = new CProcessIperf(m_pWindow);
	m_nPid =  wxExecute(m_strCmds, wxEXEC_ASYNC | wxEXEC_HIDE_CONSOLE, m_pProcessIperf);
}

void * CThreadIperf::Entry()
{
	if (m_nPid<=0) {
		SendInfo("Can't Create Process!\nCMDS:" + m_strCmds + "\n");
		return NULL;
	}
	SendInfo("* " + m_strCmds);

	wxInputStream *pErrorInput = m_pProcessIperf->GetErrorStream();
	wxInputStream *pStandInput = m_pProcessIperf->GetInputStream();
	// check process output
	while(!TestDestroy()) {


		if (m_pProcessIperf->IsErrorAvailable()) {
			wxCharBuffer buffer(4096);
			size_t offset = 0;
			while(pErrorInput->CanRead())
			{
				pErrorInput->Read(buffer.data()+offset, 1);
				offset++;
			}
			buffer.shrink(offset);
			SendInfo(buffer);
		}

		if (m_pProcessIperf->IsInputAvailable()) {
			wxCharBuffer buffer(4096);
			size_t offset = 0;
			while(pStandInput->CanRead())
			{
				pStandInput->Read(buffer.data()+offset, 1);
				offset++;
			}
			buffer.shrink(offset);

			SendInfo(buffer);
		}

		if (!m_pProcessIperf->Exists(m_nPid))
			break;
		Sleep(500);
	}

	if (m_pProcessIperf->Exists(m_nPid))
		m_pProcessIperf->Kill(m_nPid, wxSIGKILL);

	delete m_pProcessIperf;
	return NULL;
}

void CThreadIperf::OnExit()
{
	SendInfo("* Thread exit\n");
	wxCommandEvent evt(ENUM_CUSTOMEVENT_IPERF_EXIT);
	wxPostEvent(m_pWindow->GetEventHandler(), evt);
}

void CThreadIperf::SendInfo( wxString str )
{
	wxCommandEvent evt(ENUM_CUSTOMEVENT_IPERF_INFO);
	evt.SetString(str);
	wxPostEvent(m_pWindow->GetEventHandler(), evt);
}

