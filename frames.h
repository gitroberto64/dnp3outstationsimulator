///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/spinctrl.h>
#include <wx/choice.h>
#include <wx/scrolwin.h>
#include <wx/grid.h>
#include <wx/listbook.h>
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/combobox.h>
#include <wx/statline.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame
{
	private:

	protected:
		wxMenuBar* m_menubar1;
		wxMenu* m_menuFile;
		wxMenu* m_menuChannels;
		wxMenu* m_menuSlaves;
		wxMenu* m_menuPreference;
		wxMenu* m_menuHelp;
		wxPanel* m_panelMain;
		wxListBox* m_listBoxChannels;
		wxStaticBoxSizer* sbSizerNotebookSlaves;
		wxListBox* m_listBoxLog;
		wxStatusBar* m_statusBar1;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnMenuSelectionNew( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSelectionOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSelectionSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSelectionSaveAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSelectionExit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSelectionTCPServerAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSelectionSerialAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSelectionChannelEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSelectionChannelDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSelectionSlaveAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSelectionSlaveEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSelectionSlaveDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSelectionLogLev( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSelectionAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnListBoxChannels( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,500 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class PanelSlave
///////////////////////////////////////////////////////////////////////////////
class PanelSlave : public wxPanel
{
	private:

	protected:
		wxListbook* m_listbookObjects;
		wxPanel* m_panelConfig;
		wxScrolledWindow* m_scrolledWindow2;
		wxStaticText* m_staticTextSlaveName;
		wxStaticText* m_staticTextSlaveAddress;
		wxStaticText* m_staticTextMasterAddress;
		wxCheckBox* m_checkBoxUnsol;
		wxTextCtrl* m_textCtrl25;
		wxTextCtrl* m_textCtrl26;
		wxTextCtrl* m_textCtrl27;
		wxTextCtrl* m_textCtrl28;
		wxTextCtrl* m_textCtrl29;
		wxTextCtrl* m_textCtrl30;
		wxTextCtrl* m_textCtrl31;
		wxSpinCtrl* m_spinCtrlBinaryInput;
		wxSpinCtrl* m_spinCtrlDBit;
		wxSpinCtrl* m_spinCtrlAnalogInput;
		wxSpinCtrl* m_spinCtrlCounter;
		wxSpinCtrl* m_spinCtrlFCounter;
		wxSpinCtrl* m_spinCtrlBinaryOutput;
		wxSpinCtrl* m_spinCtrlAnalogOutput;
		wxChoice* m_choiceStaticBinary;
		wxChoice* m_choiceStaticDBit;
		wxChoice* m_choiceStaticAnalogInput;
		wxChoice* m_choiceStaticCounter;
		wxChoice* m_choiceStaticFCounter;
		wxChoice* m_choiceStaticBinaryOutput;
		wxChoice* m_choiceStaticAnalogOutput;
		wxChoice* m_choiceEventBinary;
		wxChoice* m_choiceEventDBit;
		wxChoice* m_choiceEventAnalogInput;
		wxChoice* m_choiceEventCounter;
		wxChoice* m_choiceEventFCounter;
		wxChoice* m_choiceEventBinaryOutput;
		wxChoice* m_choiceEventAnalogOutput;
		wxCheckBox* m_checkBoxRandom;
		wxPanel* m_panelBinaryIn;
		wxGrid* m_gridBinaryInput;
		wxPanel* m_panelDBinaryIn;
		wxGrid* m_gridDBinaryInput;
		wxPanel* m_panelAnalogIn;
		wxGrid* m_gridAnalogInput;
		wxPanel* m_panelCounter;
		wxGrid* m_gridCounter;
		wxPanel* m_panelFCounter;
		wxGrid* m_gridFCounter;
		wxPanel* m_panelBinaryOut;
		wxGrid* m_gridBinaryOut;
		wxPanel* m_panelAnalogOut;
		wxGrid* m_gridAnalogOut;
		wxListBox* m_listBoxSlave;
		wxButton* m_buttonSlaveStart;
		wxButton* m_buttonSlaveRestart;
		wxButton* m_buttonStop;
		wxButton* m_buttonSyncTime;

		// Virtual event handlers, override them in your derived class
		virtual void OnSpinCtrlBinaryInput( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpinCtrlDBinaryInput( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpinCtrlAnalogInput( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpinCtrlCounter( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpinCtrlFCounter( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpinCtrlBinaryOutput( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnSpinCtrlAnalogOutput( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnChoiceBinaryStatic( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceDBinaryStatic( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceAnalogStatic( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceCounterStatic( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceFCounterStatic( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceBinaryOutputStatic( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceAmalogOutputStatic( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceBinaryEvent( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceDBinaryEvent( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceAnalogEvent( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceCounterEvent( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceFCounterEvent( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceBinaryOutputEvent( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChoiceAnalogOutputEvent( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCheckBoxLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnGridCellChangeBinaryInput( wxGridEvent& event ) { event.Skip(); }
		virtual void OnGridCellChangeDBinaryInput( wxGridEvent& event ) { event.Skip(); }
		virtual void OnGridCellChangeAnalogInput( wxGridEvent& event ) { event.Skip(); }
		virtual void OnGridCellChangeCounter( wxGridEvent& event ) { event.Skip(); }
		virtual void OnGridCellChangeFrozenCounter( wxGridEvent& event ) { event.Skip(); }
		virtual void OnGridCellChangeBinaryOutputStatus( wxGridEvent& event ) { event.Skip(); }
		virtual void OnGridCellChangeAnalogOutputStatus( wxGridEvent& event ) { event.Skip(); }
		virtual void OnButtonClickSlaveStart( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickSlaveRestart( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickSlaveStop( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonSyncTimeClick( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxTextCtrl* m_textCtrlSlaveName;
		wxTextCtrl* m_textCtrlSlaveAddr;
		wxTextCtrl* m_textCtrlMasterAddr;

		PanelSlave( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 972,662 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~PanelSlave();

};

///////////////////////////////////////////////////////////////////////////////
/// Class SerialParamDialog
///////////////////////////////////////////////////////////////////////////////
class SerialParamDialog : public wxDialog
{
	private:

	protected:
		wxPanel* m_panel8;
		wxStaticText* m_staticText14;
		wxTextCtrl* m_textCtrlName;
		wxStaticText* m_staticText15;
		wxTextCtrl* m_textCtrlPort;
		wxStaticText* m_staticText16;
		wxTextCtrl* m_textCtrlBaud;
		wxStaticText* m_staticText17;
		wxTextCtrl* m_textCtrlDataBits;
		wxStaticText* m_staticText18;
		wxComboBox* m_comboBoxParity;
		wxStaticText* m_staticText19;
		wxComboBox* m_comboBoxStopBits;
		wxStaticText* m_staticText32;
		wxComboBox* m_comboBoxFlow;
		wxStaticLine* m_staticline7;
		wxStaticLine* m_staticline8;
		wxButton* m_buttonOK;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnButtonClickOK( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickCancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		SerialParamDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Serial Parameters"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );

		~SerialParamDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class TCPServerParamDialog
///////////////////////////////////////////////////////////////////////////////
class TCPServerParamDialog : public wxDialog
{
	private:

	protected:
		wxPanel* m_panel9;
		wxStaticText* m_staticText21;
		wxTextCtrl* m_textCtrlName;
		wxStaticText* m_staticText22;
		wxTextCtrl* m_textCtrlAddress;
		wxStaticText* m_staticText23;
		wxTextCtrl* m_textCtrlPort;
		wxStaticLine* m_staticline5;
		wxStaticLine* m_staticline6;
		wxButton* m_buttonOK;
		wxButton* m_buttonCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnButtonClickOK( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickCancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		TCPServerParamDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("TCP Server Parameters"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~TCPServerParamDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class StateDialog
///////////////////////////////////////////////////////////////////////////////
class StateDialog : public wxDialog
{
	private:

	protected:
		wxPanel* m_panelStateDialog;
		wxBoxSizer* bSizerStateDialog;
		wxBoxSizer* bSizerValue;
		wxStaticLine* m_staticline5;
		wxCheckBox* m_checkBoxQuality7;
		wxCheckBox* m_checkBoxQuality6;
		wxCheckBox* m_checkBoxQuality5;
		wxCheckBox* m_checkBoxQuality4;
		wxCheckBox* m_checkBoxQuality3;
		wxCheckBox* m_checkBoxQuality2;
		wxCheckBox* m_checkBoxQuality1;
		wxCheckBox* m_checkBoxQuality0;
		wxStaticLine* m_staticline51;
		wxStdDialogButtonSizer* m_sdbSizer2;
		wxButton* m_sdbSizer2OK;
		wxButton* m_sdbSizer2Apply;
		wxButton* m_sdbSizer2Cancel;

		// Virtual event handlers, override them in your derived class
		virtual void StateDialogOnApplyButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void StateDialogOnCancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void StateDialogOnOKButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		StateDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("State"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );

		~StateDialog();

};

