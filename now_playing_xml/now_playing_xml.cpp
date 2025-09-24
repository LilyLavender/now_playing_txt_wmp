/////////////////////////////////////////////////////////////////////////////
//
// now_playing_xml.cpp : Implementation of CNow_playing_xml
// Copyright (c) Microsoft Corporation. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "now_playing_xml.h"
#include "CPropertyDialog.h"

#include <iostream>
#include <fstream>
#include <comutil.h>
#include <msxml.h>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CNow_playing_xml::CNow_playing_xml
// Constructor

CNow_playing_xml::CNow_playing_xml()
{
    wcsncpy_s(m_wszPluginText, sizeof(m_wszPluginText) / sizeof(m_wszPluginText[0]), L"D:\\now_playing_track.xml", sizeof(m_wszPluginText) / sizeof(m_wszPluginText[0]));
    m_dwAdviseCookie = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CNow_playing_xml::~CNow_playing_xml
// Destructor

CNow_playing_xml::~CNow_playing_xml()
{
}

/////////////////////////////////////////////////////////////////////////////
// CNow_playing_xml:::FinalConstruct
// Called when an plugin is first loaded. Use this function to do one-time
// intializations that could fail instead of doing this in the constructor,
// which cannot return an error.

HRESULT CNow_playing_xml::FinalConstruct()
{
	CreateXMLFile(m_wszPluginText);
    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CNow_playing_xml:::FinalRelease
// Called when a plugin is unloaded. Use this function to free any
// resources allocated in FinalConstruct.

void CNow_playing_xml::FinalRelease()
{
    ReleaseCore();
}

/////////////////////////////////////////////////////////////////////////////
// CNow_playing_xml::SetCore
// Set WMP core interface

HRESULT CNow_playing_xml::SetCore(IWMPCore *pCore)
{
    HRESULT hr = S_OK;

    // release any existing WMP core interfaces
    ReleaseCore();

    // If we get passed a NULL core, this  means
    // that the plugin is being shutdown.

    if (pCore == NULL)
    {
        return S_OK;
    }

    m_spCore = pCore;

    // connect up the event interface
    CComPtr<IConnectionPointContainer>  spConnectionContainer;

    hr = m_spCore->QueryInterface( &spConnectionContainer );

    if (SUCCEEDED(hr))
    {
        hr = spConnectionContainer->FindConnectionPoint( __uuidof(IWMPEvents), &m_spConnectionPoint );
    }

    if (SUCCEEDED(hr))
    {
        hr = m_spConnectionPoint->Advise( GetUnknown(), &m_dwAdviseCookie );

        if ((FAILED(hr)) || (0 == m_dwAdviseCookie))
        {
            m_spConnectionPoint = NULL;
        }
    }

    return hr;
}

/////////////////////////////////////////////////////////////////////////////
// CNow_playing_xml::ReleaseCore
// Release WMP core interfaces

void CNow_playing_xml::ReleaseCore()
{
    if (m_spConnectionPoint)
    {
        if (0 != m_dwAdviseCookie)
        {
            m_spConnectionPoint->Unadvise(m_dwAdviseCookie);
            m_dwAdviseCookie = 0;
        }
        m_spConnectionPoint = NULL;
    }

    if (m_spCore)
    {
        m_spCore = NULL;
    }
}


/////////////////////////////////////////////////////////////////////////////
// CNow_playing_xml::DisplayPropertyPage
// Display property page for plugin

HRESULT CNow_playing_xml::DisplayPropertyPage(HWND hwndParent)
{
    CPropertyDialog dialog(this);

    dialog.DoModal(hwndParent);

    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CNow_playing_xml::GetProperty
// Get plugin property

HRESULT CNow_playing_xml::GetProperty(const WCHAR *pwszName, VARIANT *pvarProperty)
{
    if (NULL == pvarProperty)
    {
        return E_POINTER;
    }

    return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// CNow_playing_xml::SetProperty
// Set plugin property

HRESULT CNow_playing_xml::SetProperty(const WCHAR *pwszName, const VARIANT *pvarProperty)
{
    return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// CNow_playing_xml::CreateXML
// Create the XML file when the plugin starts up.
// TODO: Need to find a way to store the path and remember it

HRESULT CNow_playing_xml::CreateXMLFile(const WCHAR *pwszFilePath)
{
    ofstream ofsTrackDataXML(pwszFilePath, ios::out | ios::binary);
    ofsTrackDataXML << "";
    ofsTrackDataXML.close();
    return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CNow_playing_xml::CreateXML
// Update the XML on various player events.

void CNow_playing_xml::UpdateXMLFile(const WCHAR *pwszFilePath, const long NewState)
{
    ofstream ofsTrackDataXML(pwszFilePath, ios::out | ios::binary);

    // If not playing, blank file
    if (NewState != wmppsPlaying)
    {
        ofsTrackDataXML << "";
        ofsTrackDataXML.close();
        return;
    }

    if (m_spCore == NULL)
    {
        ofsTrackDataXML << "";
        ofsTrackDataXML.close();
        return;
    }

    CComPtr<IWMPMedia> pCurrentMedia;
    if (FAILED(m_spCore->get_currentMedia(&pCurrentMedia)) || !pCurrentMedia)
    {
        ofsTrackDataXML << "";
        ofsTrackDataXML.close();
        return;
    }

    BSTR bstrValue;
    string artistStr;
    string titleStr;

    // Artist
    if (SUCCEEDED(pCurrentMedia->getItemInfo(L"Artist", &bstrValue)) && bstrValue)
    {
        COLE2T pStrArtist(bstrValue);
        CW2A pszArtist(pStrArtist);
        artistStr = pszArtist;
        ::SysFreeString(bstrValue);
    }

    // Title
    if (SUCCEEDED(pCurrentMedia->getItemInfo(L"Title", &bstrValue)) && bstrValue)
    {
        COLE2T pStrTrack(bstrValue);
        CW2A pszTrack(pStrTrack);
        titleStr = pszTrack;
        ::SysFreeString(bstrValue);
    }

    // Write in "{artist} - {title}" format
    if (!artistStr.empty() || !titleStr.empty())
    {
        ofsTrackDataXML << artistStr << " - " << titleStr;
    }

    ofsTrackDataXML.close();
}
