///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "frames.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	m_menubar1 = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* m_menuItemNew;
	m_menuItemNew = new wxMenuItem( m_menuFile, wxID_ANY, wxString( wxT("New") ) + wxT('\t') + wxT("Ctrl-N"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemNew );

	wxMenuItem* m_menuItemOpen;
	m_menuItemOpen = new wxMenuItem( m_menuFile, wxID_ANY, wxString( wxT("Open") ) + wxT('\t') + wxT("Ctrl-O"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemOpen );

	wxMenuItem* m_menuItemSave;
	m_menuItemSave = new wxMenuItem( m_menuFile, wxID_ANY, wxString( wxT("Save") ) + wxT('\t') + wxT("Ctrl-S"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemSave );

	wxMenuItem* m_menuItemSaveAs;
	m_menuItemSaveAs = new wxMenuItem( m_menuFile, wxID_ANY, wxString( wxT("Save as") ) + wxT('\t') + wxT("Ctrl-Shift-S"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemSaveAs );

	m_menuFile->AppendSeparator();

	m_menuFile->AppendSeparator();

	wxMenuItem* m_menuItemExit;
	m_menuItemExit = new wxMenuItem( m_menuFile, wxID_ANY, wxString( wxT("Exit") ) + wxT('\t') + wxT("Ctrl-Q"), wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemExit );

	m_menubar1->Append( m_menuFile, wxT("File") );

	m_menuChannels = new wxMenu();
	wxMenuItem* m_menuItemTCPServerAdd;
	m_menuItemTCPServerAdd = new wxMenuItem( m_menuChannels, wxID_ANY, wxString( wxT("Add TCP Server") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuChannels->Append( m_menuItemTCPServerAdd );

	wxMenuItem* m_menuItemSerialAdd;
	m_menuItemSerialAdd = new wxMenuItem( m_menuChannels, wxID_ANY, wxString( wxT("Add Serial") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuChannels->Append( m_menuItemSerialAdd );

	wxMenuItem* m_menuItemChannelEdit;
	m_menuItemChannelEdit = new wxMenuItem( m_menuChannels, wxID_ANY, wxString( wxT("Edit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuChannels->Append( m_menuItemChannelEdit );

	wxMenuItem* m_menuItemChannelDelete;
	m_menuItemChannelDelete = new wxMenuItem( m_menuChannels, wxID_ANY, wxString( wxT("Delete") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuChannels->Append( m_menuItemChannelDelete );

	m_menubar1->Append( m_menuChannels, wxT("Channels") );

	m_menuSlaves = new wxMenu();
	wxMenuItem* m_menuItemSlaveAdd;
	m_menuItemSlaveAdd = new wxMenuItem( m_menuSlaves, wxID_ANY, wxString( wxT("Add") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSlaves->Append( m_menuItemSlaveAdd );

	wxMenuItem* m_menuItemSlaveEdit;
	m_menuItemSlaveEdit = new wxMenuItem( m_menuSlaves, wxID_ANY, wxString( wxT("Edit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSlaves->Append( m_menuItemSlaveEdit );

	wxMenuItem* m_menuItemSlaveDelete;
	m_menuItemSlaveDelete = new wxMenuItem( m_menuSlaves, wxID_ANY, wxString( wxT("Delete") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuSlaves->Append( m_menuItemSlaveDelete );

	m_menubar1->Append( m_menuSlaves, wxT("Slaves") );

	m_menuPreference = new wxMenu();
	wxMenuItem* m_menuItemLogLev;
	m_menuItemLogLev = new wxMenuItem( m_menuPreference, wxID_ANY, wxString( wxT("Log level") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuPreference->Append( m_menuItemLogLev );

	m_menubar1->Append( m_menuPreference, wxT("Preferences") );

	m_menuHelp = new wxMenu();
	wxMenuItem* m_menuItemAbout;
	m_menuItemAbout = new wxMenuItem( m_menuHelp, wxID_ANY, wxString( wxT("About") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuHelp->Append( m_menuItemAbout );

	m_menubar1->Append( m_menuHelp, wxT("Help") );

	this->SetMenuBar( m_menubar1 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	m_panelMain = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_panelMain, wxID_ANY, wxT("Channels") ), wxVERTICAL );

	m_listBoxChannels = new wxListBox( sbSizer5->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	sbSizer5->Add( m_listBoxChannels, 1, wxALL|wxEXPAND, 0 );


	bSizer3->Add( sbSizer5, 1, wxEXPAND, 5 );

	sbSizerNotebookSlaves = new wxStaticBoxSizer( new wxStaticBox( m_panelMain, wxID_ANY, wxT("Slaves") ), wxVERTICAL );


	bSizer3->Add( sbSizerNotebookSlaves, 4, wxEXPAND, 0 );


	bSizer2->Add( bSizer3, 3, wxEXPAND, 0 );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panelMain, wxID_ANY, wxT("Log") ), wxVERTICAL );

	m_listBoxLog = new wxListBox( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	sbSizer1->Add( m_listBoxLog, 1, wxALL|wxEXPAND, 0 );


	bSizer2->Add( sbSizer1, 1, wxEXPAND, 0 );


	m_panelMain->SetSizer( bSizer2 );
	m_panelMain->Layout();
	bSizer2->Fit( m_panelMain );
	bSizer14->Add( m_panelMain, 1, wxEXPAND | wxALL, 0 );


	this->SetSizer( bSizer14 );
	this->Layout();
	m_statusBar1 = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame::OnClose ) );
	m_menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuSelectionNew ), this, m_menuItemNew->GetId());
	m_menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuSelectionOpen ), this, m_menuItemOpen->GetId());
	m_menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuSelectionSave ), this, m_menuItemSave->GetId());
	m_menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuSelectionSaveAs ), this, m_menuItemSaveAs->GetId());
	m_menuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuSelectionExit ), this, m_menuItemExit->GetId());
	m_menuChannels->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuSelectionTCPServerAdd ), this, m_menuItemTCPServerAdd->GetId());
	m_menuChannels->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuSelectionSerialAdd ), this, m_menuItemSerialAdd->GetId());
	m_menuChannels->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuSelectionChannelEdit ), this, m_menuItemChannelEdit->GetId());
	m_menuChannels->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuSelectionChannelDelete ), this, m_menuItemChannelDelete->GetId());
	m_menuSlaves->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuSelectionSlaveAdd ), this, m_menuItemSlaveAdd->GetId());
	m_menuSlaves->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuSelectionSlaveEdit ), this, m_menuItemSlaveEdit->GetId());
	m_menuSlaves->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuSelectionSlaveDelete ), this, m_menuItemSlaveDelete->GetId());
	m_menuPreference->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuSelectionLogLev ), this, m_menuItemLogLev->GetId());
	m_menuHelp->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuSelectionAbout ), this, m_menuItemAbout->GetId());
	m_listBoxChannels->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( MainFrame::OnListBoxChannels ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame::OnClose ) );
	m_listBoxChannels->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( MainFrame::OnListBoxChannels ), NULL, this );

}

