#ifndef _WLANTEST_H_
#define _WLANTEST_H_
#include "CMyFrame.h"
#include "utils.h"
/** @brief Bandwidth */
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

/** @brief Jitter */
class CPanelJitter:public CPanelJitterBase
{
public:
	CPanelJitter(wxWindow *parent=NULL);
protected:
	virtual void OnTestButtonClick( wxCommandEvent& event );

	void OnIperfInfo( wxCommandEvent& event );
	void OnIperfExit( wxCommandEvent& event );
private:
	DECLARE_EVENT_TABLE()
};

/** @brief Drop Rate */
class CPanelPackaetDrogRate:public CPanelPackaetDrogRateBase
{
public:
	CPanelPackaetDrogRate(wxWindow *parent=NULL);
protected:
	virtual void OnTestButtonClick( wxCommandEvent& event );

	void OnIperfInfo( wxCommandEvent& event );
	void OnIperfExit( wxCommandEvent& event );
private:
	DECLARE_EVENT_TABLE()
};

/** @brief Delay */
class CPanelDelay:public CPanelDelayBase
{
public:
	CPanelDelay(wxWindow *parent=NULL);
protected:
	virtual void OnTestButtonClick( wxCommandEvent& event );

	void OnPingInfo( wxCommandEvent& event );
	void OnPingExit( wxCommandEvent& event );
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
	CPanelDelay *m_pDelay;
	CPanelJitter *m_pJiffer;
	CPanelPackaetDrogRate *m_pPacketDropRate;
	wxIcon m_icon;

private:
	DECLARE_EVENT_TABLE()

	virtual void TCPUDPOnRadioBox( wxCommandEvent& event );

	virtual void OnNotebookPageChanged( wxNotebookEvent& event );

};

#endif