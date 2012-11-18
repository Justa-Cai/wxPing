#ifndef _WLANTEST_H_
#define _WLANTEST_H_
#include "CMyFrame.h"
#include "utils.h"

class CPanelBandwidth:public CPanelBandwidthBase
{
public:
	CPanelBandwidth(wxWindow *parent=NULL);
protected:
	virtual void OnTestButtonClick( wxCommandEvent& event );

	void OnIperfInfo( wxCommandEvent& event );
	void OnIperfExit( wxCommandEvent& event );
private:
	DECLARE_EVENT_TABLE()
};

class CDialogWlanTest: public CDialogWlanTestBase
{
public:
	CDialogWlanTest( wxWindow *parent=NULL);
	~CDialogWlanTest();

public:
	CPanelBandwidth *m_pBandwidth;
	CPanelDelayBase *m_pDelay;
	CPanelJitterBase *m_pJiffer;
	CPanelPackaetDrogRate *m_pPacketDropRate;

private:
	DECLARE_EVENT_TABLE()
};

#endif