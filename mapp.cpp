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
#include <wx/msgdlg.h>
#include "mapp.hpp"
#include "mframes.hpp"

#ifdef __linux__
#include "resources/IDI_ICON1_xpm.xpm"
#endif

IMPLEMENT_APP(MApp)

bool MApp::OnInit()
{
    try
    {
        setlocale(LC_ALL,"");
        frame = new MFrame();
		frame->SetTitle(GetAppName());
        frame->SetIcon(wxICON(IDI_ICON1));
        SetTopWindow(frame);
        frame->Show();
        if(argc == 2)
            frame->LoadFromFile(argv[1]);
        return true;
    }
    catch(const std::exception& e)
    {
        wxMessageBox(wxString(e.what(), wxConvLocal), GetAppName());
        return false;
    }
	catch(...)
	{
        wxMessageBox("Unknow exception", GetAppName());
        return false;
	}
}

int MApp::OnExit()
{
	try
	{
		frame->Destroy();
	}
	catch(const std::exception& e)
	{
		wxMessageBox(wxString(e.what(), wxConvLocal), GetAppName());
	}
	catch(...)
	{
        wxMessageBox("Unknow exception", GetAppName());
	}
	return wxApp::OnExit();
}


