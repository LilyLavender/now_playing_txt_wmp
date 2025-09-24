/////////////////////////////////////////////////////////////////////////////
//
// now_playing_xmlEvents.cpp : Implementation of CNow_playing_xml events
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "now_playing_xml.h"

void CNow_playing_xml::OpenStateChange( long NewState )
{
    switch (NewState)
    {
    case wmposUndefined:
        break;
    case wmposPlaylistChanging:
        break;
    case wmposPlaylistLocating:
        break;
    case wmposPlaylistConnecting:
        break;
    case wmposPlaylistLoading:
        break;
    case wmposPlaylistOpening:
        break;
    case wmposPlaylistOpenNoMedia:
        break;
    case wmposPlaylistChanged:
        break;
    case wmposMediaChanging:
        break;
    case wmposMediaLocating:
        break;
    case wmposMediaConnecting:
        break;
    case wmposMediaLoading:
        break;
    case wmposMediaOpening:
        break;
    case wmposMediaOpen:
        break;
    case wmposBeginCodecAcquisition:
        break;
    case wmposEndCodecAcquisition:
        break;
    case wmposBeginLicenseAcquisition:
        break;
    case wmposEndLicenseAcquisition:
        break;
    case wmposBeginIndividualization:
        break;
    case wmposEndIndividualization:
        break;
    case wmposMediaWaiting:
        break;
    case wmposOpeningUnknownURL:
        break;
    default:
        break;
    }
}

void CNow_playing_xml::PlayStateChange( long NewState )
{
    switch (NewState)
    {
    case wmppsUndefined:
        break;
    case wmppsStopped:
		CNow_playing_xml::UpdateXMLFile(CNow_playing_xml::m_wszPluginText, NewState);
        break;
    case wmppsPaused:
		CNow_playing_xml::UpdateXMLFile(CNow_playing_xml::m_wszPluginText, NewState);
        break;
    case wmppsPlaying:
		CNow_playing_xml::UpdateXMLFile(CNow_playing_xml::m_wszPluginText, NewState);
        break;
    case wmppsScanForward:
        break;
    case wmppsScanReverse:
        break;
    case wmppsBuffering:
        break;
    case wmppsWaiting:
        break;
    case wmppsMediaEnded:
        CNow_playing_xml::UpdateXMLFile(CNow_playing_xml::m_wszPluginText, NewState);
        break;
    case wmppsTransitioning:
        break;
    case wmppsReady:
        break;
    case wmppsReconnecting:
        break;
    case wmppsLast:
        break;
    default:
        break;
    }
}

void CNow_playing_xml::AudioLanguageChange( long LangID )
{
}

void CNow_playing_xml::StatusChange()
{
}

void CNow_playing_xml::ScriptCommand( BSTR scType, BSTR Param )
{
}

void CNow_playing_xml::NewStream()
{
}

void CNow_playing_xml::Disconnect( long Result )
{
}

void CNow_playing_xml::Buffering( VARIANT_BOOL Start )
{
}

void CNow_playing_xml::Error()
{
    CComPtr<IWMPError>      spError;
    CComPtr<IWMPErrorItem>  spErrorItem;
    HRESULT                 dwError = S_OK;
    HRESULT                 hr = S_OK;

    if (m_spCore)
    {
        hr = m_spCore->get_error(&spError);

        if (SUCCEEDED(hr))
        {
            hr = spError->get_item(0, &spErrorItem);
        }

        if (SUCCEEDED(hr))
        {
            hr = spErrorItem->get_errorCode( (long *) &dwError );
        }
    }
}

void CNow_playing_xml::Warning( long WarningType, long Param, BSTR Description )
{
}

void CNow_playing_xml::EndOfStream( long Result )
{
}

void CNow_playing_xml::PositionChange( double oldPosition, double newPosition)
{
}

void CNow_playing_xml::MarkerHit( long MarkerNum )
{
}

void CNow_playing_xml::DurationUnitChange( long NewDurationUnit )
{
}

void CNow_playing_xml::CdromMediaChange( long CdromNum )
{
}