PanelSlave::PanelSlave( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_listbookObjects = new wxListbook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_DEFAULT );
	m_panelConfig = new wxPanel( m_listbookObjects, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_scrolledWindow2 = new wxScrolledWindow( m_panelConfig, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxHSCROLL|wxVSCROLL );
	m_scrolledWindow2->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );

	m_staticTextSlaveName = new wxStaticText( m_scrolledWindow2, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSlaveName->Wrap( -1 );
	bSizer17->Add( m_staticTextSlaveName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlSlaveName = new wxTextCtrl( m_scrolledWindow2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 120,-1 ), 0 );
	bSizer17->Add( m_textCtrlSlaveName, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer17->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer7->Add( bSizer17, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );

	m_staticTextSlaveAddress = new wxStaticText( m_scrolledWindow2, wxID_ANY, wxT("Slave address:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextSlaveAddress->Wrap( -1 );
	bSizer18->Add( m_staticTextSlaveAddress, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlSlaveAddr = new wxTextCtrl( m_scrolledWindow2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer18->Add( m_textCtrlSlaveAddr, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticTextMasterAddress = new wxStaticText( m_scrolledWindow2, wxID_ANY, wxT("Master address:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextMasterAddress->Wrap( -1 );
	bSizer18->Add( m_staticTextMasterAddress, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlMasterAddr = new wxTextCtrl( m_scrolledWindow2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer18->Add( m_textCtrlMasterAddr, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );

	m_checkBoxUnsol = new wxCheckBox( m_scrolledWindow2, wxID_ANY, wxT("Unsolicited"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxUnsol->SetValue(true);
	bSizer20->Add( m_checkBoxUnsol, 1, wxALIGN_CENTER|wxALL, 5 );


	bSizer18->Add( bSizer20, 1, wxEXPAND, 5 );


	bSizer7->Add( bSizer18, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow2, wxID_ANY, wxT("Group") ), wxVERTICAL );

	m_textCtrl25 = new wxTextCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Binary Input:"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer6->Add( m_textCtrl25, 0, wxALL|wxEXPAND, 5 );

	m_textCtrl26 = new wxTextCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Double Binary Input:"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer6->Add( m_textCtrl26, 0, wxALL|wxEXPAND, 5 );

	m_textCtrl27 = new wxTextCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Analog Input:"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer6->Add( m_textCtrl27, 0, wxALL|wxEXPAND, 5 );

	m_textCtrl28 = new wxTextCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Counter:"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer6->Add( m_textCtrl28, 0, wxALL|wxEXPAND, 5 );

	m_textCtrl29 = new wxTextCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Frozen Counter:"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer6->Add( m_textCtrl29, 0, wxALL|wxEXPAND, 5 );

	m_textCtrl30 = new wxTextCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Binary Output:"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer6->Add( m_textCtrl30, 0, wxALL|wxEXPAND, 5 );

	m_textCtrl31 = new wxTextCtrl( sbSizer6->GetStaticBox(), wxID_ANY, wxT("Analog Output:"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer6->Add( m_textCtrl31, 0, wxALL|wxEXPAND, 5 );


	bSizer27->Add( sbSizer6, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow2, wxID_ANY, wxT("Count") ), wxVERTICAL );

	m_spinCtrlBinaryInput = new wxSpinCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 9999, 0 );
	sbSizer10->Add( m_spinCtrlBinaryInput, 0, wxALL|wxEXPAND, 5 );

	m_spinCtrlDBit = new wxSpinCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 9999, 0 );
	sbSizer10->Add( m_spinCtrlDBit, 0, wxALL|wxEXPAND, 5 );

	m_spinCtrlAnalogInput = new wxSpinCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 9999, 0 );
	sbSizer10->Add( m_spinCtrlAnalogInput, 0, wxALL|wxEXPAND, 5 );

	m_spinCtrlCounter = new wxSpinCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 9999, 0 );
	sbSizer10->Add( m_spinCtrlCounter, 0, wxALL|wxEXPAND, 5 );

	m_spinCtrlFCounter = new wxSpinCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 9999, 0 );
	sbSizer10->Add( m_spinCtrlFCounter, 0, wxALL|wxEXPAND, 5 );

	m_spinCtrlBinaryOutput = new wxSpinCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 9999, 0 );
	sbSizer10->Add( m_spinCtrlBinaryOutput, 0, wxALL|wxEXPAND, 5 );

	m_spinCtrlAnalogOutput = new wxSpinCtrl( sbSizer10->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 9999, 0 );
	sbSizer10->Add( m_spinCtrlAnalogOutput, 0, wxALL|wxEXPAND, 5 );


	bSizer27->Add( sbSizer10, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow2, wxID_ANY, wxT("Static Variation") ), wxVERTICAL );

	wxArrayString m_choiceStaticBinaryChoices;
	m_choiceStaticBinary = new wxChoice( sbSizer11->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceStaticBinaryChoices, 0 );
	m_choiceStaticBinary->SetSelection( 0 );
	sbSizer11->Add( m_choiceStaticBinary, 0, wxALL|wxEXPAND, 5 );

	wxArrayString m_choiceStaticDBitChoices;
	m_choiceStaticDBit = new wxChoice( sbSizer11->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceStaticDBitChoices, 0 );
	m_choiceStaticDBit->SetSelection( 0 );
	sbSizer11->Add( m_choiceStaticDBit, 0, wxALL|wxEXPAND, 5 );

	wxArrayString m_choiceStaticAnalogInputChoices;
	m_choiceStaticAnalogInput = new wxChoice( sbSizer11->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceStaticAnalogInputChoices, 0 );
	m_choiceStaticAnalogInput->SetSelection( 0 );
	sbSizer11->Add( m_choiceStaticAnalogInput, 0, wxALL|wxEXPAND, 5 );

	wxArrayString m_choiceStaticCounterChoices;
	m_choiceStaticCounter = new wxChoice( sbSizer11->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceStaticCounterChoices, 0 );
	m_choiceStaticCounter->SetSelection( 0 );
	sbSizer11->Add( m_choiceStaticCounter, 0, wxALL|wxEXPAND, 5 );

	wxArrayString m_choiceStaticFCounterChoices;
	m_choiceStaticFCounter = new wxChoice( sbSizer11->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceStaticFCounterChoices, 0 );
	m_choiceStaticFCounter->SetSelection( 0 );
	sbSizer11->Add( m_choiceStaticFCounter, 0, wxALL|wxEXPAND, 5 );

	wxArrayString m_choiceStaticBinaryOutputChoices;
	m_choiceStaticBinaryOutput = new wxChoice( sbSizer11->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceStaticBinaryOutputChoices, 0 );
	m_choiceStaticBinaryOutput->SetSelection( 0 );
	sbSizer11->Add( m_choiceStaticBinaryOutput, 0, wxALL|wxEXPAND, 5 );

	wxArrayString m_choiceStaticAnalogOutputChoices;
	m_choiceStaticAnalogOutput = new wxChoice( sbSizer11->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceStaticAnalogOutputChoices, 0 );
	m_choiceStaticAnalogOutput->SetSelection( 0 );
	sbSizer11->Add( m_choiceStaticAnalogOutput, 0, wxALL|wxEXPAND, 5 );


	bSizer27->Add( sbSizer11, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer12;
	sbSizer12 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow2, wxID_ANY, wxT("Event Variation") ), wxVERTICAL );

	wxArrayString m_choiceEventBinaryChoices;
	m_choiceEventBinary = new wxChoice( sbSizer12->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceEventBinaryChoices, 0 );
	m_choiceEventBinary->SetSelection( 0 );
	sbSizer12->Add( m_choiceEventBinary, 0, wxALL|wxEXPAND, 5 );

	wxArrayString m_choiceEventDBitChoices;
	m_choiceEventDBit = new wxChoice( sbSizer12->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceEventDBitChoices, 0 );
	m_choiceEventDBit->SetSelection( 0 );
	sbSizer12->Add( m_choiceEventDBit, 0, wxALL|wxEXPAND, 5 );

	wxArrayString m_choiceEventAnalogInputChoices;
	m_choiceEventAnalogInput = new wxChoice( sbSizer12->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceEventAnalogInputChoices, 0 );
	m_choiceEventAnalogInput->SetSelection( 0 );
	sbSizer12->Add( m_choiceEventAnalogInput, 0, wxALL|wxEXPAND, 5 );

	wxArrayString m_choiceEventCounterChoices;
	m_choiceEventCounter = new wxChoice( sbSizer12->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceEventCounterChoices, 0 );
	m_choiceEventCounter->SetSelection( 0 );
	sbSizer12->Add( m_choiceEventCounter, 0, wxALL|wxEXPAND, 5 );

	wxArrayString m_choiceEventFCounterChoices;
	m_choiceEventFCounter = new wxChoice( sbSizer12->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceEventFCounterChoices, 0 );
	m_choiceEventFCounter->SetSelection( 0 );
	sbSizer12->Add( m_choiceEventFCounter, 0, wxALL|wxEXPAND, 5 );

	wxArrayString m_choiceEventBinaryOutputChoices;
	m_choiceEventBinaryOutput = new wxChoice( sbSizer12->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceEventBinaryOutputChoices, 0 );
	m_choiceEventBinaryOutput->SetSelection( 0 );
	sbSizer12->Add( m_choiceEventBinaryOutput, 0, wxALL|wxEXPAND, 5 );

	wxArrayString m_choiceEventAnalogOutputChoices;
	m_choiceEventAnalogOutput = new wxChoice( sbSizer12->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceEventAnalogOutputChoices, 0 );
	m_choiceEventAnalogOutput->SetSelection( 0 );
	sbSizer12->Add( m_choiceEventAnalogOutput, 0, wxALL|wxEXPAND, 5 );


	bSizer27->Add( sbSizer12, 1, wxEXPAND, 5 );


	bSizer7->Add( bSizer27, 0, wxALL|wxEXPAND, 5 );


	m_scrolledWindow2->SetSizer( bSizer7 );
	m_scrolledWindow2->Layout();
	bSizer7->Fit( m_scrolledWindow2 );
	bSizer4->Add( m_scrolledWindow2, 1, wxALL|wxEXPAND, 5 );


	m_panelConfig->SetSizer( bSizer4 );
	m_panelConfig->Layout();
	bSizer4->Fit( m_panelConfig );
	m_listbookObjects->AddPage( m_panelConfig, wxT("Config"), true );
	m_panelBinaryIn = new wxPanel( m_listbookObjects, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_gridBinaryInput = new wxGrid( m_panelBinaryIn, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_gridBinaryInput->CreateGrid( 0, 5 );
	m_gridBinaryInput->EnableEditing( true );
	m_gridBinaryInput->EnableGridLines( true );
	m_gridBinaryInput->EnableDragGridSize( false );
	m_gridBinaryInput->SetMargins( 0, 0 );

	// Columns
	m_gridBinaryInput->SetColSize( 0, 60 );
	m_gridBinaryInput->SetColSize( 1, 140 );
	m_gridBinaryInput->SetColSize( 2, 70 );
	m_gridBinaryInput->SetColSize( 3, 400 );
	m_gridBinaryInput->EnableDragColMove( false );
	m_gridBinaryInput->EnableDragColSize( true );
	m_gridBinaryInput->SetColLabelValue( 0, wxT("Index") );
	m_gridBinaryInput->SetColLabelValue( 1, wxT("Description") );
	m_gridBinaryInput->SetColLabelValue( 2, wxT("State") );
	m_gridBinaryInput->SetColLabelValue( 3, wxT("Flags") );
	m_gridBinaryInput->SetColLabelValue( 4, wxT("Random") );
	m_gridBinaryInput->SetColLabelSize( 30 );
	m_gridBinaryInput->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_gridBinaryInput->EnableDragRowSize( true );
	m_gridBinaryInput->SetRowLabelSize( 50 );
	m_gridBinaryInput->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_gridBinaryInput->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer5->Add( m_gridBinaryInput, 1, wxALL|wxEXPAND, 0 );


	m_panelBinaryIn->SetSizer( bSizer5 );
	m_panelBinaryIn->Layout();
	bSizer5->Fit( m_panelBinaryIn );
	m_listbookObjects->AddPage( m_panelBinaryIn, wxT("Binary input"), false );
	m_panelDBinaryIn = new wxPanel( m_listbookObjects, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxVERTICAL );

	m_gridDBinaryInput = new wxGrid( m_panelDBinaryIn, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_gridDBinaryInput->CreateGrid( 0, 5 );
	m_gridDBinaryInput->EnableEditing( true );
	m_gridDBinaryInput->EnableGridLines( true );
	m_gridDBinaryInput->EnableDragGridSize( false );
	m_gridDBinaryInput->SetMargins( 0, 0 );

	// Columns
	m_gridDBinaryInput->SetColSize( 0, 60 );
	m_gridDBinaryInput->SetColSize( 1, 140 );
	m_gridDBinaryInput->SetColSize( 2, 140 );
	m_gridDBinaryInput->SetColSize( 3, 400 );
	m_gridDBinaryInput->EnableDragColMove( false );
	m_gridDBinaryInput->EnableDragColSize( true );
	m_gridDBinaryInput->SetColLabelValue( 0, wxT("Index") );
	m_gridDBinaryInput->SetColLabelValue( 1, wxT("Description") );
	m_gridDBinaryInput->SetColLabelValue( 2, wxT("State") );
	m_gridDBinaryInput->SetColLabelValue( 3, wxT("Flags") );
	m_gridDBinaryInput->SetColLabelValue( 4, wxT("Random") );
	m_gridDBinaryInput->SetColLabelSize( 30 );
	m_gridDBinaryInput->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_gridDBinaryInput->EnableDragRowSize( true );
	m_gridDBinaryInput->SetRowLabelSize( 50 );
	m_gridDBinaryInput->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_gridDBinaryInput->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer51->Add( m_gridDBinaryInput, 1, wxALL|wxEXPAND, 0 );


	m_panelDBinaryIn->SetSizer( bSizer51 );
	m_panelDBinaryIn->Layout();
	bSizer51->Fit( m_panelDBinaryIn );
	m_listbookObjects->AddPage( m_panelDBinaryIn, wxT("DBinary input"), false );
	m_panelAnalogIn = new wxPanel( m_listbookObjects, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );

	m_gridAnalogInput = new wxGrid( m_panelAnalogIn, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_gridAnalogInput->CreateGrid( 0, 5 );
	m_gridAnalogInput->EnableEditing( true );
	m_gridAnalogInput->EnableGridLines( true );
	m_gridAnalogInput->EnableDragGridSize( false );
	m_gridAnalogInput->SetMargins( 0, 0 );

	// Columns
	m_gridAnalogInput->SetColSize( 0, 60 );
	m_gridAnalogInput->SetColSize( 1, 130 );
	m_gridAnalogInput->SetColSize( 2, 100 );
	m_gridAnalogInput->SetColSize( 3, 400 );
	m_gridAnalogInput->EnableDragColMove( false );
	m_gridAnalogInput->EnableDragColSize( true );
	m_gridAnalogInput->SetColLabelValue( 0, wxT("Index") );
	m_gridAnalogInput->SetColLabelValue( 1, wxT("Description") );
	m_gridAnalogInput->SetColLabelValue( 2, wxT("State") );
	m_gridAnalogInput->SetColLabelValue( 3, wxT("Flags") );
	m_gridAnalogInput->SetColLabelValue( 4, wxT("Random") );
	m_gridAnalogInput->SetColLabelSize( 30 );
	m_gridAnalogInput->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_gridAnalogInput->EnableDragRowSize( true );
	m_gridAnalogInput->SetRowLabelSize( 50 );
	m_gridAnalogInput->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_gridAnalogInput->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer8->Add( m_gridAnalogInput, 1, wxALL|wxEXPAND, 0 );


	m_panelAnalogIn->SetSizer( bSizer8 );
	m_panelAnalogIn->Layout();
	bSizer8->Fit( m_panelAnalogIn );
	m_listbookObjects->AddPage( m_panelAnalogIn, wxT("Analog input"), false );
	m_panelCounter = new wxPanel( m_listbookObjects, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer91;
	bSizer91 = new wxBoxSizer( wxVERTICAL );

	m_gridCounter = new wxGrid( m_panelCounter, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_gridCounter->CreateGrid( 0, 5 );
	m_gridCounter->EnableEditing( true );
	m_gridCounter->EnableGridLines( true );
	m_gridCounter->EnableDragGridSize( false );
	m_gridCounter->SetMargins( 0, 0 );

	// Columns
	m_gridCounter->SetColSize( 0, 60 );
	m_gridCounter->SetColSize( 1, 140 );
	m_gridCounter->SetColSize( 2, 100 );
	m_gridCounter->SetColSize( 3, 400 );
	m_gridCounter->EnableDragColMove( false );
	m_gridCounter->EnableDragColSize( true );
	m_gridCounter->SetColLabelValue( 0, wxT("Index") );
	m_gridCounter->SetColLabelValue( 1, wxT("Description") );
	m_gridCounter->SetColLabelValue( 2, wxT("State") );
	m_gridCounter->SetColLabelValue( 3, wxT("Flags") );
	m_gridCounter->SetColLabelValue( 4, wxT("Increment") );
	m_gridCounter->SetColLabelSize( 30 );
	m_gridCounter->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_gridCounter->EnableDragRowSize( true );
	m_gridCounter->SetRowLabelSize( 50 );
	m_gridCounter->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_gridCounter->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer91->Add( m_gridCounter, 1, wxALL|wxEXPAND, 0 );


	m_panelCounter->SetSizer( bSizer91 );
	m_panelCounter->Layout();
	bSizer91->Fit( m_panelCounter );
	m_listbookObjects->AddPage( m_panelCounter, wxT("Counter"), false );
	m_panelFCounter = new wxPanel( m_listbookObjects, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer912;
	bSizer912 = new wxBoxSizer( wxVERTICAL );

	m_gridFCounter = new wxGrid( m_panelFCounter, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_gridFCounter->CreateGrid( 0, 4 );
	m_gridFCounter->EnableEditing( true );
	m_gridFCounter->EnableGridLines( true );
	m_gridFCounter->EnableDragGridSize( false );
	m_gridFCounter->SetMargins( 0, 0 );

	// Columns
	m_gridFCounter->SetColSize( 0, 60 );
	m_gridFCounter->SetColSize( 1, 140 );
	m_gridFCounter->SetColSize( 2, 100 );
	m_gridFCounter->SetColSize( 3, 400 );
	m_gridFCounter->EnableDragColMove( false );
	m_gridFCounter->EnableDragColSize( true );
	m_gridFCounter->SetColLabelValue( 0, wxT("Index") );
	m_gridFCounter->SetColLabelValue( 1, wxT("Description") );
	m_gridFCounter->SetColLabelValue( 2, wxT("State") );
	m_gridFCounter->SetColLabelValue( 3, wxT("Flags") );
	m_gridFCounter->SetColLabelSize( 30 );
	m_gridFCounter->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_gridFCounter->EnableDragRowSize( true );
	m_gridFCounter->SetRowLabelSize( 50 );
	m_gridFCounter->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_gridFCounter->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer912->Add( m_gridFCounter, 1, wxALL|wxEXPAND, 0 );


	m_panelFCounter->SetSizer( bSizer912 );
	m_panelFCounter->Layout();
	bSizer912->Fit( m_panelFCounter );
	m_listbookObjects->AddPage( m_panelFCounter, wxT("Frozen counter"), false );
	m_panelBinaryOut = new wxPanel( m_listbookObjects, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer911;
	bSizer911 = new wxBoxSizer( wxVERTICAL );

	m_gridBinaryOut = new wxGrid( m_panelBinaryOut, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_gridBinaryOut->CreateGrid( 0, 4 );
	m_gridBinaryOut->EnableEditing( true );
	m_gridBinaryOut->EnableGridLines( true );
	m_gridBinaryOut->EnableDragGridSize( false );
	m_gridBinaryOut->SetMargins( 0, 0 );

	// Columns
	m_gridBinaryOut->SetColSize( 0, 60 );
	m_gridBinaryOut->SetColSize( 1, 140 );
	m_gridBinaryOut->SetColSize( 2, 100 );
	m_gridBinaryOut->SetColSize( 3, 400 );
	m_gridBinaryOut->EnableDragColMove( false );
	m_gridBinaryOut->EnableDragColSize( true );
	m_gridBinaryOut->SetColLabelValue( 0, wxT("Index") );
	m_gridBinaryOut->SetColLabelValue( 1, wxT("Description") );
	m_gridBinaryOut->SetColLabelValue( 2, wxT("State") );
	m_gridBinaryOut->SetColLabelValue( 3, wxT("Flags") );
	m_gridBinaryOut->SetColLabelSize( 30 );
	m_gridBinaryOut->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_gridBinaryOut->EnableDragRowSize( true );
	m_gridBinaryOut->SetRowLabelSize( 50 );
	m_gridBinaryOut->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_gridBinaryOut->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer911->Add( m_gridBinaryOut, 1, wxALL|wxEXPAND, 0 );


	m_panelBinaryOut->SetSizer( bSizer911 );
	m_panelBinaryOut->Layout();
	bSizer911->Fit( m_panelBinaryOut );
	m_listbookObjects->AddPage( m_panelBinaryOut, wxT("Binary output"), false );
	m_panelAnalogOut = new wxPanel( m_listbookObjects, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9111;
	bSizer9111 = new wxBoxSizer( wxVERTICAL );

	m_gridAnalogOut = new wxGrid( m_panelAnalogOut, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	m_gridAnalogOut->CreateGrid( 0, 4 );
	m_gridAnalogOut->EnableEditing( true );
	m_gridAnalogOut->EnableGridLines( true );
	m_gridAnalogOut->EnableDragGridSize( false );
	m_gridAnalogOut->SetMargins( 0, 0 );

	// Columns
	m_gridAnalogOut->SetColSize( 0, 60 );
	m_gridAnalogOut->SetColSize( 1, 140 );
	m_gridAnalogOut->SetColSize( 2, 100 );
	m_gridAnalogOut->SetColSize( 3, 400 );
	m_gridAnalogOut->EnableDragColMove( false );
	m_gridAnalogOut->EnableDragColSize( true );
	m_gridAnalogOut->SetColLabelValue( 0, wxT("Index") );
	m_gridAnalogOut->SetColLabelValue( 1, wxT("Description") );
	m_gridAnalogOut->SetColLabelValue( 2, wxT("State") );
	m_gridAnalogOut->SetColLabelValue( 3, wxT("Flags") );
	m_gridAnalogOut->SetColLabelSize( 30 );
	m_gridAnalogOut->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	m_gridAnalogOut->EnableDragRowSize( true );
	m_gridAnalogOut->SetRowLabelSize( 50 );
	m_gridAnalogOut->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	m_gridAnalogOut->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer9111->Add( m_gridAnalogOut, 1, wxALL|wxEXPAND, 0 );


	m_panelAnalogOut->SetSizer( bSizer9111 );
	m_panelAnalogOut->Layout();
	bSizer9111->Fit( m_panelAnalogOut );
	m_listbookObjects->AddPage( m_panelAnalogOut, wxT("Analog output"), false );
	#ifdef __WXGTK__ // Small icon style not supported in GTK
	wxListView* m_listbookObjectsListView = m_listbookObjects->GetListView();
	long m_listbookObjectsFlags = m_listbookObjectsListView->GetWindowStyleFlag();
	if( m_listbookObjectsFlags & wxLC_SMALL_ICON )
	{
		m_listbookObjectsFlags = ( m_listbookObjectsFlags & ~wxLC_SMALL_ICON ) | wxLC_ICON;
	}
	m_listbookObjectsListView->SetWindowStyleFlag( m_listbookObjectsFlags );
	#endif

	bSizer6->Add( m_listbookObjects, 4, wxEXPAND | wxALL, 1 );

	m_listBoxSlave = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer6->Add( m_listBoxSlave, 1, wxALL|wxEXPAND, 1 );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonSlaveStart = new wxButton( this, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_buttonSlaveStart, 1, wxALL, 1 );

	m_buttonSlaveRestart = new wxButton( this, wxID_ANY, wxT("Restart"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_buttonSlaveRestart, 1, wxALL, 1 );

	m_buttonStop = new wxButton( this, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_buttonStop, 1, wxALL, 1 );

	m_buttonSyncTime = new wxButton( this, wxID_ANY, wxT("Need Time Sync"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_buttonSyncTime, 1, wxALL, 1 );


	bSizer6->Add( bSizer9, 0, wxEXPAND, 0 );


	this->SetSizer( bSizer6 );
	this->Layout();

	// Connect Events
	m_spinCtrlBinaryInput->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PanelSlave::OnSpinCtrlBinaryInput ), NULL, this );
	m_spinCtrlDBit->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PanelSlave::OnSpinCtrlDBinaryInput ), NULL, this );
	m_spinCtrlAnalogInput->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PanelSlave::OnSpinCtrlAnalogInput ), NULL, this );
	m_spinCtrlCounter->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PanelSlave::OnSpinCtrlCounter ), NULL, this );
	m_spinCtrlFCounter->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PanelSlave::OnSpinCtrlFCounter ), NULL, this );
	m_spinCtrlBinaryOutput->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PanelSlave::OnSpinCtrlBinaryOutput ), NULL, this );
	m_spinCtrlAnalogOutput->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PanelSlave::OnSpinCtrlAnalogOutput ), NULL, this );
	m_choiceStaticBinary->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceBinaryStatic ), NULL, this );
	m_choiceStaticDBit->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceDBinaryStatic ), NULL, this );
	m_choiceStaticAnalogInput->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceAnalogStatic ), NULL, this );
	m_choiceStaticCounter->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceCounterStatic ), NULL, this );
	m_choiceStaticFCounter->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceFCounterStatic ), NULL, this );
	m_choiceStaticBinaryOutput->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceBinaryOutputStatic ), NULL, this );
	m_choiceStaticAnalogOutput->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceAmalogOutputStatic ), NULL, this );
	m_choiceEventBinary->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceBinaryEvent ), NULL, this );
	m_choiceEventDBit->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceDBinaryEvent ), NULL, this );
	m_choiceEventAnalogInput->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceAnalogEvent ), NULL, this );
	m_choiceEventCounter->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceCounterEvent ), NULL, this );
	m_choiceEventFCounter->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceFCounterEvent ), NULL, this );
	m_choiceEventBinaryOutput->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceBinaryOutputEvent ), NULL, this );
	m_choiceEventAnalogOutput->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceAnalogOutputEvent ), NULL, this );
	m_gridBinaryInput->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( PanelSlave::OnGridCellChangeBinaryInput ), NULL, this );
	m_gridDBinaryInput->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( PanelSlave::OnGridCellChangeDBinaryInput ), NULL, this );
	m_gridAnalogInput->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( PanelSlave::OnGridCellChangeAnalogInput ), NULL, this );
	m_gridCounter->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( PanelSlave::OnGridCellChangeCounter ), NULL, this );
	m_gridFCounter->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( PanelSlave::OnGridCellChangeFrozenCounter ), NULL, this );
	m_gridBinaryOut->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( PanelSlave::OnGridCellChangeBinaryOutputStatus ), NULL, this );
	m_gridAnalogOut->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( PanelSlave::OnGridCellChangeAnalogOutputStatus ), NULL, this );
	m_buttonSlaveStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSlave::OnButtonClickSlaveStart ), NULL, this );
	m_buttonSlaveRestart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSlave::OnButtonClickSlaveRestart ), NULL, this );
	m_buttonStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSlave::OnButtonClickSlaveStop ), NULL, this );
	m_buttonSyncTime->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSlave::OnButtonSyncTimeClick ), NULL, this );
}

