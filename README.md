# Now Playing (TXT)
A very minimal "Now Playing" TXT generating plugin for Windows Media Player.

## Forked from...
Forked from [fraggerfox's now_playing_xml](https://github.com/fraggerfox/now_playing_xml). This project edits the original xml format:
```xml
<?xml version="1.0" encoding="UTF-8"?>
<now_playing_track>
  <title>Some Title</title>
  <artist>Some Artist</artist>
  <album>Some Album</album>
  <duration>Track Length</duration>
  <player_state>playing</player_state>
</now_playing_track>
```
Into a very minimal txt, for use in OBS:
```
Artist - Song Title 
```
Everything from here on through the References section is unedited from the original repo. Some notes about my findings on the project will be at the very end.

### Introduction

The motivation for writing this plugin was quite simple, a very simple
python script[1] for updating the current music track that you are
listening to in your media player to an IRC channel was developed by a
Rajiv. Originally the script was written for Linux for Amarok based
back-end and later on extended for a mpd based back-end, but since I
hang around Windows machines a lot I thought of extending the original
script to work with Windows Media Player (WMP).

In order for the python script to read the data from WMP it needed to
retrieve data on the fly from it and since I did not find a direct way
to do it, I looked around for a plugin that could generate the current
track data in some sort of XML format from WMP and the nearest
solution was a paid plugin[2] for WMP. I decided to write a simple WMP
plugin using the tools available for free within the Windows 7
Development framework that would get the job done without any
restrictions imposed on me by this paid plugin.

A special thanks to the Last.fm scrobbling application[3] hosted in
github, that helped me understand and implement the WMP SDK from the
Windows 7 SDK framework.

### How to compile 

Before doing a proper compile make sure you have the following items
installed and ready to go in your system.

* Microsoft Visual C++ 2010 Express Edition (or higher)
* Microsoft Visual Studio Express Edition SP1
* Windows 7 Software Development Kit
* Windows 7 Driver Development Kit

The total installed size of all the components comes to roughly 2.0G+
in size.

Clone the repository open up the solution and compile.

- NOTE: You have to change the path to the ``` atl71 ``` and ```
  vc\include ``` directory into your include and library paths to meet
  your path where you have installed.

- NOTE: You may have to include the ``` atlthunk.lib ``` manually into
  the Linker -> Input area of your VC++ project properties.


In order to make the plugin active execute the following command on
the dll after compilation is done

``` regsvr32 /s "C:\Program Files (x86)\Windows Media Player\Plugins\now_playing_xml.dll" ```

### How it works

Currently it creates a file in ``` D:\ ``` Drive (because I hard-coded it), that
contains the following items in an XML format.

### TODO

1. Make the path of the output file more configurable.
2. Provide a better XML parsing library.

### References

* [1] - https://github.com/fraggerfox/music_bot
* [2] - http://brandon.fuller.name/archives/2004/09/14/11.05.20/
* [3] - https://github.com/lastfm/lastfm-desktop/blob/master/plugins/wmp

### Lily's notes
I'm not 100% sure if this was the best use of my day, but my thought process of this needing to exist is this:
- There's no easy way to get a song overlay in OBS when using Windows Media Player Legacy
  - [Tuna](https://github.com/univrsal/tuna) exists, but doesn't have compatibility for WMP. Since WMP doesn't change the window title like other programs do, we can't even use Tuna's "window title" mode.
  - A Python or C# script that gets data from WMP won't work. win32com is really our only hope, but we can't gain control of the current instance of WMP to get information from it. If we try to create a new instance we *can* control with win32com, it'll be a COM instance that can't be interacted with and only useful for getting information on arbitrary audio files.
  - A .dll built with C# won't work. From my research, a plug-in class needs to inherit from IWMPPluginUI, and I don't have access to that class in Windows 11 and even if I did, making the dll COM-visible didn't work, so WMP ignored it.
  - Windows' SMTC allows us to get the data from the currently playing media (ie a YouTube video in Chrome). However, WMP data doesn't appear in SMTC.
- This project already exists, even if it's rather old. Updating it was a bit of a pain and I did lose the ability for the properties window in WMP to appear in the center of the screen because my version of atlwin.h gave errors.
- I could've just built the original project and then made an additional Python script to get the data from the XML and put it into another txt for OBS to use, but I didn't like the idea of having to run an extra script while streaming if I don't have to.
- As it was a bit of a hassle to install C++ devtools with Visual Studio and edit the program to work well on Windows 11, the releases tab has not only the txt version built with the current code in this repo, but also as close as I can get to the original XML version.
- fraggerfox is still active today, but I doubt this project is still being updated. If anyone comes across this and has any questions, either contact them or me at Discord @LilyLambda or lilylambda136@gmail.com