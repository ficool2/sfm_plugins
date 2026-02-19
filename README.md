# SFM Plugins

Source code for various SFM plugins I made:

* [Shader Loader](https://steamcommunity.com/workshop/filedetails/?id=3669466136)
* [Unrestricted Uploader](https://steamcommunity.com/sharedfiles/filedetails/?id=3669477571)
* [Blendmodulate Light Fix](https://steamcommunity.com/sharedfiles/filedetails/?id=3669252571)

## Building

Visual Studio 2022 or newer is required with MSVC build tools downloaded.

Open the `sfm_plugins.sln` and build. 

I recommend changing the Output directories to your SFM's `addons` folder in `usermod`.

## Info

SFM, like most other Source games, has support for loading [server plugins](https://developer.valvesoftware.com/wiki/Server_plugins)

It turn out that after patching where the engine searches these, it's possible to load them from the workshop. See [Plugin Loader](https://steamcommunity.com/workshop/filedetails/?id=3669237174) script.

This allows for more sophisticated patches to be made on SFM than would be possible with Python alone.