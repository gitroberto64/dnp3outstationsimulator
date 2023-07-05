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

#include "stdafx.h"
#include "mframes.hpp"
#include <bitset>
#include <thread>
#include <sstream>
#include <regex>
#include <wx/app.h>
#include <wx/aboutdlg.h>
#include <wx/msgdlg.h>
#include <wx/textdlg.h>
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/config.h>
#include <wx/stdpaths.h>
#include "variations_spec.hpp"

template <typename T>
std::uint8_t quality_to_uint8(const wxString &s)
{
    std::uint8_t bq(0);
    std::istringstream is(s.ToStdString());
    std::string one;
    while (is >> one)
    {
        bq |= T::to_type(T::from_string(one));
    }
    return bq;
}

template <typename T>
typename T::enum_type_t quality_to_type(const wxString &s)
{
    return typename T::enum_type_t(quality_to_uint8<T>(s));
}


MFrame::MFrame() : MainFrame(NULL, wxID_ANY), mgr(this)
{
    last_channel = 0;
    last_tcp_port = 20000;
    last_serial_port = 0;
    last_number = 0;
    last_remote = 2;
    frame_event_id = wxNewId();
    current_dir = wxStandardPaths::Get().GetDocumentsDir();
    SetStatusBarPane(-1);    
    ReadProp();
    Center();    
    auto fp = wxFileName(current_dir, current_filename).GetFullPath();
    if (wxFileName::FileExists(fp))
        LoadFromFile(fp);
    Connect(frame_event_id, wxCommandEventHandler(MFrame::OnThreadListLog));
}

MFrame::~MFrame()
{
    frame_event_id = 0;
    for (std::vector<wxAuiNotebook *>::iterator i = notebooks_slaves.begin(); i != notebooks_slaves.end(); i++)
        (*i)->Destroy();
    mgr.Shutdown();
    SaveProp();
}

void MFrame::AddLog(const std::string &s)
{
    if (frame_event_id > 0)
    {
        wxCommandEvent e(frame_event_id);
        e.SetClientData(new std::string(s));
        wxPostEvent(GetEventHandler(), e);
    }
}

void MFrame::LoadFromFile(const wxString &name)
{
    wxXmlDocument doc;
    if (!doc.Load(name))
    {
        wxMessageBox(wxT("Error in XML: ") + name);
    }
    else
    {
        wxXmlNode *root = doc.GetRoot();
        if (root && root->GetName() == "DNP3OutstationSimulator")
        {
            const wxXmlNode *ch = root->GetChildren();
            while (ch)
            {
                ChannelFromXML(ch);
                const wxXmlNode *slave = ch->GetChildren();
                while (slave)
                {
                    MPanelSlave *ps = new MPanelSlave(notebooks_slaves.back());
                    ps->LoadFromXML(slave);
                    notebooks_slaves.back()->AddPage(ps, ps->GetSlaveName());
                    last_remote++;
                    slave = slave->GetNext();
                }
                ch = ch->GetNext();
            }
            for (std::size_t i = 0; i < notebooks_slaves.back()->GetPageCount(); i++)
            {
                notebooks_slaves.back()->GetPage(i)->Fit();
            }
        }
        else
        {
            wxString("It is not DNP3OutstationSimulator document !!!");
        }
        SetStatusText(name);
    }
}

void MFrame::SaveToFile(const wxString &name)
{
    wxXmlDocument doc;
    wxXmlNode *root = new wxXmlNode(nullptr, wxXmlNodeType::wxXML_ELEMENT_NODE, "DNP3OutstationSimulator");
    doc.SetRoot(root);
    for (size_t i = 0; i < m_listBoxChannels->GetCount(); i++)
    {
        wxXmlNode *ch = new wxXmlNode(root, wxXmlNodeType::wxXML_ELEMENT_NODE, "Channel");
        ClientChannel *cch = static_cast<ClientChannel *>(m_listBoxChannels->GetClientObject(i));
        for (size_t s = 0; s < notebooks_slaves[i]->GetPageCount(); s++)
        {
            wxXmlNode *slave = new wxXmlNode(ch, wxXmlNodeType::wxXML_ELEMENT_NODE, "Slave");
            static_cast<MPanelSlave *>(notebooks_slaves[i]->GetPage(s))->SaveToXML(slave);
        }

        cch->SaveToXML(ch);
    }
    doc.Save(name);
    SetStatusText(name);
}

void MFrame::AddTCPServer(const std::string &name, const std::string &addr, std::uint16_t port)
{
    std::shared_ptr<opendnp3::IChannel> ch = mgr.AddTCPServer(name, addr, port);
    m_listBoxChannels->Freeze();
    m_listBoxChannels->Append(wxString((name + ':' + addr + ':' + std::to_string(port)).c_str(), wxConvLocal), new TCPServerClientChannel(ch, name, addr, port));
    m_listBoxChannels->Thaw();
    notebooks_slaves.push_back(new wxAuiNotebook(m_panelMain));
    notebooks_slaves.back()->Hide();
    sbSizerNotebookSlaves->Add(notebooks_slaves.back(), 1, wxALL | wxEXPAND, 0);
    last_channel++;
    last_tcp_port = port + 1;
}

void MFrame::AddSerial(const std::string &name, const opendnp3::SerialSettings &settings)
{
    std::shared_ptr<opendnp3::IChannel> ch = mgr.AddSerial(name, settings);
    std::string par(name + ':' + settings.deviceName);
    par += ":" + std::to_string(settings.baud);
    par += ":" + std::to_string(settings.dataBits);
    if (settings.parity == opendnp3::Parity::None)
        par += ":none";
    else if (settings.parity == opendnp3::Parity::Even)
        par += ":even";
    else if (settings.parity == opendnp3::Parity::Odd)
        par += ":odd";
    if (settings.stopBits == opendnp3::StopBits::None)
        par += ":none";
    else if (settings.stopBits == opendnp3::StopBits::One)
        par += ":one";
    else if (settings.stopBits == opendnp3::StopBits::OnePointFive)
        par += ":onepointfive";
    else if (settings.stopBits == opendnp3::StopBits::Two)
        par += ":two";
    if (settings.flowType == opendnp3::FlowControl::None)
        par += ":none";
    else if (settings.flowType == opendnp3::FlowControl::Hardware)
        par += ":hardware";
    else if (settings.flowType == opendnp3::FlowControl::XONXOFF)
        par += ":xonxoff";
    m_listBoxChannels->Freeze();
    m_listBoxChannels->Append(wxString(par), new SerialClientChannel(ch, name, settings));
    m_listBoxChannels->Thaw();
    notebooks_slaves.push_back(new wxAuiNotebook(m_panelMain));
    notebooks_slaves.back()->Hide();
    sbSizerNotebookSlaves->Add(notebooks_slaves.back(), 1, wxALL | wxEXPAND, 0);
    last_channel++;
    last_serial_port++;
}

void MFrame::SelectChannel()
{
    m_listBoxChannels->Select(m_listBoxChannels->GetCount() - 1);
    ShowSelectedChannel();
}

void MFrame::ChannelFromXML(const wxXmlNode *ele)
{
    const wxString type = ele->GetAttribute("Type");
    if (type == "TCPServer")
    {
        const wxString name = ele->GetAttribute("Name");
        const wxString addr = ele->GetAttribute("Address");
        const wxString port = ele->GetAttribute("Port");
        AddTCPServer(name.ToStdString(), addr.ToStdString(), std::stoi(port.ToStdString()));
    }
    else if (type == "Serial")
    {
        const wxString name = ele->GetAttribute("Name");
        const wxString port = ele->GetAttribute("Port");
        const wxString baud = ele->GetAttribute("Baud");
        const wxString bits = ele->GetAttribute("DataBits");
        const wxString par = ele->GetAttribute("Parity");
        const wxString stopb = ele->GetAttribute("StopBits");
        const wxString flow = ele->GetAttribute("Flow");
        opendnp3::SerialSettings ss;
        ss.deviceName = port.ToStdString();
        ss.baud = std::stoi(baud.ToStdString());
        ss.dataBits = std::stoi(bits.ToStdString());
        if (par == "none")
            ss.parity = opendnp3::Parity::None;
        else if (par == "even")
            ss.parity = opendnp3::Parity::Even;
        else if (par == "odd")
            ss.parity = opendnp3::Parity::Odd;

        if (stopb == "none")
            ss.stopBits = opendnp3::StopBits::None;
        else if (stopb == "one")
            ss.stopBits = opendnp3::StopBits::One;
        else if (stopb == "two")
            ss.stopBits = opendnp3::StopBits::Two;
        else if (stopb == "onepointfive")
            ss.stopBits = opendnp3::StopBits::OnePointFive;

        if (flow == "none")
            ss.flowType = opendnp3::FlowControl::None;
        else if (flow == "hardware")
            ss.flowType = opendnp3::FlowControl::Hardware;
        else if (flow == "xonxoff")
            ss.flowType = opendnp3::FlowControl::XONXOFF;
        AddSerial(name.ToStdString(), ss);
    }
    SelectChannel();
}

void MFrame::DeleteChannel()
{
    int sel = m_listBoxChannels->GetSelection();
    if (sel != -1)
    {
        notebooks_slaves[sel]->Destroy();
        notebooks_slaves.erase(notebooks_slaves.begin() + sel);
        static_cast<ClientChannel *>(m_listBoxChannels->GetClientObject(sel))->channel->Shutdown();
        m_listBoxChannels->Delete(sel);
    }
    else
    {
        throw std::runtime_error("No select channel");
    }
}

void MFrame::DeleteAll()
{
    for (std::vector<wxAuiNotebook *>::iterator i = notebooks_slaves.begin(); i != notebooks_slaves.end(); i++)
        (*i)->Destroy();
    for (size_t i = 0; i < m_listBoxChannels->GetCount(); i++)
    {
        static_cast<ClientChannel *>(m_listBoxChannels->GetClientObject(i))->channel->Shutdown();
    }
    notebooks_slaves.clear();
    m_listBoxChannels->Clear();
}

void MFrame::ShowSelectedChannel()
{
    int sel = m_listBoxChannels->GetSelection();
    for (size_t i = 0; i != notebooks_slaves.size(); i++)
    {
        if (i == (size_t)sel)
            notebooks_slaves[i]->Show();
        else
            notebooks_slaves[i]->Hide();
    }
    sbSizerNotebookSlaves->Layout();
}

void MFrame::ReadProp()
{
    wxConfig conf(wxTheApp->GetAppName());
    SetSize(conf.Read("width", GetSize().GetWidth()), conf.Read("height", GetSize().GetHeight()));
    current_dir = conf.Read("current_dir", current_dir);
    current_filename = conf.Read("current_filename", current_filename);
}

void MFrame::SaveProp()
{
    wxConfig conf(wxTheApp->GetAppName());
    conf.Write("width", GetSize().GetWidth());
    conf.Write("height", GetSize().GetHeight());
    conf.Write("current_dir", current_dir);
    conf.Write("current_filename", current_filename);
}

void MFrame::OnClose(wxCloseEvent &event)
{
    wxTheApp->ExitMainLoop();
}

void MFrame::OnMenuSelectionNew(wxCommandEvent &event)
{
    DeleteAll();
}

