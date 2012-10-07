///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __CMYFRAME_H__
#define __CMYFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class CMyFrame
///////////////////////////////////////////////////////////////////////////////
class CMyFrame : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrlIP;
		wxStaticText* m_staticText21;
		wxTextCtrl* m_textCtrlTimes;
		wxButton* m_buttonPing;
		wxTextCtrl* m_textCtrlInfo;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnBtnPingClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		CMyFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("wxPing"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 703,643 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~CMyFrame();
	
};

#endif //__CMYFRAME_H__
