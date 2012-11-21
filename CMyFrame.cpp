///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "CMyFrame.h"

///////////////////////////////////////////////////////////////////////////

CMyFrame::CMyFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Ip:     "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer31->Add( m_staticText2, 0, wxALL, 8 );
	
	m_textCtrlIP = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), 0 );
	bSizer31->Add( m_textCtrlIP, 0, wxALL, 5 );
	
	bSizer8->Add( bSizer31, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer311;
	bSizer311 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("Times:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer311->Add( m_staticText21, 0, wxALL, 8 );
	
	m_textCtrlTimes = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), 0 );
	bSizer311->Add( m_textCtrlTimes, 0, wxALL, 5 );
	
	bSizer8->Add( bSizer311, 1, wxEXPAND, 5 );
	
	bSizer3->Add( bSizer8, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonPing = new wxButton( this, wxID_ANY, wxT("Ping"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonPing->SetDefault(); 
	bSizer4->Add( m_buttonPing, 0, wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxEXPAND|wxRIGHT, 5 );
	
	bSizer3->Add( bSizer4, 1, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	bSizer2->Add( bSizer3, 0, wxALL|wxEXPAND, 5 );
	
	m_textCtrlInfo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	bSizer2->Add( m_textCtrlInfo, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonPing->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMyFrame::OnBtnPingClick ), NULL, this );
}

CMyFrame::~CMyFrame()
{
	// Disconnect Events
	m_buttonPing->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMyFrame::OnBtnPingClick ), NULL, this );
	
}

CDialogPingBase::CDialogPingBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Ip:     "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer31->Add( m_staticText2, 0, wxALL, 8 );
	
	m_textCtrlIP = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), 0 );
	bSizer31->Add( m_textCtrlIP, 0, wxALL, 5 );
	
	bSizer8->Add( bSizer31, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer311;
	bSizer311 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("Times:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer311->Add( m_staticText21, 0, wxALL, 8 );
	
	m_textCtrlTimes = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), 0 );
	bSizer311->Add( m_textCtrlTimes, 0, wxALL, 5 );
	
	bSizer8->Add( bSizer311, 1, wxEXPAND, 5 );
	
	bSizer3->Add( bSizer8, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonPing = new wxButton( this, wxID_ANY, wxT("Ping"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonPing->SetDefault(); 
	bSizer4->Add( m_buttonPing, 0, wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxEXPAND|wxRIGHT, 5 );
	
	bSizer3->Add( bSizer4, 1, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	bSizer2->Add( bSizer3, 0, wxALL|wxEXPAND, 5 );
	
	m_textCtrlInfo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	bSizer2->Add( m_textCtrlInfo, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_buttonPing->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CDialogPingBase::OnBtnPingClick ), NULL, this );
}

CDialogPingBase::~CDialogPingBase()
{
	// Disconnect Events
	m_buttonPing->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CDialogPingBase::OnBtnPingClick ), NULL, this );
	
}

CDialogIperfBase::CDialogIperfBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer312;
	bSizer312 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText22 = new wxStaticText( this, wxID_ANY, wxT("CMDS:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	bSizer312->Add( m_staticText22, 0, wxALL, 8 );
	
	m_textCtrlCmds = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 250,-1 ), 0 );
	bSizer312->Add( m_textCtrlCmds, 0, wxALL, 5 );
	
	bSizer8->Add( bSizer312, 1, wxEXPAND, 5 );
	
	bSizer3->Add( bSizer8, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonCreate = new wxButton( this, wxID_ANY, wxT("Create"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonCreate->SetDefault(); 
	bSizer4->Add( m_buttonCreate, 0, wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL|wxEXPAND|wxRIGHT, 5 );
	
	m_buttonKill = new wxButton( this, wxID_ANY, wxT("Kill"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonKill->SetDefault(); 
	bSizer4->Add( m_buttonKill, 0, wxALL, 5 );
	
	bSizer3->Add( bSizer4, 1, wxALIGN_RIGHT|wxALL|wxEXPAND, 5 );
	
	bSizer2->Add( bSizer3, 0, wxALL|wxEXPAND, 5 );
	
	m_textCtrlInfo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	bSizer2->Add( m_textCtrlInfo, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( CDialogIperfBase::OnIdle ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( CDialogIperfBase::OnInitDialog ) );
	m_buttonCreate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CDialogIperfBase::OnBtnCreateClick ), NULL, this );
	m_buttonKill->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CDialogIperfBase::OnBtnKillClick ), NULL, this );
}

CDialogIperfBase::~CDialogIperfBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( CDialogIperfBase::OnIdle ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( CDialogIperfBase::OnInitDialog ) );
	m_buttonCreate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CDialogIperfBase::OnBtnCreateClick ), NULL, this );
	m_buttonKill->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CDialogIperfBase::OnBtnKillClick ), NULL, this );
	
}