PanelSlave::~PanelSlave()
{
	// Disconnect Events
	m_spinCtrlBinaryInput->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PanelSlave::OnSpinCtrlBinaryInput ), NULL, this );
	m_spinCtrlDBit->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PanelSlave::OnSpinCtrlDBinaryInput ), NULL, this );
	m_spinCtrlAnalogInput->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PanelSlave::OnSpinCtrlAnalogInput ), NULL, this );
	m_spinCtrlCounter->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PanelSlave::OnSpinCtrlCounter ), NULL, this );
	m_spinCtrlFCounter->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PanelSlave::OnSpinCtrlFCounter ), NULL, this );
	m_spinCtrlBinaryOutput->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PanelSlave::OnSpinCtrlBinaryOutput ), NULL, this );
	m_spinCtrlAnalogOutput->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PanelSlave::OnSpinCtrlAnalogOutput ), NULL, this );
	m_choiceStaticBinary->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceBinaryStatic ), NULL, this );
	m_choiceStaticDBit->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceDBinaryStatic ), NULL, this );
	m_choiceStaticAnalogInput->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceAnalogStatic ), NULL, this );
	m_choiceStaticCounter->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceCounterStatic ), NULL, this );
	m_choiceStaticFCounter->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceFCounterStatic ), NULL, this );
	m_choiceStaticBinaryOutput->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceBinaryOutputStatic ), NULL, this );
	m_choiceStaticAnalogOutput->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceAmalogOutputStatic ), NULL, this );
	m_choiceEventBinary->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceBinaryEvent ), NULL, this );
	m_choiceEventDBit->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceDBinaryEvent ), NULL, this );
	m_choiceEventAnalogInput->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceAnalogEvent ), NULL, this );
	m_choiceEventCounter->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceCounterEvent ), NULL, this );
	m_choiceEventFCounter->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceFCounterEvent ), NULL, this );
	m_choiceEventBinaryOutput->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceBinaryOutputEvent ), NULL, this );
	m_choiceEventAnalogOutput->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelSlave::OnChoiceAnalogOutputEvent ), NULL, this );
	m_gridBinaryInput->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( PanelSlave::OnGridCellChangeBinaryInput ), NULL, this );
	m_gridDBinaryInput->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( PanelSlave::OnGridCellChangeDBinaryInput ), NULL, this );
	m_gridAnalogInput->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( PanelSlave::OnGridCellChangeAnalogInput ), NULL, this );
	m_gridCounter->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( PanelSlave::OnGridCellChangeCounter ), NULL, this );
	m_gridFCounter->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( PanelSlave::OnGridCellChangeFrozenCounter ), NULL, this );
	m_gridBinaryOut->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( PanelSlave::OnGridCellChangeBinaryOutputStatus ), NULL, this );
	m_gridAnalogOut->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( PanelSlave::OnGridCellChangeAnalogOutputStatus ), NULL, this );
	m_buttonSlaveStart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSlave::OnButtonClickSlaveStart ), NULL, this );
	m_buttonSlaveRestart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSlave::OnButtonClickSlaveRestart ), NULL, this );
	m_buttonStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSlave::OnButtonClickSlaveStop ), NULL, this );
	m_buttonSyncTime->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelSlave::OnButtonSyncTimeClick ), NULL, this );

}