void MFrame::OnMenuSelectionOpen(wxCommandEvent &event)
{
    try
    {
        wxFileDialog fd(this, "Choose file to open", current_dir, current_filename, "XDS file (*.xds)|*.xds", wxFD_OPEN);
        if (fd.ShowModal() == wxID_OK)
        {
            current_dir = fd.GetDirectory();
            current_filename = fd.GetFilename();
            DeleteAll();
            LoadFromFile(fd.GetPath());
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MFrame::OnMenuSelectionSave(wxCommandEvent &event)
{
    try
    {
        auto fp = wxFileName(current_dir, current_filename).GetFullPath();
        if (wxFileName::FileExists(fp))
            SaveToFile(fp);
        else
        {
            wxFileDialog fd(this, "Choose file to save", current_dir, current_filename, "XDS file (*.xds)|*.xds", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
            if (fd.ShowModal() == wxID_OK)
            {
                wxString fn = fd.GetFilename();
                if (!fn.empty())
                {
                    if (fn.find(".xds") == wxString::npos)
                    {
                        fn += ".xds";
                    }
                    fd.SetFilename(fn);
                    current_dir = fd.GetDirectory();
                    current_filename = fn;
                    SaveToFile(fd.GetPath());
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MFrame::OnMenuSelectionSaveAs(wxCommandEvent &event)
{
    try
    {
        wxFileDialog fd(this, "Choose file to save", current_dir, current_filename, "XDS file (*.xds)|*.xds", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if (fd.ShowModal() == wxID_OK)
        {
            wxString fn = fd.GetFilename();
            if(!fn.empty())
            {
                if(fn.find(".xds") == wxString::npos)
                {
                    fn += ".xds";
                }
                fd.SetFilename(fn);
                current_dir = fd.GetDirectory();
                current_filename = fn;
                SaveToFile(fd.GetPath());
            }
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MFrame::OnMenuSelectionExit(wxCommandEvent &event)
{
    Close();
}

void MFrame::OnMenuSelectionTCPServerAdd(wxCommandEvent &event)
{
    try
    {
        MTCPServerParamDialog pd(this);
        if (pd.ShowModal() == wxID_OK)
        {
            pd.Read();
            SelectChannel();
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MFrame::OnMenuSelectionSerialAdd(wxCommandEvent &event)
{
    try
    {
        MSerialParamDialog ted(this);
        if (ted.ShowModal() == wxID_OK)
        {
            ted.Read();
            SelectChannel();
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MFrame::OnMenuSelectionChannelEdit(wxCommandEvent &event)
{
    try
    {
        int sel = m_listBoxChannels->GetSelection();
        if (sel != -1)
        {
            wxMessageDialog(this, "Not yet implemented.").ShowModal();
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MFrame::OnMenuSelectionChannelDelete(wxCommandEvent &event)
{
    try
    {
        DeleteChannel();
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MFrame::OnMenuSelectionSlaveAdd(wxCommandEvent &event)
{
    try
    {
        std::string name = std::string("Slave") + std::to_string(last_number++);
        int sel = m_listBoxChannels->GetSelection();
        if (sel != -1)
        {
            MPanelSlave *ps = new MPanelSlave(notebooks_slaves[sel]);
            ps->m_textCtrlSlaveName->SetValue(wxString(name));
            ps->m_textCtrlSlaveAddr->SetValue(wxString::Format("%u", 1));
            ps->m_textCtrlMasterAddr->SetValue(wxString::Format("%u", last_remote));
            notebooks_slaves[sel]->AddPage(ps, wxString(name), true);
            last_remote++;
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MFrame::OnMenuSelectionSlaveEdit(wxCommandEvent &event)
{
    try
    {
        int sel = m_listBoxChannels->GetSelection();
        if (sel != -1)
        {
            int i = notebooks_slaves[sel]->GetSelection();
            if (i != -1)
                static_cast<MPanelSlave *>(notebooks_slaves[sel]->GetPage(i))->SelectConfig();
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MFrame::OnMenuSelectionSlaveDelete(wxCommandEvent &event)
{
    try
    {
        int sel = m_listBoxChannels->GetSelection();
        if (sel != -1)
        {
            if (notebooks_slaves[sel]->GetSelection() != -1)
            {
                notebooks_slaves[sel]->DeletePage(notebooks_slaves[sel]->GetSelection());
            }
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MFrame::OnMenuSelectionLogLev(wxCommandEvent &event)
{
    wxMessageDialog(this, "Not yet implemented.").ShowModal();
}

void MFrame::OnMenuSelectionAbout(wxCommandEvent &event)
{
    wxAboutDialogInfo info;
    info.SetName(wxTheApp->GetAppName());
    info.AddDeveloper("roberto64");
    info.SetWebSite("https://bitbucket.org/roberto64/dnp3outstationsimulator");
    info.SetVersion(VERSION);
    info.SetLicense("https://apache.org/licenses/LICENSE-2.0");
    wxAboutBox(info);
}

void MFrame::OnAuiNotebookPageChangedSlaves(wxAuiNotebookEvent &event)
{
    try
    {
        // std::cout << "changed" << std::endl;
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MFrame::OnListBoxChannels(wxCommandEvent &event)
{
    ShowSelectedChannel();
}

void MFrame::OnThreadListLog(wxCommandEvent &e)
{
    if (e.GetExtraLong() == 0)
    {
        std::string *str = static_cast<std::string *>(e.GetClientData());
        m_listBoxLog->Freeze();
        if (m_listBoxLog->GetCount() > 64)
            m_listBoxLog->Delete(0);
        m_listBoxLog->Append(wxString(*str));
        m_listBoxLog->Select(m_listBoxLog->GetCount() - 1);
        m_listBoxLog->Thaw();
        delete str;
    }
}

MPanelSlave::MPanelSlave(wxWindow *parent) : PanelSlave(parent)
{
    wxGridCellBoolEditor::UseStringValues("ON", "OFF");
    m_slave = NULL;
    // m_gridBinaryInput->SetSelectionMode(wxGrid::wxGridSelectRows);
    SetDefaultVariations();
    panel_event_id = wxNewId();
    Connect(panel_event_id, wxCommandEventHandler(MPanelSlave::OnPanelEvent));
}

MPanelSlave::~MPanelSlave()
{
    SlaveStop();
}

const int MPanelSlave::col_index = 0;
const int MPanelSlave::col_descrypt = 1;
const int MPanelSlave::col_value = 2;
const int MPanelSlave::col_flags = 3;
const int MPanelSlave::col_random = 4;
const int MPanelSlave::col_increment = MPanelSlave::col_random;

void MPanelSlave::SetDefaultVariations()
{
    m_choiceStaticBinary->Append(opendnp3::StaticBinaryVariationSpec::to_string((opendnp3::StaticBinaryVariation::Group1Var1)));
    m_choiceStaticBinary->Append(opendnp3::StaticBinaryVariationSpec::to_string((opendnp3::StaticBinaryVariation::Group1Var2)));
    m_choiceStaticBinary->Select(1);

    m_choiceEventBinary->Append(opendnp3::EventBinaryVariationSpec::to_string((opendnp3::EventBinaryVariation::Group2Var1)));
    m_choiceEventBinary->Append(opendnp3::EventBinaryVariationSpec::to_string((opendnp3::EventBinaryVariation::Group2Var2)));
    m_choiceEventBinary->Append(opendnp3::EventBinaryVariationSpec::to_string((opendnp3::EventBinaryVariation::Group2Var3)));
    m_choiceEventBinary->Select(0);

    m_choiceStaticDBit->Append(opendnp3::StaticDoubleBinaryVariationSpec::to_string((opendnp3::StaticDoubleBinaryVariation::Group3Var2)));
    m_choiceStaticDBit->Select(0);

    m_choiceEventDBit->Append(opendnp3::EventDoubleBinaryVariationSpec::to_string((opendnp3::EventDoubleBinaryVariation::Group4Var1)));
    m_choiceEventDBit->Append(opendnp3::EventDoubleBinaryVariationSpec::to_string((opendnp3::EventDoubleBinaryVariation::Group4Var2)));
    m_choiceEventDBit->Append(opendnp3::EventDoubleBinaryVariationSpec::to_string((opendnp3::EventDoubleBinaryVariation::Group4Var3)));
    m_choiceEventDBit->Select(0);

    m_choiceStaticAnalogInput->Append(opendnp3::StaticAnalogVariationSpec::to_string((opendnp3::StaticAnalogVariation::Group30Var1)));
    m_choiceStaticAnalogInput->Append(opendnp3::StaticAnalogVariationSpec::to_string((opendnp3::StaticAnalogVariation::Group30Var2)));
    m_choiceStaticAnalogInput->Append(opendnp3::StaticAnalogVariationSpec::to_string((opendnp3::StaticAnalogVariation::Group30Var3)));
    m_choiceStaticAnalogInput->Append(opendnp3::StaticAnalogVariationSpec::to_string((opendnp3::StaticAnalogVariation::Group30Var4)));
    m_choiceStaticAnalogInput->Append(opendnp3::StaticAnalogVariationSpec::to_string((opendnp3::StaticAnalogVariation::Group30Var5)));
    m_choiceStaticAnalogInput->Append(opendnp3::StaticAnalogVariationSpec::to_string((opendnp3::StaticAnalogVariation::Group30Var6)));
    m_choiceStaticAnalogInput->Select(0);

    m_choiceEventAnalogInput->Append(opendnp3::EventAnalogVariationSpec::to_string((opendnp3::EventAnalogVariation::Group32Var1)));
    m_choiceEventAnalogInput->Append(opendnp3::EventAnalogVariationSpec::to_string((opendnp3::EventAnalogVariation::Group32Var2)));
    m_choiceEventAnalogInput->Append(opendnp3::EventAnalogVariationSpec::to_string((opendnp3::EventAnalogVariation::Group32Var3)));
    m_choiceEventAnalogInput->Append(opendnp3::EventAnalogVariationSpec::to_string((opendnp3::EventAnalogVariation::Group32Var4)));
    m_choiceEventAnalogInput->Append(opendnp3::EventAnalogVariationSpec::to_string((opendnp3::EventAnalogVariation::Group32Var5)));
    m_choiceEventAnalogInput->Append(opendnp3::EventAnalogVariationSpec::to_string((opendnp3::EventAnalogVariation::Group32Var6)));
    m_choiceEventAnalogInput->Append(opendnp3::EventAnalogVariationSpec::to_string((opendnp3::EventAnalogVariation::Group32Var7)));
    m_choiceEventAnalogInput->Append(opendnp3::EventAnalogVariationSpec::to_string((opendnp3::EventAnalogVariation::Group32Var8)));
    m_choiceEventAnalogInput->Select(0);

    m_choiceStaticCounter->Append(opendnp3::StaticCounterVariationSpec::to_string((opendnp3::StaticCounterVariation::Group20Var1)));
    m_choiceStaticCounter->Append(opendnp3::StaticCounterVariationSpec::to_string((opendnp3::StaticCounterVariation::Group20Var2)));
    m_choiceStaticCounter->Append(opendnp3::StaticCounterVariationSpec::to_string((opendnp3::StaticCounterVariation::Group20Var5)));
    m_choiceStaticCounter->Append(opendnp3::StaticCounterVariationSpec::to_string((opendnp3::StaticCounterVariation::Group20Var6)));
    m_choiceStaticCounter->Select(0);

    m_choiceEventCounter->Append(opendnp3::EventCounterVariationSpec::to_string((opendnp3::EventCounterVariation::Group22Var1)));
    m_choiceEventCounter->Append(opendnp3::EventCounterVariationSpec::to_string((opendnp3::EventCounterVariation::Group22Var2)));
    m_choiceEventCounter->Append(opendnp3::EventCounterVariationSpec::to_string((opendnp3::EventCounterVariation::Group22Var5)));
    m_choiceEventCounter->Append(opendnp3::EventCounterVariationSpec::to_string((opendnp3::EventCounterVariation::Group22Var6)));
    m_choiceEventCounter->Select(0);

    m_choiceStaticFCounter->Append(opendnp3::StaticFrozenCounterVariationSpec::to_string((opendnp3::StaticFrozenCounterVariation::Group21Var1)));
    m_choiceStaticFCounter->Append(opendnp3::StaticFrozenCounterVariationSpec::to_string((opendnp3::StaticFrozenCounterVariation::Group21Var2)));
    m_choiceStaticFCounter->Append(opendnp3::StaticFrozenCounterVariationSpec::to_string((opendnp3::StaticFrozenCounterVariation::Group21Var5)));
    m_choiceStaticFCounter->Append(opendnp3::StaticFrozenCounterVariationSpec::to_string((opendnp3::StaticFrozenCounterVariation::Group21Var6)));
    m_choiceStaticFCounter->Append(opendnp3::StaticFrozenCounterVariationSpec::to_string((opendnp3::StaticFrozenCounterVariation::Group21Var9)));
    m_choiceStaticFCounter->Append(opendnp3::StaticFrozenCounterVariationSpec::to_string((opendnp3::StaticFrozenCounterVariation::Group21Var10)));
    m_choiceStaticFCounter->Select(0);

    m_choiceEventFCounter->Append(opendnp3::EventFrozenCounterVariationSpec::to_string((opendnp3::EventFrozenCounterVariation::Group23Var1)));
    m_choiceEventFCounter->Append(opendnp3::EventFrozenCounterVariationSpec::to_string((opendnp3::EventFrozenCounterVariation::Group23Var2)));
    m_choiceEventFCounter->Append(opendnp3::EventFrozenCounterVariationSpec::to_string((opendnp3::EventFrozenCounterVariation::Group23Var5)));
    m_choiceEventFCounter->Append(opendnp3::EventFrozenCounterVariationSpec::to_string((opendnp3::EventFrozenCounterVariation::Group23Var6)));
    m_choiceEventFCounter->Select(0);

    m_choiceStaticBinaryOutput->Append(opendnp3::StaticBinaryOutputStatusVariationSpec::to_string((opendnp3::StaticBinaryOutputStatusVariation::Group10Var2)));
    m_choiceStaticBinaryOutput->Select(0);

    m_choiceEventBinaryOutput->Append(opendnp3::EventBinaryOutputStatusVariationSpec::to_string((opendnp3::EventBinaryOutputStatusVariation::Group11Var1)));
    m_choiceEventBinaryOutput->Append(opendnp3::EventBinaryOutputStatusVariationSpec::to_string((opendnp3::EventBinaryOutputStatusVariation::Group11Var2)));
    m_choiceEventBinaryOutput->Select(0);

    m_choiceStaticAnalogOutput->Append(opendnp3::StaticAnalogOutputStatusVariationSpec::to_string((opendnp3::StaticAnalogOutputStatusVariation::Group40Var1)));
    m_choiceStaticAnalogOutput->Append(opendnp3::StaticAnalogOutputStatusVariationSpec::to_string((opendnp3::StaticAnalogOutputStatusVariation::Group40Var2)));
    m_choiceStaticAnalogOutput->Append(opendnp3::StaticAnalogOutputStatusVariationSpec::to_string((opendnp3::StaticAnalogOutputStatusVariation::Group40Var3)));
    m_choiceStaticAnalogOutput->Append(opendnp3::StaticAnalogOutputStatusVariationSpec::to_string((opendnp3::StaticAnalogOutputStatusVariation::Group40Var4)));
    m_choiceStaticAnalogOutput->Select(0);

    m_choiceEventAnalogOutput->Append(opendnp3::EventAnalogOutputStatusVariationSpec::to_string((opendnp3::EventAnalogOutputStatusVariation::Group42Var1)));
    m_choiceEventAnalogOutput->Append(opendnp3::EventAnalogOutputStatusVariationSpec::to_string((opendnp3::EventAnalogOutputStatusVariation::Group42Var2)));
    m_choiceEventAnalogOutput->Append(opendnp3::EventAnalogOutputStatusVariationSpec::to_string((opendnp3::EventAnalogOutputStatusVariation::Group42Var3)));
    m_choiceEventAnalogOutput->Append(opendnp3::EventAnalogOutputStatusVariationSpec::to_string((opendnp3::EventAnalogOutputStatusVariation::Group42Var4)));
    m_choiceEventAnalogOutput->Append(opendnp3::EventAnalogOutputStatusVariationSpec::to_string((opendnp3::EventAnalogOutputStatusVariation::Group42Var5)));
    m_choiceEventAnalogOutput->Append(opendnp3::EventAnalogOutputStatusVariationSpec::to_string((opendnp3::EventAnalogOutputStatusVariation::Group42Var6)));
    m_choiceEventAnalogOutput->Append(opendnp3::EventAnalogOutputStatusVariationSpec::to_string((opendnp3::EventAnalogOutputStatusVariation::Group42Var7)));
    m_choiceEventAnalogOutput->Append(opendnp3::EventAnalogOutputStatusVariationSpec::to_string((opendnp3::EventAnalogOutputStatusVariation::Group42Var8)));
    m_choiceEventAnalogOutput->Select(0);
}

void MPanelSlave::LoadFromXML(const wxXmlNode *ele)
{
    m_textCtrlSlaveName->SetValue(ele->GetAttribute("Name"));
    m_textCtrlSlaveAddr->SetValue(ele->GetAttribute("SlaveAddress"));
    m_textCtrlMasterAddr->SetValue(ele->GetAttribute("MasterAddress"));
    m_checkBoxUnsol->SetValue(std::stoi(ele->GetAttribute("Unsolicied").ToStdString()) > 0);

    const wxXmlNode *child = ele->GetChildren();
    while (child)
    {
        wxString name = child->GetName();
        if (child->GetName() == "Binarys")
            LoadBinaryInput(child);
        else if (child->GetName() == "DoubleBinarys")
            LoadDBinaryInput(child);
        else if (child->GetName() == "Analogs")
            LoadAnalogInput(child);
        else if (child->GetName() == "Counters")
            LoadCounter(child);
        else if (child->GetName() == "FrozenCounters")
            LoadFCounter(child);
        else if (child->GetName() == "BinaryOutputsStatus")
            LoadBinaryOuput(child);
        else if (child->GetName() == "AnalogOutputsStatus")
            LoadAnalogOutput(child);
        child = child->GetNext();
    }
    m_spinCtrlFCounter->SetRange(0, m_spinCtrlFCounter->GetValue());
}

void MPanelSlave::SaveToXML(wxXmlNode *ele)
{
    ele->AddAttribute("Name", m_textCtrlSlaveName->GetValue().mbc_str());
    ele->AddAttribute("SlaveAddress", m_textCtrlSlaveAddr->GetValue().mbc_str());
    ele->AddAttribute("MasterAddress", m_textCtrlMasterAddr->GetValue().mbc_str());
    ele->AddAttribute("Unsolicied", m_checkBoxUnsol->GetValue() ? "1" : "0");

    {
        wxXmlNode *binarys = new wxXmlNode(ele, wxXmlNodeType::wxXML_ELEMENT_NODE, "Binarys");
        binarys->AddAttribute("DefStatic", m_choiceStaticBinary->GetStringSelection());
        binarys->AddAttribute("DefEvent", m_choiceEventBinary->GetStringSelection());
        int n = m_spinCtrlBinaryInput->GetValue();
        wxString v;
        v << n;
        binarys->AddAttribute("Count", v);
        for (int i = 0; i < n; i++)
        {
            wxXmlNode *binary = new wxXmlNode(binarys, wxXmlNodeType::wxXML_ELEMENT_NODE, "Binary");
            binary->AddAttribute("Index", m_gridBinaryInput->GetCellValue(i, col_index));
            binary->AddAttribute("Description", m_gridBinaryInput->GetCellValue(i, col_descrypt));
            binary->AddAttribute("Flags", m_gridBinaryInput->GetCellValue(i, col_flags));
            binary->AddAttribute("Value", m_gridBinaryInput->GetCellValue(i, col_value));
            binary->AddAttribute("Random", m_gridBinaryInput->GetCellValue(i, col_random));
        }
    }
    {
        wxXmlNode *dbinarys = new wxXmlNode(ele, wxXmlNodeType::wxXML_ELEMENT_NODE, "DoubleBinarys");
        dbinarys->AddAttribute("DefStatic", m_choiceStaticDBit->GetStringSelection());
        dbinarys->AddAttribute("DefEvent", m_choiceEventDBit->GetStringSelection());
        int n = m_spinCtrlDBit->GetValue();
        wxString v;
        v << n;
        dbinarys->AddAttribute("Count", v);
        for (int i = 0; i < n; i++)
        {
            wxXmlNode *dbinary = new wxXmlNode(dbinarys, wxXmlNodeType::wxXML_ELEMENT_NODE, "DoubleBinary");
            dbinary->AddAttribute("Index", m_gridDBinaryInput->GetCellValue(i, col_index));
            dbinary->AddAttribute("Description", m_gridDBinaryInput->GetCellValue(i, col_descrypt));
            dbinary->AddAttribute("Flags", m_gridDBinaryInput->GetCellValue(i, col_flags));
            dbinary->AddAttribute("Value", m_gridDBinaryInput->GetCellValue(i, col_value));
            dbinary->AddAttribute("Random", m_gridDBinaryInput->GetCellValue(i, col_random));
        }
    }
    {
        wxXmlNode *analogs = new wxXmlNode(ele, wxXmlNodeType::wxXML_ELEMENT_NODE, "Analogs");
        analogs->AddAttribute("DefStatic", m_choiceStaticAnalogInput->GetStringSelection());
        analogs->AddAttribute("DefEvent", m_choiceEventAnalogInput->GetStringSelection());
        int n = m_spinCtrlAnalogInput->GetValue();
        wxString v;
        v << n;
        analogs->AddAttribute("Count", v);
        for (int i = 0; i < n; i++)
        {
            wxXmlNode *analog = new wxXmlNode(analogs, wxXmlNodeType::wxXML_ELEMENT_NODE, "Analog");
            analog->AddAttribute("Index", m_gridAnalogInput->GetCellValue(i, col_index));
            analog->AddAttribute("Description", m_gridAnalogInput->GetCellValue(i, col_descrypt));
            analog->AddAttribute("Flags", m_gridAnalogInput->GetCellValue(i, col_flags));
            analog->AddAttribute("Value", m_gridAnalogInput->GetCellValue(i, col_value));
            analog->AddAttribute("Random", m_gridAnalogInput->GetCellValue(i, col_random));
        }
    }
    {
        wxXmlNode *counters = new wxXmlNode(ele, wxXmlNodeType::wxXML_ELEMENT_NODE, "Counters");
        counters->AddAttribute("DefStatic", m_choiceStaticCounter->GetStringSelection());
        counters->AddAttribute("DefEvent", m_choiceEventCounter->GetStringSelection());
        int n = m_spinCtrlCounter->GetValue();
        wxString v;
        v << n;
        counters->AddAttribute("Count", v);
        for (int i = 0; i < n; i++)
        {
            wxXmlNode *counter = new wxXmlNode(counters, wxXmlNodeType::wxXML_ELEMENT_NODE, "Counter");
            counter->AddAttribute("Index", m_gridCounter->GetCellValue(i, col_index));
            counter->AddAttribute("Description", m_gridCounter->GetCellValue(i, col_descrypt));
            counter->AddAttribute("Flags", m_gridCounter->GetCellValue(i, col_flags));
            counter->AddAttribute("Value", m_gridCounter->GetCellValue(i, col_value));
            counter->AddAttribute("Increment", m_gridCounter->GetCellValue(i, col_increment));
        }
    }
    {
        wxXmlNode *fcounters = new wxXmlNode(ele, wxXmlNodeType::wxXML_ELEMENT_NODE, "FrozenCounters");
        fcounters->AddAttribute("DefStatic", m_choiceStaticFCounter->GetStringSelection());
        fcounters->AddAttribute("DefEvent", m_choiceEventFCounter->GetStringSelection());
        int n = m_spinCtrlFCounter->GetValue();
        wxString v;
        v << n;
        fcounters->AddAttribute("Count", v);
        for (int i = 0; i < n; i++)
        {
            wxXmlNode *fcounter = new wxXmlNode(fcounters, wxXmlNodeType::wxXML_ELEMENT_NODE, "FrozenCounter");
            fcounter->AddAttribute("Index", m_gridFCounter->GetCellValue(i, col_index));
            fcounter->AddAttribute("Description", m_gridFCounter->GetCellValue(i, col_descrypt));
            fcounter->AddAttribute("Flags", m_gridFCounter->GetCellValue(i, col_flags));
            fcounter->AddAttribute("Value", m_gridFCounter->GetCellValue(i, col_value));
        }
    }
    {
        wxXmlNode *boutputs = new wxXmlNode(ele, wxXmlNodeType::wxXML_ELEMENT_NODE, "BinaryOutputsStatus");
        boutputs->AddAttribute("DefStatic", m_choiceStaticBinaryOutput->GetStringSelection());
        boutputs->AddAttribute("DefEvent", m_choiceEventBinaryOutput->GetStringSelection());
        int n = m_spinCtrlBinaryOutput->GetValue();
        wxString v;
        v << n;
        boutputs->AddAttribute("Count", v);
        for (int i = 0; i < n; i++)
        {
            wxXmlNode *boutput = new wxXmlNode(boutputs, wxXmlNodeType::wxXML_ELEMENT_NODE, "BinaryOutputStatus");
            boutput->AddAttribute("Index", m_gridBinaryOut->GetCellValue(i, col_index));
            boutput->AddAttribute("Description", m_gridBinaryOut->GetCellValue(i, col_descrypt));
            boutput->AddAttribute("Flags", m_gridBinaryOut->GetCellValue(i, col_flags));
            boutput->AddAttribute("Value", m_gridBinaryOut->GetCellValue(i, col_value));
        }
    }
    {
        wxXmlNode *aoutputs = new wxXmlNode(ele, wxXmlNodeType::wxXML_ELEMENT_NODE, "AnalogOutputsStatus");
        aoutputs->AddAttribute("DefStatic", m_choiceStaticAnalogOutput->GetStringSelection());
        aoutputs->AddAttribute("DefEvent", m_choiceEventAnalogOutput->GetStringSelection());
        int n = m_spinCtrlAnalogOutput->GetValue();
        wxString v;
        v << n;
        aoutputs->AddAttribute("Count", v);
        for (int i = 0; i < n; i++)
        {
            wxXmlNode *aoutput = new wxXmlNode(aoutputs, wxXmlNodeType::wxXML_ELEMENT_NODE, "AnalogOutputStatus");
            aoutput->AddAttribute("Index", m_gridAnalogOut->GetCellValue(i, col_index));
            aoutput->AddAttribute("Description", m_gridAnalogOut->GetCellValue(i, col_descrypt));
            aoutput->AddAttribute("Flags", m_gridAnalogOut->GetCellValue(i, col_flags));
            aoutput->AddAttribute("Value", m_gridAnalogOut->GetCellValue(i, col_value));
        }
    }
}

void MPanelSlave::ReadSlaveConfig()
{
    stackConfig.link.LocalAddr = std::stoi(m_textCtrlSlaveAddr->GetValue().ToStdString());
    stackConfig.link.RemoteAddr = std::stoi(m_textCtrlMasterAddr->GetValue().ToStdString());

    opendnp3::DatabaseConfig device;
    for (int i = 0; i < m_spinCtrlBinaryInput->GetValue(); i++)
    {
        device.binary_input[i] = {};
        device.binary_input[i].clazz = opendnp3::PointClass::Class1;
        device.binary_input[i].svariation = opendnp3::StaticBinaryVariationSpec::from_string(m_choiceStaticBinary->GetStringSelection().ToStdString());
        device.binary_input[i].evariation = opendnp3::EventBinaryVariationSpec::from_string(m_choiceEventBinary->GetStringSelection().ToStdString());
    }
    for (int i = 0; i < m_spinCtrlDBit->GetValue(); i++)
    {
        device.double_binary[i] = {};

        device.double_binary[i].clazz = opendnp3::PointClass::Class1;
        device.double_binary[i].svariation = opendnp3::StaticDoubleBinaryVariationSpec::from_string(m_choiceStaticDBit->GetStringSelection().ToStdString());
        device.double_binary[i].evariation = opendnp3::EventDoubleBinaryVariationSpec::from_string(m_choiceEventDBit->GetStringSelection().ToStdString());
    }
    for (int i = 0; i < m_spinCtrlAnalogInput->GetValue(); i++)
    {
        device.analog_input[i] = {};

        device.analog_input[i].clazz = opendnp3::PointClass::Class1;
        device.analog_input[i].svariation = opendnp3::StaticAnalogVariationSpec::from_string(m_choiceStaticAnalogInput->GetStringSelection().ToStdString());
        device.analog_input[i].evariation = opendnp3::EventAnalogVariationSpec::from_string(m_choiceEventAnalogInput->GetStringSelection().ToStdString());
    }
    for (int i = 0; i < m_spinCtrlCounter->GetValue(); i++)
    {
        device.counter[i] = {};

        device.counter[i].clazz = opendnp3::PointClass::Class1;
        device.counter[i].svariation = opendnp3::StaticCounterVariationSpec::from_string(m_choiceStaticCounter->GetStringSelection().ToStdString());
        device.counter[i].evariation = opendnp3::EventCounterVariationSpec::from_string(m_choiceEventCounter->GetStringSelection().ToStdString());
    }
    for (int i = 0; i < m_spinCtrlFCounter->GetValue(); i++)
    {
        device.counter[i] = {};

        device.frozen_counter[i].clazz = opendnp3::PointClass::Class1;
        device.frozen_counter[i].svariation = opendnp3::StaticFrozenCounterVariationSpec::from_string(m_choiceStaticFCounter->GetStringSelection().ToStdString());
        device.frozen_counter[i].evariation = opendnp3::EventFrozenCounterVariationSpec::from_string(m_choiceEventFCounter->GetStringSelection().ToStdString());
    }
    for (int i = 0; i < m_spinCtrlBinaryOutput->GetValue(); i++)
    {
        device.counter[i] = {};

        device.binary_output_status[i].clazz = opendnp3::PointClass::Class1;
        device.binary_output_status[i].svariation = opendnp3::StaticBinaryOutputStatusVariationSpec::from_string(m_choiceStaticBinaryOutput->GetStringSelection().ToStdString());
        device.binary_output_status[i].evariation = opendnp3::EventBinaryOutputStatusVariationSpec::from_string(m_choiceEventBinaryOutput->GetStringSelection().ToStdString());
    }
    for (int i = 0; i < m_spinCtrlAnalogOutput->GetValue(); i++)
    {
        device.counter[i] = {};

        device.analog_output_status[i].clazz = opendnp3::PointClass::Class1;
        device.analog_output_status[i].svariation = opendnp3::StaticAnalogOutputStatusVariationSpec::from_string(m_choiceStaticAnalogOutput->GetStringSelection().ToStdString());
        device.analog_output_status[i].evariation = opendnp3::EventAnalogOutputStatusVariationSpec::from_string(m_choiceEventAnalogOutput->GetStringSelection().ToStdString());
    }

    stackConfig.database = device;

    stackConfig.outstation.params.allowUnsolicited = m_checkBoxUnsol->GetValue();
    //    stackConfig.outstation.params.unsolClassMask = opendnp3::ClassField::AllClasses();
    stackConfig.outstation.eventBufferConfig = opendnp3::EventBufferConfig::AllTypes(100);
}

void MPanelSlave::DeleteObjects()
{
    if (m_gridBinaryInput->GetNumberRows() > 0)
    {
        m_gridBinaryInput->DeleteRows(0, m_gridBinaryInput->GetNumberRows());
    }
    if (m_gridDBinaryInput->GetNumberRows() > 0)
    {
        m_gridDBinaryInput->DeleteRows(0, m_gridDBinaryInput->GetNumberRows());
    }
    if (m_gridAnalogInput->GetNumberRows() > 0)
    {
        m_gridAnalogInput->DeleteRows(0, m_gridAnalogInput->GetNumberRows());
    }
    if (m_gridCounter->GetNumberRows() > 0)
    {
        m_gridCounter->DeleteRows(0, m_gridCounter->GetNumberRows());
    }
    if (m_gridFCounter->GetNumberRows() > 0)
    {
        m_gridFCounter->DeleteRows(0, m_gridFCounter->GetNumberRows());
    }
    if (m_gridBinaryOut->GetNumberRows() > 0)
    {
        m_gridBinaryOut->DeleteRows(0, m_gridBinaryOut->GetNumberRows());
    }
    if (m_gridAnalogOut->GetNumberRows() > 0)
    {
        m_gridAnalogOut->DeleteRows(0, m_gridAnalogOut->GetNumberRows());
    }
}

void MPanelSlave::SelectConfig()
{
    m_listbookObjects->SetSelection(0);
}

void MPanelSlave::AddLog(const std::string &str)
{
    if (panel_event_id > 0)
    {
        wxCommandEvent e(panel_event_id);
        e.SetExtraLong(0);
        e.SetClientData(new std::string(str));
        wxPostEvent(GetEventHandler(), e);
    }
}

void MPanelSlave::UpdateBinaryValueCell(int row, bool value)
{    
    if (panel_event_id > 0)
    {
        wxCommandEvent e(panel_event_id);
        e.SetExtraLong(1);
        e.SetClientData(new Cell(m_gridBinaryInput, row, col_value, value ? "ON" : "OFF"));
        wxPostEvent(GetEventHandler(), e);
    }
}

void MPanelSlave::UpdateDBinaryValueCell(int row, opendnp3::DoubleBit value)
{    
    if (panel_event_id > 0)
    {
        wxCommandEvent e(panel_event_id);
        e.SetExtraLong(1);
        e.SetClientData(new Cell(m_gridDBinaryInput, row, col_value, opendnp3::DoubleBitSpec::to_string(value)));
        wxPostEvent(GetEventHandler(), e);
    }
}

void MPanelSlave::UpdateAnalogValueCell(int row, double value)
{    
    if (panel_event_id > 0)
    {
        wxCommandEvent e(panel_event_id);
        e.SetExtraLong(1);
        e.SetClientData(new Cell(m_gridAnalogInput, row, col_value, std::to_string(value)));
        wxPostEvent(GetEventHandler(), e);
    }
}

void MPanelSlave::UpdateCounterValueCell(int row, std::uint32_t value)
{    
    if (panel_event_id > 0)
    {
        wxCommandEvent e(panel_event_id);
        e.SetExtraLong(1);
        e.SetClientData(new Cell(m_gridCounter, row, col_value, std::to_string(value)));
        wxPostEvent(GetEventHandler(), e);
    }
}

void MPanelSlave::ReadStateFromGui()
{
    for (int i = 0; i < m_gridBinaryInput->GetNumberRows(); i++)
    {
        wxString state = m_gridBinaryInput->GetCellValue(i, col_value);
        bool bstate = state == "ON";
        m_slave->UpdateBinary(bstate, quality_to_type<opendnp3::BinaryQualitySpec>(m_gridBinaryInput->GetCellValue(i, col_flags)),
                              std::stoul(m_gridBinaryInput->GetCellValue(i, col_index).ToStdString()));
    }
    for (int i = 0; i < m_gridBinaryInput->GetNumberRows(); i++)
    {
        wxString state = m_gridBinaryInput->GetCellValue(i, col_random);
        if(state == "ON")
            m_slave->AddBinaryRandom(i);
    }
    for (int i = 0; i < m_gridDBinaryInput->GetNumberRows(); i++)
    {
        std::string state = m_gridDBinaryInput->GetCellValue(i, col_value).ToStdString();
        opendnp3::DoubleBit db;
        if (state == "INTERMEDIATE")
            db = opendnp3::DoubleBit::INDETERMINATE;
        else if (state == "DETERMINED_OFF")
            db = opendnp3::DoubleBit::DETERMINED_OFF;
        else if (state == "DETERMINED_ON")
            db = opendnp3::DoubleBit::DETERMINED_ON;
        else
            db = opendnp3::DoubleBit::INDETERMINATE;
        m_slave->UpdateDouble(db, quality_to_type<opendnp3::DoubleBitBinaryQualitySpec>(m_gridDBinaryInput->GetCellValue(i, col_flags)),
                              std::stoul(m_gridDBinaryInput->GetCellValue(i, col_index).ToStdString()));
    }
    for (int i = 0; i < m_gridDBinaryInput->GetNumberRows(); i++)
    {
        wxString state = m_gridDBinaryInput->GetCellValue(i, col_random);
        if(state == "ON")
            m_slave->AddDBinaryRandom(i);
    }
    for (int i = 0; i < m_gridAnalogInput->GetNumberRows(); i++)
    {
        wxString v = m_gridAnalogInput->GetCellValue(i, col_value);
        double state = std::stod(v.ToStdString());
        m_slave->UpdateAnalog(state, quality_to_type<opendnp3::AnalogQualitySpec>(m_gridAnalogInput->GetCellValue(i, col_flags)),
                              std::stoul(m_gridAnalogInput->GetCellValue(i, col_index).ToStdString()));
    }
    for (int i = 0; i < m_gridAnalogInput->GetNumberRows(); i++)
    {
        const wxString state = m_gridAnalogInput->GetCellValue(i, col_random);
        if(state != "OFF")
        {
            const std::string s = state.ToStdString();
            const std::regex pattern(R"((-?\d+(\.\d+)?)\s*:\s*(-?\d+(\.\d+)?))");
            std::smatch matches;
            if (std::regex_match(s, matches, pattern)) {
                const double first = std::stod(matches[1]);
                const double second = std::stod(matches[3]);
                m_slave->AddAnalogRandom(i, first, second);
            }
            else
            {
                m_gridAnalogInput->SetCellValue(i, col_random, "OFF");
            }
        }
    }
    for (int i = 0; i < m_gridCounter->GetNumberRows(); i++)
    {
        std::uint32_t state = std::stoi(m_gridCounter->GetCellValue(i, col_value).ToStdString());
        m_slave->UpdateCounter(state, quality_to_type<opendnp3::CounterQualitySpec>(m_gridCounter->GetCellValue(i, col_flags)),
                               std::stoul(m_gridCounter->GetCellValue(i, col_index).ToStdString()));
    }
    for (int i = 0; i < m_gridCounter->GetNumberRows(); i++)
    {
        wxString state = m_gridCounter->GetCellValue(i, col_increment);
        if(state == "ON")
            m_slave->AddCounterIncrement(i);
    }
    for (int i = 0; i < m_gridFCounter->GetNumberRows(); i++)
    {
        m_slave->FreezeCounter(std::stoul(m_gridCounter->GetCellValue(i, col_index).ToStdString()));
    }
    for (int i = 0; i < m_gridBinaryOut->GetNumberRows(); i++)
    {
        wxString state = m_gridBinaryOut->GetCellValue(i, col_value);
        bool bstate = state == "ON";
        m_slave->UpdateBinaryOutputStatus(bstate, quality_to_type<opendnp3::BinaryOutputStatusQualitySpec>(m_gridBinaryOut->GetCellValue(i, col_flags)),
                                          std::stoul(m_gridBinaryOut->GetCellValue(i, col_index).ToStdString()));
    }
    for (int i = 0; i < m_gridAnalogOut->GetNumberRows(); i++)
    {
        std::uint32_t state = std::stoi(m_gridAnalogOut->GetCellValue(i, col_value).ToStdString());
        m_slave->UpdateAnalogOutputStatus(state, quality_to_type<opendnp3::AnalogOutputStatusQualitySpec>(m_gridAnalogOut->GetCellValue(i, col_flags)),
                                          std::stoul(m_gridAnalogOut->GetCellValue(i, col_index).ToStdString()));
    }
}

void MPanelSlave::SlaveStart()
{
    if (m_slave == NULL)
    {
        MFrame *mf = dynamic_cast<MFrame *>(GetParent()->GetGrandParent());
        int sel = mf->m_listBoxChannels->GetSelection();
        if (sel != -1)
        {
            mf->notebooks_slaves[sel]->SetPageText(mf->notebooks_slaves[sel]->GetPageIndex(this), m_textCtrlSlaveName->GetValue());
            _name = m_textCtrlSlaveName->GetValue().ToStdString();
            ReadSlaveConfig();
            m_slave = new MSlave(this, static_cast<ClientChannel *>(mf->m_listBoxChannels->GetClientObject(sel))->channel, _name, opendnp3::levels::NORMAL, stackConfig);
            ReadStateFromGui();
            m_slave->Start();
            if(m_checkBoxRandom->IsChecked())
            {
                m_slave->StartRandomize(m_spinCtrlRandom->GetValue());
            }
        }
        else
        {
            throw std::runtime_error("No select channel !");
        }
    }
}

void MPanelSlave::SlaveStop()
{
    if (m_slave)
    {
        m_slave->Shutdown();
        delete m_slave;
        m_slave = NULL;
    }
}

void MPanelSlave::AppendBinaryInput(int l)
{
    m_gridBinaryInput->BeginBatch();
    m_gridBinaryInput->AppendRows(l);
    for (int i = m_gridBinaryInput->GetNumberRows() - l; i < m_gridBinaryInput->GetNumberRows(); i++)
    {
        m_gridBinaryInput->SetCellValue(i, col_index, wxString::Format("%i", i));
        m_gridBinaryInput->SetReadOnly(i, col_index);
        m_gridBinaryInput->SetCellValue(i, col_descrypt, wxString::Format("%s%i", "BinaryIn", i));
        m_gridBinaryInput->SetCellValue(i, col_value, "OFF");
        m_gridBinaryInput->SetReadOnly(i, col_value);
        m_gridBinaryInput->SetCellValue(i, col_flags, opendnp3::BinaryQualitySpec::to_string(opendnp3::BinaryQuality::ONLINE));
        m_gridBinaryInput->SetReadOnly(i, col_flags);
        m_gridBinaryInput->SetCellRenderer(i, col_random, new wxGridCellBoolRenderer());
        m_gridBinaryInput->SetCellEditor(i, col_random, new wxGridCellBoolEditor());
        m_gridBinaryInput->SetCellValue(i, col_random, "OFF");
        
    }
    m_gridBinaryInput->EndBatch();
}

void MPanelSlave::LoadBinaryInput(const wxXmlNode *ele)
{
    std::size_t n = std::stoi(ele->GetAttribute("Count").ToStdString());
    m_spinCtrlBinaryInput->SetValue(n);
    m_gridBinaryInput->AppendRows(n);
    m_choiceStaticBinary->SetStringSelection(ele->GetAttribute("DefStatic"));
    m_choiceEventBinary->SetStringSelection(ele->GetAttribute("DefEvent"));
    const wxXmlNode *item = ele->GetChildren();
    while (item)
    {
        wxString sindex = item->GetAttribute("Index");
        std::size_t index = std::stoi(sindex.ToStdString());
        wxString val = item->GetAttribute("Value");
        wxString desc = item->GetAttribute("Description");
        wxString fl = item->GetAttribute("Flags");
        wxString rand = item->GetAttribute("Random", "OFF");

        m_gridBinaryInput->BeginBatch();
        m_gridBinaryInput->SetCellValue(index, col_index, sindex);
        m_gridBinaryInput->SetReadOnly(index, col_index);
        m_gridBinaryInput->SetCellValue(index, col_descrypt, desc);
        m_gridBinaryInput->SetCellValue(index, col_value, val);
        m_gridBinaryInput->SetReadOnly(index, col_value);
        m_gridBinaryInput->SetCellValue(index, col_flags, fl);
        m_gridBinaryInput->SetReadOnly(index, col_flags);
        m_gridBinaryInput->SetCellRenderer(index, col_random, new wxGridCellBoolRenderer());
        m_gridBinaryInput->SetCellEditor(index, col_random, new wxGridCellBoolEditor());
        m_gridBinaryInput->SetCellValue(index, col_random, rand);
        m_gridBinaryInput->EndBatch();
        item = item->GetNext();
    }
}

void MPanelSlave::AppendDBinaryInput(int l)
{
    m_gridDBinaryInput->BeginBatch();
    m_gridDBinaryInput->AppendRows(l);
    for (int i = m_gridDBinaryInput->GetNumberRows() - l; i < m_gridDBinaryInput->GetNumberRows(); i++)
    {
        m_gridDBinaryInput->SetCellValue(i, col_index, wxString::Format("%i", i));
        m_gridDBinaryInput->SetReadOnly(i, col_index);
        m_gridDBinaryInput->SetCellValue(i, col_descrypt, wxString::Format("%s%i", "DBinaryIn", i));
        m_gridDBinaryInput->SetCellValue(i, col_value, opendnp3::DoubleBitSpec::to_string(opendnp3::DoubleBit::INTERMEDIATE));
        m_gridDBinaryInput->SetReadOnly(i, col_value);
        m_gridDBinaryInput->SetCellValue(i, col_flags, opendnp3::DoubleBitBinaryQualitySpec::to_string(opendnp3::DoubleBitBinaryQuality::ONLINE));
        m_gridDBinaryInput->SetReadOnly(i, col_flags);
        m_gridDBinaryInput->SetCellRenderer(i, col_random, new wxGridCellBoolRenderer());
        m_gridDBinaryInput->SetCellEditor(i, col_random, new wxGridCellBoolEditor());
        m_gridDBinaryInput->SetCellValue(i, col_random, "OFF");
    }
    m_gridDBinaryInput->EndBatch();
}

void MPanelSlave::LoadDBinaryInput(const wxXmlNode *ele)
{
    std::size_t n = std::stoi(ele->GetAttribute("Count").ToStdString());
    m_spinCtrlDBit->SetValue(n);
    m_gridDBinaryInput->AppendRows(n);
    m_choiceStaticDBit->SetStringSelection(ele->GetAttribute("DefStatic"));
    m_choiceEventDBit->SetStringSelection(ele->GetAttribute("DefEvent"));
    const wxXmlNode *item = ele->GetChildren();
    while (item)
    {
        wxString sindex = item->GetAttribute("Index");
        std::size_t index = std::stoi(sindex.ToStdString());
        wxString val = item->GetAttribute("Value");
        wxString desc = item->GetAttribute("Description");
        wxString fl = item->GetAttribute("Flags");
        wxString rand = item->GetAttribute("Random", "OFF");

        m_gridDBinaryInput->BeginBatch();
        m_gridDBinaryInput->SetCellValue(index, col_index, sindex);
        m_gridDBinaryInput->SetReadOnly(index, col_index);
        m_gridDBinaryInput->SetCellValue(index, col_descrypt, desc);
        m_gridDBinaryInput->SetCellValue(index, col_value, val);
        m_gridDBinaryInput->SetReadOnly(index, col_value);
        m_gridDBinaryInput->SetCellValue(index, col_flags, fl);
        m_gridDBinaryInput->SetReadOnly(index, col_flags);
        m_gridDBinaryInput->SetCellRenderer(index, col_random, new wxGridCellBoolRenderer());
        m_gridDBinaryInput->SetCellEditor(index, col_random, new wxGridCellBoolEditor());
        m_gridDBinaryInput->SetCellValue(index, col_random, rand);
        m_gridDBinaryInput->EndBatch();

        item = item->GetNext();
    }
}

void MPanelSlave::AppendAnalogInput(int l)
{
    m_gridAnalogInput->BeginBatch();
    m_gridAnalogInput->AppendRows(l);
    for (int i = m_gridAnalogInput->GetNumberRows() - l; i < m_gridAnalogInput->GetNumberRows(); i++)
    {
        m_gridAnalogInput->SetCellValue(i, col_index, wxString::Format("%i", i));
        m_gridAnalogInput->SetReadOnly(i, col_index);
        m_gridAnalogInput->SetCellValue(i, col_descrypt, wxString::Format("%s%i", "AnalogIn", i));
        m_gridAnalogInput->SetCellValue(i, col_value, "0.0");
        m_gridAnalogInput->SetReadOnly(i, col_value);
        m_gridAnalogInput->SetCellValue(i, col_flags,  opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::ONLINE));
        m_gridAnalogInput->SetReadOnly(i, col_flags);
        m_gridAnalogInput->SetCellValue(i, col_random, "OFF");
    }
    m_gridAnalogInput->EndBatch();
}

void MPanelSlave::LoadAnalogInput(const wxXmlNode *ele)
{
    std::size_t n = std::stoi(ele->GetAttribute("Count").ToStdString());
    m_spinCtrlAnalogInput->SetValue(n);
    m_gridAnalogInput->AppendRows(n);
    m_choiceStaticAnalogInput->SetStringSelection(ele->GetAttribute("DefStatic"));
    m_choiceEventAnalogInput->SetStringSelection(ele->GetAttribute("DefEvent"));
    const wxXmlNode *item = ele->GetChildren();
    while (item)
    {
        wxString sindex = item->GetAttribute("Index");
        std::size_t index = std::stoi(sindex.ToStdString());
        wxString val = item->GetAttribute("Value");
        wxString desc = item->GetAttribute("Description");
        wxString fl = item->GetAttribute("Flags");
        wxString rand = item->GetAttribute("Random", "OFF");
        val.Replace(',', '.');

        m_gridAnalogInput->BeginBatch();
        m_gridAnalogInput->SetCellValue(index, col_index, sindex);
        m_gridAnalogInput->SetReadOnly(index, col_index);
        m_gridAnalogInput->SetCellValue(index, col_descrypt, desc);
        m_gridAnalogInput->SetCellValue(index, col_value, val);
        m_gridAnalogInput->SetReadOnly(index, col_value);
        m_gridAnalogInput->SetCellValue(index, col_flags, fl);
        m_gridAnalogInput->SetReadOnly(index, col_flags);
        m_gridAnalogInput->SetCellValue(index, col_random, rand);
        m_gridAnalogInput->EndBatch();

        item = item->GetNext();
    }
}

void MPanelSlave::AppendCounter(int l)
{
    m_gridCounter->BeginBatch();
    m_gridCounter->AppendRows(l);
    for (int i = m_gridCounter->GetNumberRows() - l; i < m_gridCounter->GetNumberRows(); i++)
    {
        m_gridCounter->SetCellValue(i, col_index, wxString::Format("%i", i));
        m_gridCounter->SetReadOnly(i, col_index);
        m_gridCounter->SetCellValue(i, col_descrypt, wxString::Format("%s%i", "Counter", i));
        m_gridCounter->SetCellValue(i, col_value, "0");
        m_gridCounter->SetReadOnly(i, col_value);
        m_gridCounter->SetCellValue(i, col_flags, opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::ONLINE));
        m_gridCounter->SetReadOnly(i, col_flags);
        m_gridCounter->SetCellRenderer(i, col_increment, new wxGridCellBoolRenderer());
        m_gridCounter->SetCellEditor(i, col_increment, new wxGridCellBoolEditor());
        m_gridCounter->SetCellValue(i, col_increment, "OFF");
    }
    m_gridCounter->EndBatch();
}

void MPanelSlave::LoadCounter(const wxXmlNode *ele)
{
    std::size_t n = std::stoi(ele->GetAttribute("Count").ToStdString());
    m_spinCtrlCounter->SetValue(n);
    m_gridCounter->AppendRows(n);
    m_choiceStaticCounter->SetStringSelection(ele->GetAttribute("DefStatic"));
    m_choiceEventCounter->SetStringSelection(ele->GetAttribute("DefEvent"));
    const wxXmlNode *item = ele->GetChildren();
    while (item)
    {
        wxString sindex = item->GetAttribute("Index");
        std::size_t index = std::stoi(sindex.ToStdString());
        wxString val = item->GetAttribute("Value");
        wxString desc = item->GetAttribute("Description");
        wxString fl = item->GetAttribute("Flags");
        wxString inc = item->GetAttribute("Increment", "OFF");
        if(inc.empty())
        {
            inc = "OFF";
        }
        m_gridCounter->BeginBatch();
        m_gridCounter->SetCellValue(index, col_index, sindex);
        m_gridCounter->SetReadOnly(index, col_index);
        m_gridCounter->SetCellValue(index, col_descrypt, desc);
        m_gridCounter->SetCellValue(index, col_value, val);
        m_gridCounter->SetReadOnly(index, col_value);
        m_gridCounter->SetCellValue(index, col_flags, fl);
        m_gridCounter->SetReadOnly(index, col_flags);
        m_gridCounter->SetCellRenderer(index, col_increment, new wxGridCellBoolRenderer());
        m_gridCounter->SetCellEditor(index, col_increment, new wxGridCellBoolEditor());
        m_gridCounter->SetCellValue(index, col_increment, inc);
        m_gridCounter->EndBatch();

        item = item->GetNext();
    }
}

void MPanelSlave::AppendFCounter(int l)
{
    m_gridFCounter->BeginBatch();
    m_gridFCounter->AppendRows(l);
    for (int i = m_gridFCounter->GetNumberRows() - l; i < m_gridFCounter->GetNumberRows(); i++)
    {
        m_gridFCounter->SetCellValue(i, col_index, wxString::Format("%i", i));
        m_gridFCounter->SetReadOnly(i, col_index);
        m_gridFCounter->SetCellValue(i, col_descrypt, wxString::Format("%s%i", "FCounter", i));
        m_gridFCounter->SetCellValue(i, col_value, "0");
        m_gridFCounter->SetReadOnly(i, col_value);
        m_gridFCounter->SetCellValue(i, col_flags, opendnp3::FrozenCounterQualitySpec::to_string(opendnp3::FrozenCounterQuality::ONLINE));
        m_gridFCounter->SetReadOnly(i, col_flags);
    }
    m_gridFCounter->EndBatch();
}

void MPanelSlave::LoadFCounter(const wxXmlNode *ele)
{
    std::size_t n = std::stoi(ele->GetAttribute("Count").ToStdString());
    m_spinCtrlFCounter->SetValue(n);
    m_gridFCounter->AppendRows(n);
    m_choiceStaticFCounter->SetStringSelection(ele->GetAttribute("DefStatic"));
    m_choiceEventFCounter->SetStringSelection(ele->GetAttribute("DefEvent"));
    const wxXmlNode *item = ele->GetChildren();
    while (item)
    {
        wxString sindex = item->GetAttribute("Index");
        std::size_t index = std::stoi(sindex.ToStdString());
        wxString desc = item->GetAttribute("Description");
        wxString value = item->GetAttribute("Value");
        wxString fl = item->GetAttribute("Flags");

        m_gridFCounter->BeginBatch();
        m_gridFCounter->SetCellValue(index, col_index, sindex);
        m_gridFCounter->SetReadOnly(index, col_index);
        m_gridFCounter->SetCellValue(index, col_value, value);
        m_gridFCounter->SetReadOnly(index, col_value);
        m_gridFCounter->SetCellValue(index, col_descrypt, desc);
        m_gridFCounter->SetCellValue(index, col_flags, fl);
        m_gridFCounter->SetReadOnly(index, col_flags);
        m_gridFCounter->EndBatch();

        item = item->GetNext();
    }
}

void MPanelSlave::AppendBinaryOutput(int l)
{
    m_gridBinaryOut->BeginBatch();
    m_gridBinaryOut->AppendRows(l);
    for (int i = m_gridBinaryOut->GetNumberRows() - l; i < m_gridBinaryOut->GetNumberRows(); i++)
    {
        m_gridBinaryOut->SetCellValue(i, col_index, wxString::Format("%i", i));
        m_gridBinaryOut->SetReadOnly(i, col_index);
        m_gridBinaryOut->SetCellValue(i, col_descrypt, wxString::Format("%s%i", "BinaryOut", i));
        m_gridBinaryOut->SetCellValue(i, col_value, "OFF");
        m_gridBinaryOut->SetReadOnly(i, col_value);
        m_gridBinaryOut->SetCellValue(i, 3, opendnp3::BinaryOutputStatusQualitySpec::to_string(opendnp3::BinaryOutputStatusQuality::ONLINE));
        m_gridBinaryOut->SetReadOnly(i, col_flags);
    }
    m_gridBinaryOut->EndBatch();
}

void MPanelSlave::LoadBinaryOuput(const wxXmlNode *ele)
{
    std::size_t n = std::stoi(ele->GetAttribute("Count").ToStdString());
    m_spinCtrlBinaryOutput->SetValue(n);
    m_gridBinaryOut->AppendRows(n);
    m_choiceStaticBinaryOutput->SetStringSelection(ele->GetAttribute("DefStatic"));
    m_choiceEventBinaryOutput->SetStringSelection(ele->GetAttribute("DefEvent"));
    const wxXmlNode *item = ele->GetChildren();
    while (item)
    {
        wxString sindex = item->GetAttribute("Index");
        std::size_t index = std::stoi(sindex.ToStdString());
        wxString val = item->GetAttribute("Value");
        wxString desc = item->GetAttribute("Description");
        wxString fl = item->GetAttribute("Flags");

        m_gridBinaryOut->BeginBatch();
        m_gridBinaryOut->SetCellValue(index, col_index, sindex);
        m_gridBinaryOut->SetReadOnly(index, col_index);
        m_gridBinaryOut->SetCellValue(index, col_descrypt, desc);
        m_gridBinaryOut->SetCellValue(index, col_value, val);
        m_gridBinaryOut->SetReadOnly(index, col_value);
        m_gridBinaryOut->SetCellValue(index, col_flags, fl);
        m_gridBinaryOut->SetReadOnly(index, col_flags);
        m_gridBinaryOut->EndBatch();

        item = item->GetNext();
    }
}

void MPanelSlave::AppendAnalogOutput(int l)
{
    m_gridAnalogOut->BeginBatch();
    m_gridAnalogOut->AppendRows(l);
    for (int i = m_gridAnalogOut->GetNumberRows() - l; i < m_gridAnalogOut->GetNumberRows(); i++)
    {
        m_gridAnalogOut->SetCellValue(i, col_index, wxString::Format("%i", i));
        m_gridAnalogOut->SetReadOnly(i, col_index);
        m_gridAnalogOut->SetCellValue(i, col_descrypt, wxString::Format("%s%i", "AnalogOut", i));
        m_gridAnalogOut->SetCellValue(i, col_value, "0.0");
        m_gridAnalogOut->SetReadOnly(i, col_value);
        m_gridAnalogOut->SetCellValue(i, col_flags, opendnp3::AnalogOutputStatusQualitySpec::to_string(opendnp3::AnalogOutputStatusQuality::ONLINE));
        m_gridAnalogOut->SetReadOnly(i, col_flags);
    }
    m_gridAnalogOut->EndBatch();
}

void MPanelSlave::LoadAnalogOutput(const wxXmlNode *ele)
{
    std::size_t n = std::stoi(ele->GetAttribute("Count").ToStdString());
    m_spinCtrlAnalogOutput->SetValue(n);
    m_gridAnalogOut->AppendRows(n);
    m_choiceStaticAnalogOutput->SetStringSelection(ele->GetAttribute("DefStatic"));
    m_choiceEventAnalogOutput->SetStringSelection(ele->GetAttribute("DefEvent"));
    const wxXmlNode *item = ele->GetChildren();
    while (item)
    {
        wxString sindex = item->GetAttribute("Index");
        std::size_t index = std::stoi(sindex.ToStdString());
        wxString val = item->GetAttribute("Value");
        wxString desc = item->GetAttribute("Description");
        wxString fl = item->GetAttribute("Flags");

        m_gridAnalogOut->BeginBatch();
        m_gridAnalogOut->SetCellValue(index, col_index, sindex);
        m_gridAnalogOut->SetReadOnly(index, col_index);
        m_gridAnalogOut->SetCellValue(index, col_descrypt, desc);
        m_gridAnalogOut->SetCellValue(index, col_value, val);
        m_gridAnalogOut->SetReadOnly(index, col_value);
        m_gridAnalogOut->SetCellValue(index, col_flags, fl);
        m_gridAnalogOut->SetReadOnly(index, col_flags);
        m_gridAnalogOut->EndBatch();

        item = item->GetNext();
    }
}

void MPanelSlave::OnButtonSyncTimeClick(wxCommandEvent &event)
{
    if (m_slave)
        m_slave->NeedTimeSync();
}

void MPanelSlave::OnSpinCtrlBinaryInput(wxSpinEvent &event)
{
    int l = event.GetValue() - m_gridBinaryInput->GetNumberRows();
    if (l > 0)
    {
        AppendBinaryInput(l);
    }
    else if (l < 0)
    {
        m_gridBinaryInput->BeginBatch();
        m_gridBinaryInput->DeleteRows(m_gridBinaryInput->GetNumberRows() + l, std::abs(l));
        m_gridDBinaryInput->EndBatch();
    }
}

void MPanelSlave::OnSpinCtrlDBinaryInput(wxSpinEvent &event)
{
    int l = event.GetValue() - m_gridDBinaryInput->GetNumberRows();
    if (l > 0)
    {
        AppendDBinaryInput(l);
    }
    else if (l < 0)
    {
        m_gridDBinaryInput->BeginBatch();
        m_gridDBinaryInput->DeleteRows(m_gridDBinaryInput->GetNumberRows() + l, std::abs(l));
        m_gridDBinaryInput->EndBatch();
    }
}

void MPanelSlave::OnSpinCtrlAnalogInput(wxSpinEvent &event)
{
    int l = event.GetValue() - m_gridAnalogInput->GetNumberRows();
    if (l > 0)
    {
        AppendAnalogInput(l);
    }
    else if (l < 0)
    {
        m_gridAnalogInput->BeginBatch();
        m_gridAnalogInput->DeleteRows(m_gridAnalogInput->GetNumberRows() + l, std::abs(l));
        m_gridAnalogInput->EndBatch();
    }
}

void MPanelSlave::OnSpinCtrlCounter(wxSpinEvent &event)
{
    int l = event.GetValue() - m_gridCounter->GetNumberRows();
    if (l > 0)
    {
        AppendCounter(l);
        m_spinCtrlFCounter->SetRange(0, event.GetValue());
    }
    else if (l < 0)
    {
        m_gridCounter->BeginBatch();
        m_gridCounter->DeleteRows(m_gridCounter->GetNumberRows() + l, std::abs(l));
        m_gridCounter->EndBatch();
        int lf = m_gridFCounter->GetNumberRows() - m_gridCounter->GetNumberRows();
        if(lf > 0)
        {
            m_spinCtrlFCounter->SetValue(m_gridCounter->GetNumberRows());
            wxSpinEvent sv(wxEVT_COMMAND_SPINCTRL_UPDATED);
            sv.SetValue(m_gridCounter->GetNumberRows());
            wxPostEvent(m_spinCtrlFCounter, sv);
        }
    }
}

void MPanelSlave::OnSpinCtrlFCounter(wxSpinEvent &event)
{
    int l = event.GetValue() - m_gridFCounter->GetNumberRows();
    if (l > 0)
    {
        AppendFCounter(l);
    }
    else if (l < 0)
    {
        m_gridFCounter->BeginBatch();
        m_gridFCounter->DeleteRows(m_gridFCounter->GetNumberRows() + l, std::abs(l));
        m_gridFCounter->EndBatch();
    }
}

void MPanelSlave::OnSpinCtrlBinaryOutput(wxSpinEvent &event)
{
    int l = event.GetValue() - m_gridBinaryOut->GetNumberRows();
    if (l > 0)
    {
        AppendBinaryOutput(l);
    }
    else if (l < 0)
    {
        m_gridBinaryOut->BeginBatch();
        m_gridBinaryOut->DeleteRows(m_gridBinaryOut->GetNumberRows() + l, std::abs(l));
        m_gridBinaryOut->EndBatch();
    }
}

void MPanelSlave::OnSpinCtrlAnalogOutput(wxSpinEvent &event)
{
    int l = event.GetValue() - m_gridAnalogOut->GetNumberRows();
    if (l > 0)
    {
        AppendAnalogOutput(l);
    }
    else if (l < 0)
    {
        m_gridAnalogOut->BeginBatch();
        m_gridAnalogOut->DeleteRows(m_gridAnalogOut->GetNumberRows() + l, std::abs(l));
        m_gridAnalogOut->EndBatch();
    }
}

void MPanelSlave::OnCheckBoxLeftDown( wxMouseEvent& event )
{
    event.Skip();
}

void MPanelSlave::OnGridCellChangeBinaryInput(wxGridEvent &event)
{
    try
    {
        if (event.GetCol() >= col_value && event.GetCol() < col_random)
        {
            if (m_slave)
            {
                wxString state = m_gridBinaryInput->GetCellValue(event.GetRow(), col_value);
                wxString quality = m_gridBinaryInput->GetCellValue(event.GetRow(), col_flags);
                auto sd = new MBinaryDialog(this, state, quality,
                                            [this, &event](const wxString &val, const wxString &qual)
                                            {
                                                bool bstate = (val == "ON");
                                                m_slave->UpdateBinary(bstate, quality_to_type<opendnp3::BinaryQualitySpec>(qual),
                                                                      std::stoul(m_gridBinaryInput->GetCellValue(event.GetRow(), col_index).ToStdString()));
                                                m_gridBinaryInput->SetCellValue(event.GetRow(), col_value, val);
                                                m_gridBinaryInput->SetCellValue(event.GetRow(), col_flags, qual);
                                            });
                sd->ShowModal();
            }
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MPanelSlave::OnGridCellChangeDBinaryInput(wxGridEvent &event)
{
    try
    {
        if (event.GetCol() >= col_value && event.GetCol() < col_random)
        {
            if (m_slave)
            {
                std::string state = m_gridDBinaryInput->GetCellValue(event.GetRow(), col_value).ToStdString();
                wxString quality = m_gridDBinaryInput->GetCellValue(event.GetRow(), col_flags);
                wxString random = m_gridDBinaryInput->GetCellValue(event.GetRow(), col_random);
                auto sd = new MDBinaryDialog(this, state, quality,
                                             [this, &event](const wxString &val, const wxString &qual)
                                             {
                                                 auto dbs = opendnp3::DoubleBitSpec::from_string(val.ToStdString());
                                                 m_slave->UpdateDouble(dbs, quality_to_type<opendnp3::DoubleBitBinaryQualitySpec>(qual),
                                                                       std::stoul(m_gridDBinaryInput->GetCellValue(event.GetRow(), col_index).ToStdString()));
                                                 m_gridDBinaryInput->SetCellValue(event.GetRow(), col_value, val);
                                                 m_gridDBinaryInput->SetCellValue(event.GetRow(), col_flags, qual);
                                             });
                sd->ShowModal();
            }
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MPanelSlave::OnGridCellChangeAnalogInput(wxGridEvent &event)
{
    try
    {
        if (event.GetCol() >= col_value && event.GetCol() < col_random)
        {
            if (m_slave)
            {
                wxString state = m_gridAnalogInput->GetCellValue(event.GetRow(), col_value);
                wxString quality = m_gridAnalogInput->GetCellValue(event.GetRow(), col_flags);
                auto sd = new MAnalogDialog(this, state, quality,
                                            [this, &event](const wxString &val, const wxString &qual)
                                            {
                                                double dbs = std::stod(val.ToStdString());
                                                m_slave->UpdateAnalog(dbs, quality_to_type<opendnp3::AnalogQualitySpec>(qual),
                                                                      std::stoul(m_gridAnalogInput->GetCellValue(event.GetRow(), col_index).ToStdString()));
                                                m_gridAnalogInput->SetCellValue(event.GetRow(), col_value, val);
                                                m_gridAnalogInput->SetCellValue(event.GetRow(), col_flags, qual);
                                            });
                sd->ShowModal();
            }
        }
        else if(event.GetCol() == col_random)
        {
            
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MPanelSlave::OnGridCellChangeCounter(wxGridEvent &event)
{
    try
    {
        if (event.GetCol() >= col_value && event.GetCol() < col_increment)
        {
            if (m_slave)
            {
                wxString state = m_gridCounter->GetCellValue(event.GetRow(), col_value);
                wxString quality = m_gridCounter->GetCellValue(event.GetRow(), col_flags);
                wxString increment = m_gridCounter->GetCellValue(event.GetRow(), col_increment);
                auto sd = new MCounterDialog(this, state, quality,
                                             [this, &event](const wxString &val, const wxString &qual)
                                             {
                                                 auto dbs = std::stoul(val.ToStdString());
                                                 m_slave->UpdateCounter(dbs, quality_to_type<opendnp3::CounterQualitySpec>(qual),
                                                                        std::stoul(m_gridCounter->GetCellValue(event.GetRow(), col_index).ToStdString()));
                                                 m_gridCounter->SetCellValue(event.GetRow(), col_value, val);
                                                 m_gridCounter->SetCellValue(event.GetRow(), col_flags, qual);
                                             });
                sd->ShowModal();
            }
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MPanelSlave::OnGridCellChangeFrozenCounter(wxGridEvent &event)
{
    try
    {
        if (event.GetCol() == col_value || event.GetCol() == col_flags)
        {
            if (m_slave)
            {
                if (m_gridCounter->GetNumberRows() > event.GetRow())
                {
                    m_slave->FreezeCounter(std::stoul(m_gridFCounter->GetCellValue(event.GetRow(), col_index).ToStdString()));
                    wxString v = m_gridCounter->GetCellValue(event.GetRow(), col_value);
                    wxString q = m_gridCounter->GetCellValue(event.GetRow(), col_flags);
                    m_gridFCounter->SetCellValue(event.GetRow(), col_value, v);
                    m_gridFCounter->SetCellValue(event.GetRow(), col_flags, q);
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}
void MPanelSlave::OnGridCellChangeBinaryOutputStatus(wxGridEvent &event)
{
    try
    {
        if (event.GetCol() == col_value || event.GetCol() == col_flags)
        {
            if (m_slave)
            {
                wxString state = m_gridBinaryOut->GetCellValue(event.GetRow(), col_value);
                bool bstate = state == "ON";
                m_slave->UpdateBinaryOutputStatus(bstate, quality_to_type<opendnp3::BinaryOutputStatusQualitySpec>(m_gridBinaryOut->GetCellValue(event.GetRow(), col_flags)),
                                                  std::stoul(m_gridBinaryOut->GetCellValue(event.GetRow(), col_index).ToStdString()));
            }
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MPanelSlave::OnGridCellChangeAnalogOutputStatus(wxGridEvent &event)
{
    try
    {
        if (event.GetCol() == col_value || event.GetCol() == col_flags)
        {
            if (m_slave)
            {
                std::uint32_t state = std::stoi(m_gridAnalogOut->GetCellValue(event.GetRow(), col_value).ToStdString());
                m_slave->UpdateAnalogOutputStatus(state, quality_to_type<opendnp3::AnalogOutputStatusQualitySpec>(m_gridAnalogOut->GetCellValue(event.GetRow(), col_flags)),
                                                  std::stoul(m_gridAnalogOut->GetCellValue(event.GetRow(), col_index).ToStdString()));
            }
        }
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MPanelSlave::OnButtonClickSlaveStart(wxCommandEvent &event)
{
    try
    {
        SlaveStart();
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MPanelSlave::OnButtonClickSlaveRestart(wxCommandEvent &event)
{
    try
    {
        SlaveStop();
        SlaveStart();
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MPanelSlave::OnButtonClickSlaveStop(wxCommandEvent &event)
{
    try
    {
        SlaveStop();
    }
    catch (const std::exception &e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal));
    }
}

void MPanelSlave::OnPanelEvent(wxCommandEvent &e)
{
    if (e.GetExtraLong() == 0)
    {
        std::string *str = static_cast<std::string *>(e.GetClientData());
        m_listBoxSlave->Freeze();
        if (m_listBoxSlave->GetCount() > 64)
            m_listBoxSlave->Delete(0);
        m_listBoxSlave->Append(wxString(*str));
        m_listBoxSlave->Select(m_listBoxSlave->GetCount() - 1);
        m_listBoxSlave->Thaw();
        delete str;
    }
    else
    {
        Cell* cell = static_cast<Cell*>(e.GetClientData());
        cell->grid->SetCellValue(cell->value, cell->row, cell->col);
        delete cell;
    }
}

MSerialParamDialog::MSerialParamDialog(wxWindow *parent) : SerialParamDialog(parent)
{
    MFrame *f = static_cast<MFrame *>(GetParent());
    m_textCtrlName->SetValue(wxString::Format("serial%u", f->last_channel));
#ifdef __linux__
    m_textCtrlPort->SetValue(wxString::Format("/dev/ttyS%u", f->last_serial_port));
#else
    m_textCtrlPort->SetValue(wxString::Format("COM%u", f->last_serial_port+1));
#endif
}

void MSerialParamDialog::Read()
{
    std::string name(m_textCtrlName->GetValue().mbc_str());
    opendnp3::SerialSettings ss;
    ss.deviceName = m_textCtrlPort->GetValue().mbc_str();
    ss.baud = std::stoi((const char *)m_textCtrlBaud->GetValue().mbc_str());
    ss.dataBits = std::stoi((const char *)m_textCtrlDataBits->GetValue().mbc_str());
    if (m_comboBoxParity->GetValue() == "none")
        ss.parity = opendnp3::Parity::None;
    else if (m_comboBoxParity->GetValue() == "even")
        ss.parity = opendnp3::Parity::Even;
    else if (m_comboBoxParity->GetValue() == "odd")
        ss.parity = opendnp3::Parity::Odd;

    if (std::string(m_comboBoxStopBits->GetValue()) == "none")
        ss.stopBits = opendnp3::StopBits::None;
    else if (m_comboBoxStopBits->GetValue() == "one")
        ss.stopBits = opendnp3::StopBits::One;
    else if (m_comboBoxStopBits->GetValue() == "two")
        ss.stopBits = opendnp3::StopBits::Two;
    else if (m_comboBoxStopBits->GetValue() == "onepointfive")
        ss.stopBits = opendnp3::StopBits::OnePointFive;

    if (m_comboBoxFlow->GetValue() == "none")
        ss.flowType = opendnp3::FlowControl::None;
    else if (m_comboBoxFlow->GetValue() == "hardware")
        ss.flowType = opendnp3::FlowControl::Hardware;
    else if (m_comboBoxFlow->GetValue() == "xonxoff")
        ss.flowType = opendnp3::FlowControl::XONXOFF;
    static_cast<MFrame *>(GetParent())->AddSerial(name, ss);
}

void MSerialParamDialog::OnButtonClickOK(wxCommandEvent &event)
{
    EndModal(wxID_OK);
}

void MSerialParamDialog::OnButtonClickCancel(wxCommandEvent &event)
{
    EndModal(wxID_CANCEL);
}

MTCPServerParamDialog::MTCPServerParamDialog(wxWindow *parent) : TCPServerParamDialog(parent)
{
    MFrame *f = static_cast<MFrame *>(GetParent());
    m_textCtrlName->SetValue(wxString::Format("tcpserver%u", f->last_channel));
    m_textCtrlPort->SetValue(wxString::Format("%u", f->last_tcp_port));
}

void MTCPServerParamDialog::Read()
{
    std::string name(m_textCtrlName->GetValue().mbc_str());
    std::string addr(m_textCtrlAddress->GetValue().mbc_str());
    std::uint16_t port(std::stoi((const char *)m_textCtrlPort->GetValue().mbc_str()));
    static_cast<MFrame *>(GetParent())->AddTCPServer(name, addr, port);
}

void MTCPServerParamDialog::OnButtonClickOK(wxCommandEvent &event)
{
    EndModal(wxID_OK);
}

void MTCPServerParamDialog::OnButtonClickCancel(wxCommandEvent &event)
{
    EndModal(wxID_CANCEL);
}

void TCPServerClientChannel::SaveToXML(wxXmlNode *ele)
{
    ele->AddAttribute("Type", "TCPServer");
    ele->AddAttribute("Name", name.c_str());
    ele->AddAttribute("Address", address.c_str());
    wxString p;
    p << port;
    ele->AddAttribute("Port", p);
}

void SerialClientChannel::SaveToXML(wxXmlNode *ele)
{
    ele->AddAttribute("Type", "Serial");
    ele->AddAttribute("Name", name);
    ele->AddAttribute("Port", serial_settings.deviceName.c_str());
    wxString b;
    b << serial_settings.baud;
    ele->AddAttribute("Baud", b);
    wxString d;
    d << serial_settings.dataBits;
    ele->AddAttribute("DataBits", d);
    if (serial_settings.parity == opendnp3::Parity::None)
        ele->AddAttribute("Parity", "none");
    else if (serial_settings.parity == opendnp3::Parity::Even)
        ele->AddAttribute("Parity", "even");
    else if (serial_settings.parity == opendnp3::Parity::Odd)
        ele->AddAttribute("Parity", "odd");

    if (serial_settings.stopBits == opendnp3::StopBits::None)
        ele->AddAttribute("StopBits", "none");
    else if (serial_settings.stopBits == opendnp3::StopBits::One)
        ele->AddAttribute("StopBits", "one");
    else if (serial_settings.stopBits == opendnp3::StopBits::OnePointFive)
        ele->AddAttribute("StopBits", "onepointfive");
    else if (serial_settings.stopBits == opendnp3::StopBits::Two)
        ele->AddAttribute("StopBits", "two");

    if (serial_settings.flowType == opendnp3::FlowControl::None)
        ele->AddAttribute("Flow", "none");
    else if (serial_settings.flowType == opendnp3::FlowControl::Hardware)
        ele->AddAttribute("Flow", "hardware");
    else if (serial_settings.flowType == opendnp3::FlowControl::XONXOFF)
        ele->AddAttribute("Flow", "xonxoff");
}

MStateDialog::MStateDialog(wxWindow *parent, OnChange fun) : StateDialog(parent), on_change(fun)
{

}

void MStateDialog::StateDialogOnApplyButtonClick(wxCommandEvent &event)
{
    write();
}

void MStateDialog::StateDialogOnCancelButtonClick(wxCommandEvent &event)
{
    EndModal(wxID_CANCEL);
}

void MStateDialog::StateDialogOnOKButtonClick(wxCommandEvent &event)
{
    write();
    EndModal(wxID_OK);
}

MBinaryDialog::MBinaryDialog(wxWindow* parent, const wxString& old_val, const wxString& old_qual, OnChange fun) : MStateDialog(parent, fun)
{
    binary_value = new wxCheckBox(m_panelStateDialog, wxID_ANY, wxT("State"), wxDefaultPosition, wxDefaultSize, 0);
    binary_value->SetValue(old_val == "ON" ? true : false);
    bSizerValue->Add(binary_value, 0, wxALL, 5);

    Fit();
    read(old_val, old_qual);
}

void MBinaryDialog::read(const wxString &old_val, const wxString &old_qual)
{
    opendnp3::Flags f(quality_to_uint8<opendnp3::BinaryQualitySpec>(old_qual));
    m_checkBoxQuality0->SetLabel(opendnp3::BinaryQualitySpec::to_string(opendnp3::BinaryQuality::ONLINE));
    m_checkBoxQuality0->SetValue(f.IsSet(opendnp3::BinaryQuality::ONLINE));
    m_checkBoxQuality1->SetLabel(opendnp3::BinaryQualitySpec::to_string(opendnp3::BinaryQuality::RESTART));
    m_checkBoxQuality1->SetValue(f.IsSet(opendnp3::BinaryQuality::RESTART));
    m_checkBoxQuality2->SetLabel(opendnp3::BinaryQualitySpec::to_string(opendnp3::BinaryQuality::COMM_LOST));
    m_checkBoxQuality2->SetValue(f.IsSet(opendnp3::BinaryQuality::COMM_LOST));
    m_checkBoxQuality3->SetLabel(opendnp3::BinaryQualitySpec::to_string(opendnp3::BinaryQuality::REMOTE_FORCED));
    m_checkBoxQuality3->SetValue(f.IsSet(opendnp3::BinaryQuality::REMOTE_FORCED));
    m_checkBoxQuality4->SetLabel(opendnp3::BinaryQualitySpec::to_string(opendnp3::BinaryQuality::LOCAL_FORCED));
    m_checkBoxQuality4->SetValue(f.IsSet(opendnp3::BinaryQuality::LOCAL_FORCED));
    m_checkBoxQuality5->SetLabel(opendnp3::BinaryQualitySpec::to_string(opendnp3::BinaryQuality::CHATTER_FILTER));
    m_checkBoxQuality5->SetValue(f.IsSet(opendnp3::BinaryQuality::CHATTER_FILTER));
    m_checkBoxQuality6->SetLabel(opendnp3::BinaryQualitySpec::to_string(opendnp3::BinaryQuality::RESERVED));
    m_checkBoxQuality6->SetValue(f.IsSet(opendnp3::BinaryQuality::RESERVED));
    m_checkBoxQuality7->SetLabel("---");
    m_checkBoxQuality7->Disable();
}

void MBinaryDialog::write()
{
    wxString val, qual;
    val = binary_value->IsChecked() ? "ON" : "OFF";
    qual =  (m_checkBoxQuality6->IsChecked() ? opendnp3::BinaryQualitySpec::to_string(opendnp3::BinaryQuality::RESERVED) + wxString(" ") : "");
    qual +=  (m_checkBoxQuality5->IsChecked() ? opendnp3::BinaryQualitySpec::to_string(opendnp3::BinaryQuality::CHATTER_FILTER) + wxString(" ") : "");
    qual +=  (m_checkBoxQuality4->IsChecked() ? opendnp3::BinaryQualitySpec::to_string(opendnp3::BinaryQuality::LOCAL_FORCED) + wxString(" ") : "");
    qual +=  (m_checkBoxQuality3->IsChecked() ? opendnp3::BinaryQualitySpec::to_string(opendnp3::BinaryQuality::REMOTE_FORCED) + wxString(" ") : "");
    qual +=  (m_checkBoxQuality2->IsChecked() ? opendnp3::BinaryQualitySpec::to_string(opendnp3::BinaryQuality::COMM_LOST) + wxString(" ") : "");
    qual +=  (m_checkBoxQuality1->IsChecked() ? opendnp3::BinaryQualitySpec::to_string(opendnp3::BinaryQuality::RESTART) + wxString(" ") : "");
    qual +=  (m_checkBoxQuality0->IsChecked() ? opendnp3::BinaryQualitySpec::to_string(opendnp3::BinaryQuality::ONLINE) : "");
    on_change(val, qual);
}

MDBinaryDialog::MDBinaryDialog(wxWindow *parent, const wxString &old_val, const wxString &old_qual, OnChange fun) : MStateDialog(parent, fun)
{
    wxArrayString as;
    as.Add(opendnp3::DoubleBitSpec::to_string(opendnp3::DoubleBit::INTERMEDIATE));
    as.Add(opendnp3::DoubleBitSpec::to_string(opendnp3::DoubleBit::DETERMINED_OFF));
    as.Add(opendnp3::DoubleBitSpec::to_string(opendnp3::DoubleBit::DETERMINED_ON));
    as.Add(opendnp3::DoubleBitSpec::to_string(opendnp3::DoubleBit::INDETERMINATE));
    combo = new wxComboBox(m_panelStateDialog, wxID_ANY, old_val, wxDefaultPosition, wxDefaultSize, as);
    bSizerValue->Add(combo, 0, wxALL, 5);

    Fit();
    read(old_val, old_qual);
}

void MDBinaryDialog::read(const wxString &old_val, const wxString &old_qual)
{
    opendnp3::Flags f(quality_to_uint8<opendnp3::DoubleBitBinaryQualitySpec>(old_qual));
    m_checkBoxQuality0->SetLabel(opendnp3::DoubleBitBinaryQualitySpec::to_string(opendnp3::DoubleBitBinaryQuality::ONLINE));
    m_checkBoxQuality0->SetValue(f.IsSet(opendnp3::DoubleBitBinaryQuality::ONLINE));
    m_checkBoxQuality1->SetLabel(opendnp3::DoubleBitBinaryQualitySpec::to_string(opendnp3::DoubleBitBinaryQuality::RESTART));
    m_checkBoxQuality1->SetValue(f.IsSet(opendnp3::DoubleBitBinaryQuality::RESTART));
    m_checkBoxQuality2->SetLabel(opendnp3::DoubleBitBinaryQualitySpec::to_string(opendnp3::DoubleBitBinaryQuality::COMM_LOST));
    m_checkBoxQuality2->SetValue(f.IsSet(opendnp3::DoubleBitBinaryQuality::COMM_LOST));
    m_checkBoxQuality3->SetLabel(opendnp3::DoubleBitBinaryQualitySpec::to_string(opendnp3::DoubleBitBinaryQuality::REMOTE_FORCED));
    m_checkBoxQuality3->SetValue(f.IsSet(opendnp3::DoubleBitBinaryQuality::REMOTE_FORCED));
    m_checkBoxQuality4->SetLabel(opendnp3::DoubleBitBinaryQualitySpec::to_string(opendnp3::DoubleBitBinaryQuality::LOCAL_FORCED));
    m_checkBoxQuality4->SetValue(f.IsSet(opendnp3::DoubleBitBinaryQuality::LOCAL_FORCED));
    m_checkBoxQuality5->SetLabel(opendnp3::DoubleBitBinaryQualitySpec::to_string(opendnp3::DoubleBitBinaryQuality::CHATTER_FILTER));
    m_checkBoxQuality5->SetValue(f.IsSet(opendnp3::DoubleBitBinaryQuality::CHATTER_FILTER));
    m_checkBoxQuality6->SetLabel("---");
    m_checkBoxQuality6->Disable();
    m_checkBoxQuality7->SetLabel("---");
    m_checkBoxQuality7->Disable();
}

void MDBinaryDialog::write()
{
    wxString val, qual;
    val = combo->GetValue();
    qual = (m_checkBoxQuality5->IsChecked() ? opendnp3::DoubleBitBinaryQualitySpec::to_string(opendnp3::DoubleBitBinaryQuality::CHATTER_FILTER) + wxString(" ") : "");
    qual += (m_checkBoxQuality4->IsChecked() ? opendnp3::DoubleBitBinaryQualitySpec::to_string(opendnp3::DoubleBitBinaryQuality::LOCAL_FORCED) + wxString(" ") : "");
    qual += (m_checkBoxQuality3->IsChecked() ? opendnp3::DoubleBitBinaryQualitySpec::to_string(opendnp3::DoubleBitBinaryQuality::REMOTE_FORCED) + wxString(" ") : "");
    qual += (m_checkBoxQuality2->IsChecked() ? opendnp3::DoubleBitBinaryQualitySpec::to_string(opendnp3::DoubleBitBinaryQuality::COMM_LOST) + wxString(" ") : "");
    qual += (m_checkBoxQuality1->IsChecked() ? opendnp3::DoubleBitBinaryQualitySpec::to_string(opendnp3::DoubleBitBinaryQuality::RESTART) + wxString(" ") : "");
    qual += (m_checkBoxQuality0->IsChecked() ? opendnp3::DoubleBitBinaryQualitySpec::to_string(opendnp3::DoubleBitBinaryQuality::ONLINE) : "");
    on_change(val, qual);
}

MAnalogDialog::MAnalogDialog(wxWindow* parent, const wxString& old_val, const wxString& old_qual, OnChange fun) : MStateDialog(parent, fun)
{
    text = new wxTextCtrl(m_panelStateDialog, wxID_ANY, old_val, wxDefaultPosition, wxDefaultSize);
    bSizerValue->Add(text, 0, wxALL, 5);
    Fit();
    read(old_val, old_qual);
}

void MAnalogDialog::read(const wxString &old_val, const wxString &old_qual)
{
    opendnp3::Flags f(quality_to_uint8<opendnp3::AnalogQualitySpec>(old_qual));
    m_checkBoxQuality0->SetLabel(opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::ONLINE));
    m_checkBoxQuality0->SetValue(f.IsSet(opendnp3::AnalogQuality::ONLINE));
    m_checkBoxQuality1->SetLabel(opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::RESTART));
    m_checkBoxQuality1->SetValue(f.IsSet(opendnp3::AnalogQuality::RESTART));
    m_checkBoxQuality2->SetLabel(opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::COMM_LOST));
    m_checkBoxQuality2->SetValue(f.IsSet(opendnp3::AnalogQuality::COMM_LOST));
    m_checkBoxQuality3->SetLabel(opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::REMOTE_FORCED));
    m_checkBoxQuality3->SetValue(f.IsSet(opendnp3::AnalogQuality::REMOTE_FORCED));
    m_checkBoxQuality4->SetLabel(opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::LOCAL_FORCED));
    m_checkBoxQuality4->SetValue(f.IsSet(opendnp3::AnalogQuality::LOCAL_FORCED));
    m_checkBoxQuality5->SetLabel(opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::OVERRANGE));
    m_checkBoxQuality5->SetValue(f.IsSet(opendnp3::AnalogQuality::OVERRANGE));
    m_checkBoxQuality6->SetLabel(opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::REFERENCE_ERR));
    m_checkBoxQuality6->SetValue(f.IsSet(opendnp3::AnalogQuality::REFERENCE_ERR));
    m_checkBoxQuality7->SetLabel(opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::RESERVED));
    m_checkBoxQuality7->SetValue(f.IsSet(opendnp3::AnalogQuality::RESERVED));
}

void MAnalogDialog::write()
{
    wxString val, qual;
    val = text->GetValue();
    val.Replace(',', '.');
    qual = (m_checkBoxQuality7->IsChecked() ? opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::RESERVED) + wxString(" ") : "");
    qual += (m_checkBoxQuality6->IsChecked() ? opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::REFERENCE_ERR) + wxString(" ") : "");
    qual += (m_checkBoxQuality5->IsChecked() ? opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::OVERRANGE) + wxString(" ") : "");
    qual += (m_checkBoxQuality4->IsChecked() ? opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::LOCAL_FORCED) + wxString(" ") : "");
    qual += (m_checkBoxQuality3->IsChecked() ? opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::REMOTE_FORCED) + wxString(" ") : "");
    qual += (m_checkBoxQuality2->IsChecked() ? opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::COMM_LOST) + wxString(" ") : "");
    qual += (m_checkBoxQuality1->IsChecked() ? opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::RESTART) + wxString(" ") : "");
    qual += (m_checkBoxQuality0->IsChecked() ? opendnp3::AnalogQualitySpec::to_string(opendnp3::AnalogQuality::ONLINE) : "");
    on_change(val, qual);
}

MCounterDialog::MCounterDialog(wxWindow* parent, const wxString& old_val, const wxString& old_qual, OnChange fun) : MStateDialog(parent, fun)
{
    text = new wxTextCtrl(m_panelStateDialog, wxID_ANY, old_val, wxDefaultPosition, wxDefaultSize);
    bSizerValue->Add(text, 0, wxALL, 5);

    Fit();
    read(old_val, old_qual);
}

void MCounterDialog::read(const wxString &old_val, const wxString &old_qual)
{
    opendnp3::Flags f(quality_to_uint8<opendnp3::DoubleBitBinaryQualitySpec>(old_qual));
    m_checkBoxQuality0->SetLabel(opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::ONLINE));
    m_checkBoxQuality0->SetValue(f.IsSet(opendnp3::CounterQuality::ONLINE));
    m_checkBoxQuality1->SetLabel(opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::RESTART));
    m_checkBoxQuality1->SetValue(f.IsSet(opendnp3::CounterQuality::RESTART));
    m_checkBoxQuality2->SetLabel(opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::COMM_LOST));
    m_checkBoxQuality2->SetValue(f.IsSet(opendnp3::CounterQuality::COMM_LOST));
    m_checkBoxQuality3->SetLabel(opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::REMOTE_FORCED));
    m_checkBoxQuality3->SetValue(f.IsSet(opendnp3::CounterQuality::REMOTE_FORCED));
    m_checkBoxQuality4->SetLabel(opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::LOCAL_FORCED));
    m_checkBoxQuality4->SetValue(f.IsSet(opendnp3::CounterQuality::LOCAL_FORCED));
    m_checkBoxQuality5->SetLabel(opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::ROLLOVER));
    m_checkBoxQuality5->SetValue(f.IsSet(opendnp3::CounterQuality::ROLLOVER));
    m_checkBoxQuality6->SetLabel(opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::DISCONTINUITY));
    m_checkBoxQuality6->SetValue(f.IsSet(opendnp3::CounterQuality::DISCONTINUITY));
    m_checkBoxQuality7->SetLabel(opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::RESERVED));
    m_checkBoxQuality7->SetValue(f.IsSet(opendnp3::CounterQuality::RESERVED));
}

void MCounterDialog::write()
{
    wxString val, qual;
    val = text->GetValue();
    qual = (m_checkBoxQuality7->IsChecked() ? opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::RESERVED) + wxString(" ") : "");
    qual += (m_checkBoxQuality6->IsChecked() ? opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::DISCONTINUITY) + wxString(" ") : "");
    qual += (m_checkBoxQuality5->IsChecked() ? opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::ROLLOVER) + wxString(" ") : "");
    qual += (m_checkBoxQuality4->IsChecked() ? opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::LOCAL_FORCED) + wxString(" ") : "");
    qual += (m_checkBoxQuality3->IsChecked() ? opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::REMOTE_FORCED) + wxString(" ") : "");
    qual += (m_checkBoxQuality2->IsChecked() ? opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::COMM_LOST) + wxString(" ") : "");
    qual += (m_checkBoxQuality1->IsChecked() ? opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::RESTART) + wxString(" ") : "");
    qual += (m_checkBoxQuality0->IsChecked() ? opendnp3::CounterQualitySpec::to_string(opendnp3::CounterQuality::ONLINE) : "");
    on_change(val, qual);
}
