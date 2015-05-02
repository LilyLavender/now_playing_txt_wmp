# Now Playing (XML)

A very minimal "Now Playing" XML generating plugin for Windows Media Player.

### Introduction

The motivation for writing this plugin was quite simple, a very simple
python script[1] for updating the current music track that you are
listening to in your media player. Originally the script was written
for Linux, but since I hang around Windows machines a lot I thought of
extending the original script to work with Windows Media Player (WMP).

In order for the python script to read the data from WMP it needed to
retrieve data on the fly from it and since I did not find a direct way
to do it and the nearest solution was a paid plugin[2] for WMP. I
decided to write a simple WMP plugin using the tools available for
free within the Windows 7 Development framework.

### How to compile 

Before doing a proper compile make sure you have the following items
installed and ready to go in your system.

* Microsoft Visual C++ 2010 (or higher)
* Microsoft Visual Studio SP1
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

### References

[1] - https://github.com/fraggerfox/music_bot
[2] - http://brandon.fuller.name/archives/2004/09/14/11.05.20/