CDialogWlanTestBase::CDialogWlanTestBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer72;
	bSizer72 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("CLIENT IP:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer72->Add( m_staticText21, 0, wxALL, 5 );
	
	m_textCtrlClientIp = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer72->Add( m_textCtrlClientIp, 1, wxALL, 5 );
	
	bSizer2->Add( bSizer72, 0, wxEXPAND, 5 );
	
	bSizerTCP_UDP = new wxBoxSizer( wxHORIZONTAL );
	
	wxString m_radioBox_TCPUDPChoices[] = { wxT("TCP"), wxT("UDP") };
	int m_radioBox_TCPUDPNChoices = sizeof( m_radioBox_TCPUDPChoices ) / sizeof( wxString );
	m_radioBox_TCPUDP = new wxRadioBox( this, wxID_ANY, wxT("TCP/UDP"), wxDefaultPosition, wxDefaultSize, m_radioBox_TCPUDPNChoices, m_radioBox_TCPUDPChoices, 2, wxRA_SPECIFY_COLS );
	m_radioBox_TCPUDP->SetSelection( 0 );
	bSizerTCP_UDP->Add( m_radioBox_TCPUDP, 0, wxALL, 5 );
	
	bSizer_UDPSpeed = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1Info = new wxStaticText( this, wxID_ANY, wxT("UDP Send Speed (Kbit/sec):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1Info->Wrap( -1 );
	bSizer_UDPSpeed->Add( m_staticText1Info, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_textCtrlUDPSpeed = new wxTextCtrl( this, wxID_ANY, wxT("10"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer_UDPSpeed->Add( m_textCtrlUDPSpeed, 0, wxALIGN_CENTER|wxALL, 5 );
	
	bSizerTCP_UDP->Add( bSizer_UDPSpeed, 0, wxEXPAND, 5 );
	
	bSizer2->Add( bSizerTCP_UDP, 0, wxEXPAND, 5 );
	
	m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	bSizer2->Add( m_notebook, 1, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( CDialogWlanTestBase::OnIdle ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( CDialogWlanTestBase::OnInitDialog ) );
	m_radioBox_TCPUDP->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( CDialogWlanTestBase::TCPUDPOnRadioBox ), NULL, this );
	m_notebook->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( CDialogWlanTestBase::OnNotebookPageChanged ), NULL, this );
}

CDialogWlanTestBase::~CDialogWlanTestBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( CDialogWlanTestBase::OnIdle ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( CDialogWlanTestBase::OnInitDialog ) );
	m_radioBox_TCPUDP->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( CDialogWlanTestBase::TCPUDPOnRadioBox ), NULL, this );
	m_notebook->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( CDialogWlanTestBase::OnNotebookPageChanged ), NULL, this );
	
}

CMainFrameBase::CMainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItemPing;
	m_menuItemPing = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Ping") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItemPing );
	
	wxMenuItem* m_menuItemIperf;
	m_menuItemIperf = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Iperf") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItemIperf );
	
	m_menubar1->Append( m_menu1, wxT("Test") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer271;
	bSizer271 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("GOOD GOOD STUDY!\nDAY    DAY   UP!"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	m_staticText9->SetFont( wxFont( 24, 70, 93, 92, true, wxEmptyString ) );
	
	bSizer271->Add( m_staticText9, 0, wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizer27->Add( bSizer271, 1, wxALIGN_CENTER_VERTICAL, 5 );
	
	this->SetSizer( bSizer27 );
	this->Layout();
	m_toolBar2 = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	m_buttonPing = new wxButton( m_toolBar2, wxID_ANY, wxT("Ping"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar2->AddControl( m_buttonPing );
	m_buttonIperf = new wxButton( m_toolBar2, wxID_ANY, wxT("Iperf"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar2->AddControl( m_buttonIperf );
	m_toolBar2->Realize(); 
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( m_menuItemPing->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CMainFrameBase::OnShowPingDialog ) );
	this->Connect( m_menuItemIperf->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CMainFrameBase::OnShowIperfDialog ) );
	m_buttonPing->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnBtnPingClick ), NULL, this );
	m_buttonIperf->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnBtnIperfCllick ), NULL, this );
}

CMainFrameBase::~CMainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CMainFrameBase::OnShowPingDialog ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( CMainFrameBase::OnShowIperfDialog ) );
	m_buttonPing->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnBtnPingClick ), NULL, this );
	m_buttonIperf->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CMainFrameBase::OnBtnIperfCllick ), NULL, this );
	
}