SerialParamDialog::SerialParamDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	m_panel8 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 9, 2, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText14 = new wxStaticText( m_panel8, wxID_ANY, wxT("Channel Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer2->Add( m_staticText14, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlName = new wxTextCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0 );
	fgSizer2->Add( m_textCtrlName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticText15 = new wxStaticText( m_panel8, wxID_ANY, wxT("Port:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer2->Add( m_staticText15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlPort = new wxTextCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0 );
	fgSizer2->Add( m_textCtrlPort, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticText16 = new wxStaticText( m_panel8, wxID_ANY, wxT("Baud:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer2->Add( m_staticText16, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlBaud = new wxTextCtrl( m_panel8, wxID_ANY, wxT("9600"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	fgSizer2->Add( m_textCtrlBaud, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticText17 = new wxStaticText( m_panel8, wxID_ANY, wxT("Data Bits:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	fgSizer2->Add( m_staticText17, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlDataBits = new wxTextCtrl( m_panel8, wxID_ANY, wxT("8"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	fgSizer2->Add( m_textCtrlDataBits, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticText18 = new wxStaticText( m_panel8, wxID_ANY, wxT("Parity"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer2->Add( m_staticText18, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_comboBoxParity = new wxComboBox( m_panel8, wxID_ANY, wxT("none"), wxDefaultPosition, wxSize( 100,-1 ), 0, NULL, 0 );
	m_comboBoxParity->Append( wxT("none") );
	m_comboBoxParity->Append( wxT("even") );
	m_comboBoxParity->Append( wxT("odd") );
	fgSizer2->Add( m_comboBoxParity, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticText19 = new wxStaticText( m_panel8, wxID_ANY, wxT("Stop Bits:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	fgSizer2->Add( m_staticText19, 0, wxALL, 5 );

	m_comboBoxStopBits = new wxComboBox( m_panel8, wxID_ANY, wxT("1"), wxDefaultPosition, wxSize( 100,-1 ), 0, NULL, 0 );
	m_comboBoxStopBits->Append( wxT("1") );
	m_comboBoxStopBits->Append( wxT("2") );
	fgSizer2->Add( m_comboBoxStopBits, 0, wxALL, 5 );

	m_staticText32 = new wxStaticText( m_panel8, wxID_ANY, wxT("Flow Control:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	fgSizer2->Add( m_staticText32, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_comboBoxFlow = new wxComboBox( m_panel8, wxID_ANY, wxT("none"), wxDefaultPosition, wxSize( 100,-1 ), 0, NULL, 0 );
	m_comboBoxFlow->Append( wxT("none") );
	m_comboBoxFlow->Append( wxT("hardware") );
	m_comboBoxFlow->Append( wxT("xonxoff") );
	fgSizer2->Add( m_comboBoxFlow, 0, wxALL, 5 );

	m_staticline7 = new wxStaticLine( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer2->Add( m_staticline7, 0, wxEXPAND | wxALL, 0 );

	m_staticline8 = new wxStaticLine( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer2->Add( m_staticline8, 0, wxEXPAND | wxALL, 0 );

	m_buttonOK = new wxButton( m_panel8, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );

	m_buttonOK->SetDefault();
	fgSizer2->Add( m_buttonOK, 0, wxALIGN_CENTER|wxALL, 5 );

	m_buttonCancel = new wxButton( m_panel8, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_buttonCancel, 0, wxALIGN_CENTER|wxALL, 5 );


	m_panel8->SetSizer( fgSizer2 );
	m_panel8->Layout();
	fgSizer2->Fit( m_panel8 );
	bSizer14->Add( m_panel8, 1, wxEXPAND | wxALL, 0 );


	this->SetSizer( bSizer14 );
	this->Layout();
	bSizer14->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	m_buttonOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SerialParamDialog::OnButtonClickOK ), NULL, this );
	m_buttonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SerialParamDialog::OnButtonClickCancel ), NULL, this );
}

SerialParamDialog::~SerialParamDialog()
{
	// Disconnect Events
	m_buttonOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SerialParamDialog::OnButtonClickOK ), NULL, this );
	m_buttonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SerialParamDialog::OnButtonClickCancel ), NULL, this );

}

TCPServerParamDialog::TCPServerParamDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	m_panel9 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 5, 2, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText21 = new wxStaticText( m_panel9, wxID_ANY, wxT("Channel Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer3->Add( m_staticText21, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlName = new wxTextCtrl( m_panel9, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0 );
	fgSizer3->Add( m_textCtrlName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticText22 = new wxStaticText( m_panel9, wxID_ANY, wxT("Address:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer3->Add( m_staticText22, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlAddress = new wxTextCtrl( m_panel9, wxID_ANY, wxT("0.0.0.0"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	fgSizer3->Add( m_textCtrlAddress, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticText23 = new wxStaticText( m_panel9, wxID_ANY, wxT("Port"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer3->Add( m_staticText23, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_textCtrlPort = new wxTextCtrl( m_panel9, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 100,-1 ), 0 );
	fgSizer3->Add( m_textCtrlPort, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_staticline5 = new wxStaticLine( m_panel9, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer3->Add( m_staticline5, 0, wxEXPAND | wxALL, 0 );

	m_staticline6 = new wxStaticLine( m_panel9, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer3->Add( m_staticline6, 0, wxEXPAND | wxALL, 0 );

	m_buttonOK = new wxButton( m_panel9, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );

	m_buttonOK->SetDefault();
	fgSizer3->Add( m_buttonOK, 0, wxALIGN_CENTER|wxALL, 5 );

	m_buttonCancel = new wxButton( m_panel9, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_buttonCancel, 0, wxALIGN_CENTER|wxALL, 5 );


	m_panel9->SetSizer( fgSizer3 );
	m_panel9->Layout();
	fgSizer3->Fit( m_panel9 );
	bSizer14->Add( m_panel9, 1, wxEXPAND | wxALL, 0 );


	this->SetSizer( bSizer14 );
	this->Layout();
	bSizer14->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	m_buttonOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TCPServerParamDialog::OnButtonClickOK ), NULL, this );
	m_buttonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TCPServerParamDialog::OnButtonClickCancel ), NULL, this );
}

TCPServerParamDialog::~TCPServerParamDialog()
{
	// Disconnect Events
	m_buttonOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TCPServerParamDialog::OnButtonClickOK ), NULL, this );
	m_buttonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TCPServerParamDialog::OnButtonClickCancel ), NULL, this );

}

StateDialog::StateDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );

	m_panelStateDialog = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizerStateDialog = new wxBoxSizer( wxVERTICAL );

	bSizerValue = new wxBoxSizer( wxHORIZONTAL );


	bSizerStateDialog->Add( bSizerValue, 1, wxEXPAND, 5 );

	m_staticline5 = new wxStaticLine( m_panelStateDialog, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizerStateDialog->Add( m_staticline5, 0, wxEXPAND | wxALL, 5 );

	m_checkBoxQuality7 = new wxCheckBox( m_panelStateDialog, wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerStateDialog->Add( m_checkBoxQuality7, 0, wxALL, 5 );

	m_checkBoxQuality6 = new wxCheckBox( m_panelStateDialog, wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerStateDialog->Add( m_checkBoxQuality6, 0, wxALL, 5 );

	m_checkBoxQuality5 = new wxCheckBox( m_panelStateDialog, wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerStateDialog->Add( m_checkBoxQuality5, 0, wxALL, 5 );

	m_checkBoxQuality4 = new wxCheckBox( m_panelStateDialog, wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerStateDialog->Add( m_checkBoxQuality4, 0, wxALL, 5 );

	m_checkBoxQuality3 = new wxCheckBox( m_panelStateDialog, wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerStateDialog->Add( m_checkBoxQuality3, 0, wxALL, 5 );

	m_checkBoxQuality2 = new wxCheckBox( m_panelStateDialog, wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerStateDialog->Add( m_checkBoxQuality2, 0, wxALL, 5 );

	m_checkBoxQuality1 = new wxCheckBox( m_panelStateDialog, wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerStateDialog->Add( m_checkBoxQuality1, 0, wxALL, 5 );

	m_checkBoxQuality0 = new wxCheckBox( m_panelStateDialog, wxID_ANY, wxT("Check Me!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerStateDialog->Add( m_checkBoxQuality0, 0, wxALL, 5 );

	m_staticline51 = new wxStaticLine( m_panelStateDialog, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizerStateDialog->Add( m_staticline51, 0, wxEXPAND | wxALL, 5 );

	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( m_panelStateDialog, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2Apply = new wxButton( m_panelStateDialog, wxID_APPLY );
	m_sdbSizer2->AddButton( m_sdbSizer2Apply );
	m_sdbSizer2Cancel = new wxButton( m_panelStateDialog, wxID_CANCEL );
	m_sdbSizer2->AddButton( m_sdbSizer2Cancel );
	m_sdbSizer2->Realize();

	bSizerStateDialog->Add( m_sdbSizer2, 1, wxEXPAND, 5 );


	m_panelStateDialog->SetSizer( bSizerStateDialog );
	m_panelStateDialog->Layout();
	bSizerStateDialog->Fit( m_panelStateDialog );
	bSizer21->Add( m_panelStateDialog, 2, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer21 );
	this->Layout();
	bSizer21->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	m_sdbSizer2Apply->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StateDialog::StateDialogOnApplyButtonClick ), NULL, this );
	m_sdbSizer2Cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StateDialog::StateDialogOnCancelButtonClick ), NULL, this );
	m_sdbSizer2OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StateDialog::StateDialogOnOKButtonClick ), NULL, this );
}

StateDialog::~StateDialog()
{
	// Disconnect Events
	m_sdbSizer2Apply->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StateDialog::StateDialogOnApplyButtonClick ), NULL, this );
	m_sdbSizer2Cancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StateDialog::StateDialogOnCancelButtonClick ), NULL, this );
	m_sdbSizer2OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( StateDialog::StateDialogOnOKButtonClick ), NULL, this );

}
