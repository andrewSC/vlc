/*****************************************************************************
 * InterfaceWindow.h: BeOS interface window class prototype
 *****************************************************************************
 * Copyright (C) 1999, 2000, 2001 VideoLAN
 * $Id: InterfaceWindow.h,v 1.7 2003/01/08 02:09:15 titer Exp $
 *
 * Authors: Jean-Marc Dressler <polux@via.ecp.fr>
 *          Tony Castley <tcastley@mail.powerup.com.au>
 *          Richard Shepherd <richard@rshepherd.demon.co.uk>
 *          Stephan Aßmus <stippi@yellowbites.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA.
 *****************************************************************************/

#ifndef BEOS_INTERFACE_WINDOW_H
#define BEOS_INTERFACE_WINDOW_H

#include <Menu.h>
#include <Window.h>

class BMenuBar;
class MediaControlView;
class PlayListWindow;
class BFilePanel;
class PreferencesWindow;

class CDMenu : public BMenu
{
 public:
							CDMenu( const char* name );
	virtual					~CDMenu();

	virtual	void			AttachedToWindow();

 private:
	int						GetCD( const char* directory );
};

class LanguageMenu : public BMenu
{
 public:
							LanguageMenu( const char* name,
										  int menu_kind,
										  VlcWrapper *p_wrapper );
	virtual					~LanguageMenu();

	virtual	void			AttachedToWindow();

 private:
			void			_GetChannels();

	VlcWrapper *            p_wrapper;
	int						kind;
};

class TitleMenu : public BMenu
{
 public:
							TitleMenu( const char* name, intf_thread_t  *p_interface );
	virtual					~TitleMenu();

	virtual	void			AttachedToWindow();
	
	intf_thread_t  *p_intf;
};

class ChapterMenu : public BMenu
{
 public:
							ChapterMenu( const char* name, intf_thread_t  *p_interface );
	virtual					~ChapterMenu();

	virtual	void			AttachedToWindow();

	intf_thread_t  *p_intf;
};


class InterfaceWindow : public BWindow
{
 public:
							InterfaceWindow( BRect frame,
											 const char* name,
											 intf_thread_t* p_interface );
	virtual					~InterfaceWindow();

							// BWindow
	virtual	void			FrameResized( float width, float height );
	virtual	void			MessageReceived( BMessage* message );
	virtual	bool			QuitRequested();

							// InterfaceWindow
			void 			updateInterface();
			bool			IsStopped() const;
	    
	MediaControlView*		p_mediaControl;

 private:	
			void			_UpdatePlaylist();
			void			_SetMenusEnabled( bool hasFile,
											  bool hasChapters = false,
											  bool hasTitles = false );
			void			_UpdateSpeedMenu( int rate );
			void			_InputStreamChanged();
			status_t		_LoadSettings( BMessage* message,
										   const char* fileName,
										   const char* subFolder = NULL );
			status_t		_SaveSettings( BMessage* message,
										   const char* fileName,
										   const char* subFolder = NULL );
			void			_RestoreSettings();
			void			_StoreSettings();

	intf_thread_t*			p_intf;
	es_descriptor_t*		p_spu_es;

	bool					fPlaylistIsEmpty;
	BFilePanel*				fFilePanel;
	PlayListWindow*			fPlaylistWindow;
	PreferencesWindow*		fPreferencesWindow;
	BMenuBar*				fMenuBar;
	BMenuItem*				fNextTitleMI;
	BMenuItem*				fPrevTitleMI;
	BMenuItem*				fNextChapterMI;
	BMenuItem*				fPrevChapterMI;
	BMenuItem*				fOnTopMI;
	BMenuItem*				fSlowerMI;
	BMenuItem*				fNormalMI;
	BMenuItem*				fFasterMI;
	BMenuItem*				fPreferencesMI;
	BMenu*					fAudioMenu;
	BMenu*					fNavigationMenu;
	BMenu*					fTitleMenu;
	BMenu*					fChapterMenu;
	BMenu*					fLanguageMenu;
	BMenu*					fSubtitlesMenu;
	BMenu*					fSpeedMenu;
	BMenu*					fSettingsMenu;
	bigtime_t				fLastUpdateTime;
	BMessage*				fSettings;	// we keep the message arround
										// for forward compatibility
	
	VlcWrapper * p_wrapper;
};

#endif	// BEOS_INTERFACE_WINDOW_H