CPanelBandwidthBase::CPanelBandwidthBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonTest = new wxButton( this, wxID_ANY, wxT("Test"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonTest, 1, wxALL, 5 );
	
	bSizer2->Add( bSizer3, 0, wxALL|wxEXPAND, 5 );
	
	m_textCtrlInfo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	bSizer2->Add( m_textCtrlInfo, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	// Connect Events
	m_buttonTest->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPanelBandwidthBase::OnTestButtonClick ), NULL, this );
}

CPanelBandwidthBase::~CPanelBandwidthBase()
{
	// Disconnect Events
	m_buttonTest->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPanelBandwidthBase::OnTestButtonClick ), NULL, this );
	
}

CPanelDelayBase::CPanelDelayBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonTest = new wxButton( this, wxID_ANY, wxT("Test"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonTest, 1, wxALL, 5 );
	
	bSizer2->Add( bSizer3, 0, wxALL|wxEXPAND, 5 );
	
	m_textCtrlInfo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	bSizer2->Add( m_textCtrlInfo, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	// Connect Events
	m_buttonTest->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPanelDelayBase::OnTestButtonClick ), NULL, this );
}

CPanelDelayBase::~CPanelDelayBase()
{
	// Disconnect Events
	m_buttonTest->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPanelDelayBase::OnTestButtonClick ), NULL, this );
	
}

CPanelJitterBase::CPanelJitterBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonTest = new wxButton( this, wxID_ANY, wxT("Test"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonTest, 1, wxALL, 5 );
	
	bSizer2->Add( bSizer3, 0, wxALL|wxEXPAND, 5 );
	
	m_textCtrlInfo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	bSizer2->Add( m_textCtrlInfo, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	// Connect Events
	m_buttonTest->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPanelJitterBase::OnTestButtonClick ), NULL, this );
}

CPanelJitterBase::~CPanelJitterBase()
{
	// Disconnect Events
	m_buttonTest->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPanelJitterBase::OnTestButtonClick ), NULL, this );
	
}

CPanelPackaetDrogRateBase::CPanelPackaetDrogRateBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonTest = new wxButton( this, wxID_ANY, wxT("Test"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonTest, 1, wxALL, 5 );
	
	bSizer2->Add( bSizer3, 0, wxALL|wxEXPAND, 5 );
	
	m_textCtrlInfo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_WORDWRAP );
	bSizer2->Add( m_textCtrlInfo, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	// Connect Events
	m_buttonTest->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPanelPackaetDrogRateBase::OnTestButtonClick ), NULL, this );
}

CPanelPackaetDrogRateBase::~CPanelPackaetDrogRateBase()
{
	// Disconnect Events
	m_buttonTest->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CPanelPackaetDrogRateBase::OnTestButtonClick ), NULL, this );
	
}
