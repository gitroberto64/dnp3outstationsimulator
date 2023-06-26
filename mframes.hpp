/*
Copyright [2022] [roberto64 (roberto64dnp3oss@outlook.com)]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#pragma once
#include <vector>
#include <wx/aui/auibook.h>
#include <wx/xml/xml.h>
#include "frames.h"
#include "dnp3.hpp"


class MSerialParamDialog;

class MFrame : public MainFrame
{
    friend class MPanelSlave;
    friend class MSerialParamDialog;
    friend class MTCPServerParamDialog;
public:
    MFrame();
    ~MFrame();
    void AddLog(const std::string& s);
    void LoadFromFile(const wxString& name);
    void SaveToFile(const wxString& name);
    void AddTCPServer(const std::string& name,const std::string& addr,std::uint16_t port);
    void AddSerial(const std::string& name,const opendnp3::SerialSettings& settings);
private:
    void SelectChannel();
    void ChannelFromXML(const wxXmlNode* ele);
    void DeleteChannel();
    void DeleteAll();
    void ShowSelectedChannel();
    void ReadProp();
    void SaveProp();

    void OnClose( wxCloseEvent& event );
    void OnMenuSelectionNew( wxCommandEvent& event );
    void OnMenuSelectionOpen( wxCommandEvent& event );
    void OnMenuSelectionSave( wxCommandEvent& event );
    void OnMenuSelectionSaveAs( wxCommandEvent& event );
    void OnMenuSelectionExit( wxCommandEvent& event ); 
    void OnMenuSelectionTCPServerAdd( wxCommandEvent& event );
    void OnMenuSelectionSerialAdd( wxCommandEvent& event );
    void OnMenuSelectionChannelEdit( wxCommandEvent& event );
    void OnMenuSelectionChannelDelete( wxCommandEvent& event );
    void OnMenuSelectionSlaveAdd( wxCommandEvent& event );
    void OnMenuSelectionSlaveEdit( wxCommandEvent& event );
    void OnMenuSelectionSlaveDelete( wxCommandEvent& event );
    void OnMenuSelectionLogLev( wxCommandEvent& event );
    void OnMenuSelectionAbout( wxCommandEvent& event );
    void OnAuiNotebookPageChangedSlaves( wxAuiNotebookEvent& event );
    void OnListBoxChannels( wxCommandEvent& event );
    void OnThreadListLog(wxCommandEvent& e);
    MManager mgr;
    std::uint16_t last_channel;
    std::uint16_t last_tcp_port;
    std::uint16_t last_serial_port;
    std::uint16_t last_number;
    std::uint16_t last_remote;
    std::vector<wxAuiNotebook*> notebooks_slaves;
    int frame_event_id;
    wxString current_path; 
};

class MPanelSlave : public PanelSlave
{
public:
    MPanelSlave(wxWindow* parent);
    ~MPanelSlave();
	void SetDefaultVariations();
    void LoadFromXML(const wxXmlNode* ele);
    void SaveToXML(wxXmlNode* ele);
    void SelectConfig();
    void AddLog(const std::string& str);
    void UpdateBinaryValueCell(int row, bool value);
    const wxString GetSlaveName() const { return m_textCtrlSlaveName->GetValue(); }
    static const int col_index;
    static const int col_descrypt;
    static const int col_value;
    static const int col_flags;
    static const int col_random;
    static const int col_increment;
private:    
    struct Cell
    {
        Cell(wxGrid* _grid, int _row, int _col, const wxString& _value) : grid(_grid), row(_row), col(_col), value(_value) {}
        wxGrid* grid;
        int row;
        int col;
        wxString value;
    };
    opendnp3::OutstationStackConfig stackConfig;
    MSlave* m_slave;
    std::string _name;
    int panel_event_id;
    void ReadSlaveConfig();
    void DeleteObjects();
    void ReadStateFromGui();
    void SlaveStart();
    void SlaveStop();

    void AppendBinaryInput(int l);
    void LoadBinaryInput(const wxXmlNode* ele);
	void AppendDBinaryInput(int l);
	void LoadDBinaryInput(const wxXmlNode* ele);
	void AppendAnalogInput(int l);
	void LoadAnalogInput(const wxXmlNode* ele);
	void AppendCounter(int l);
	void LoadCounter(const wxXmlNode* ele);
	void AppendFCounter(int l);
	void LoadFCounter(const wxXmlNode* ele);
	void AppendBinaryOutput(int l);
	void LoadBinaryOuput(const wxXmlNode* ele);
	void AppendAnalogOutput(int l);
	void LoadAnalogOutput(const wxXmlNode* ele);
    void OnButtonSyncTimeClick( wxCommandEvent& event ) override final;
	void OnSpinCtrlBinaryInput(wxSpinEvent& event) override final;
	void OnSpinCtrlDBinaryInput(wxSpinEvent& event) override final;
	void OnSpinCtrlAnalogInput(wxSpinEvent& event) override final;
	void OnSpinCtrlCounter(wxSpinEvent& event) override final;
	void OnSpinCtrlFCounter(wxSpinEvent& event) override final;
	void OnSpinCtrlBinaryOutput(wxSpinEvent& event) override final;
	void OnSpinCtrlAnalogOutput(wxSpinEvent& event) override final;
    void OnCheckBoxLeftDown( wxMouseEvent& event ) override final;
    void OnGridCellChangeBinaryInput( wxGridEvent& event ) override final;
    void OnGridCellChangeDBinaryInput( wxGridEvent& event ) override final;
    void OnGridCellChangeAnalogInput( wxGridEvent& event ) override final;
    void OnGridCellChangeCounter( wxGridEvent& event ) override final;
    void OnGridCellChangeFrozenCounter( wxGridEvent& event ) override final;
    void OnGridCellChangeBinaryOutputStatus( wxGridEvent& event ) override final;
    void OnGridCellChangeAnalogOutputStatus( wxGridEvent& event ) override final;
    void OnButtonClickSlaveStart( wxCommandEvent& event ) override final;
    void OnButtonClickSlaveRestart( wxCommandEvent& event ) override final;
    void OnButtonClickSlaveStop( wxCommandEvent& event ) override final;
    void OnPanelEvent(wxCommandEvent& e);
};

class MSerialParamDialog : public SerialParamDialog
{
public:
    MSerialParamDialog(wxWindow* parent);
    void Read();
private:
    void OnButtonClickOK( wxCommandEvent& event );
    void OnButtonClickCancel( wxCommandEvent& event );
};

class MTCPServerParamDialog : public TCPServerParamDialog
{
public:
    MTCPServerParamDialog(wxWindow* parent);
    void Read();
private:
    void OnButtonClickOK( wxCommandEvent& event );
    void OnButtonClickCancel( wxCommandEvent& event );
};

struct ClientChannel : public wxClientData
{
    ClientChannel(std::shared_ptr<opendnp3::IChannel> ch,const std::string& n) : channel(ch),name(n) {}
    virtual void SaveToXML(wxXmlNode* ele) = 0;
    std::shared_ptr<opendnp3::IChannel> channel;
    std::string name;
};

struct TCPServerClientChannel : public ClientChannel
{
    TCPServerClientChannel(std::shared_ptr<opendnp3::IChannel> ch, const std::string& n, const std::string& addr, std::uint16_t p) : ClientChannel(ch, n), address(addr), port(p) {}
    void SaveToXML(wxXmlNode* ele);
    std::string address;
    std::uint16_t port;
};

struct SerialClientChannel : public ClientChannel
{
    SerialClientChannel(std::shared_ptr<opendnp3::IChannel> ch, const std::string& n,const opendnp3::SerialSettings& ss) : ClientChannel(ch,n),serial_settings(ss) {}
    void SaveToXML(wxXmlNode* ele);
    opendnp3::SerialSettings serial_settings;
};

class MStateDialog : public StateDialog
{
public:
    typedef std::function<void(const wxString& val, const wxString& qual, const wxString& random)> OnChange;
public:
    MStateDialog(wxWindow *parent, OnChange fun);
private:
    void StateDialogOnApplyButtonClick(wxCommandEvent &event) override;
    void StateDialogOnCancelButtonClick(wxCommandEvent &event) override;
    void StateDialogOnOKButtonClick(wxCommandEvent &event) override;
    virtual void read(const wxString& old_val, const wxString& old_qual, const wxString &old_random) = 0;
    virtual void write() = 0;
protected:
    OnChange on_change;
};

class MBinaryDialog : public MStateDialog
{
public:
    MBinaryDialog(wxWindow* parent, const wxString& old_val, const wxString& old_qual, const wxString& old_random, OnChange fun);
private:
    wxCheckBox *binary_value;
    wxCheckBox *random_value;
    void read(const wxString& old_val, const wxString& old_qual, const wxString &old_random) override;
    void write() override;
};

class MDBinaryDialog : public MStateDialog
{
public:
    MDBinaryDialog(wxWindow* parent, const wxString& old_val, const wxString& old_qual, const wxString& old_random, OnChange fun);
private:
    wxComboBox *combo;
    wxCheckBox *random_value;
    void read(const wxString& old_val, const wxString& old_qual, const wxString &old_random) override;
    void write() override;
};

class MAnalogDialog : public MStateDialog
{
public:
    MAnalogDialog(wxWindow* parent, const wxString& old_val, const wxString& old_qual,const wxString& old_random, OnChange fun);
private:
    wxTextCtrl *text;
    wxTextCtrl *text_random;
    void read(const wxString& old_val, const wxString& old_qual, const wxString &old_random) override;
    void write() override;
};

class MCounterDialog : public MStateDialog
{
public:
    MCounterDialog(wxWindow* parent, const wxString& old_val, const wxString& old_qual, const wxString& old_random, OnChange fun);
private:
    wxTextCtrl *text;
    wxCheckBox *increment_value;
    void read(const wxString& old_val, const wxString& old_qual, const wxString &old_random) override;
    void write() override;
};
