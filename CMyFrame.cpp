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