void CNow_playing_xml::PlaylistChange( IDispatch * Playlist, WMPPlaylistChangeEventType change )
{
    switch (change)
    {
    case wmplcUnknown:
        break;
    case wmplcClear:
        break;
    case wmplcInfoChange:
        break;
    case wmplcMove:
        break;
    case wmplcDelete:
        break;
    case wmplcInsert:
        break;
    case wmplcAppend:
        break;
    case wmplcPrivate:
        break;
    case wmplcNameChange:
        break;
    case wmplcMorph:
        break;
    case wmplcSort:
        break;
    case wmplcLast:
        break;
    default:
        break;
    }
}

void CNow_playing_xml::CurrentPlaylistChange( WMPPlaylistChangeEventType change )
{
    switch (change)
    {
    case wmplcUnknown:
        break;
    case wmplcClear:
        break;
    case wmplcInfoChange:
        break;
    case wmplcMove:
        break;
    case wmplcDelete:
        break;
    case wmplcInsert:
        break;
    case wmplcAppend:
        break;
    case wmplcPrivate:
        break;
    case wmplcNameChange:
        break;
    case wmplcMorph:
        break;
    case wmplcSort:
        break;
    case wmplcLast:
        break;
    default:
        break;
    }
}

void CNow_playing_xml::CurrentPlaylistItemAvailable( BSTR bstrItemName )
{
}

void CNow_playing_xml::MediaChange( IDispatch * Item )
{
}

void CNow_playing_xml::CurrentMediaItemAvailable( BSTR bstrItemName )
{
}

void CNow_playing_xml::CurrentItemChange( IDispatch *pdispMedia)
{
}

void CNow_playing_xml::MediaCollectionChange()
{
}

void CNow_playing_xml::MediaCollectionAttributeStringAdded( BSTR bstrAttribName,  BSTR bstrAttribVal )
{
}

void CNow_playing_xml::MediaCollectionAttributeStringRemoved( BSTR bstrAttribName,  BSTR bstrAttribVal )
{
}

void CNow_playing_xml::MediaCollectionAttributeStringChanged( BSTR bstrAttribName, BSTR bstrOldAttribVal, BSTR bstrNewAttribVal)
{
}

void CNow_playing_xml::PlaylistCollectionChange()
{
}

void CNow_playing_xml::PlaylistCollectionPlaylistAdded( BSTR bstrPlaylistName)
{
}

void CNow_playing_xml::PlaylistCollectionPlaylistRemoved( BSTR bstrPlaylistName)
{
}

void CNow_playing_xml::PlaylistCollectionPlaylistSetAsDeleted( BSTR bstrPlaylistName, VARIANT_BOOL varfIsDeleted)
{
}

void CNow_playing_xml::ModeChange( BSTR ModeName, VARIANT_BOOL NewValue)
{
}

void CNow_playing_xml::MediaError( IDispatch * pMediaObject)
{
}

void CNow_playing_xml::OpenPlaylistSwitch( IDispatch *pItem )
{
}

void CNow_playing_xml::DomainChange( BSTR strDomain)
{
}

void CNow_playing_xml::SwitchedToPlayerApplication()
{
}

void CNow_playing_xml::SwitchedToControl()
{
}

void CNow_playing_xml::PlayerDockedStateChange()
{
}

void CNow_playing_xml::PlayerReconnect()
{
}

void CNow_playing_xml::Click( short nButton, short nShiftState, long fX, long fY )
{
}

void CNow_playing_xml::DoubleClick( short nButton, short nShiftState, long fX, long fY )
{
}

void CNow_playing_xml::KeyDown( short nKeyCode, short nShiftState )
{
}

void CNow_playing_xml::KeyPress( short nKeyAscii )
{
}

void CNow_playing_xml::KeyUp( short nKeyCode, short nShiftState )
{
}

void CNow_playing_xml::MouseDown( short nButton, short nShiftState, long fX, long fY )
{
}

void CNow_playing_xml::MouseMove( short nButton, short nShiftState, long fX, long fY )
{
}

void CNow_playing_xml::MouseUp( short nButton, short nShiftState, long fX, long fY )
{
}
