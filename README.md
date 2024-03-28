# Moonlight for Samsung Tizen TVs older than 2020

This is an experimental branch in which I try to make moonlight run on old Samsung TVs (Tizen < 5.5).
If you have a newer Samsung TV please use [Moonlight-Chrome-Tizen](https://github.com/KyroFrCode/moonlight-chrome-tizen) instead.

The code has [moonlight-stream/moonlight-chrome](https://github.com/moonlight-stream/moonlight-chrome) 
and [SamsungDForum/moonlight-chrome](https://github.com/SamsungDForum/moonlight-chrome) as basis for the development. 
It is essentially a combination of the two codebase with some minor glue code to make it work.

Since I can't get the TV simulator to run properly with a Tizen
version that is low enough, and NaCl debugging requires a [Samsung TV developer model](https://developer.samsung.com/smarttv/develop/extension-libraries/nacl/managing-nacl-projects/debugging-nacl-projects.html),
my capabilities are sadly a little limited to investigate problems with NaCl code.

I have a persistent problem with streams in a too high resolution (bitrate is irrelevant). The decoder stage of the NaCl module can't keep up and crashes completely. Without better tooling to investigate the issue, I've given up and settled on running 1080p on my TV. That's the highest resolution which still works.

# Status
* Basic streaming of 1080p video + auido works okay.
* Streams with higher resolution crash on my TV and I can't really debug the problem
* Haven't tried to connect a Gamepad to TV, no idea about the existing support
* The UI is too small on big TVs
* Most of the Moonlight functionality except for removing hosts should work decently
* Only run on a Tizen 4.0 TV. I have no Idea if other Tizen versions work. I've put 2.3 as minimum in the Manifest.

# Build & Install
The build is neatly packaged in a docker container. The container build takes pretty long! (toolchains unpacking + installation)
> docker build -t Moonlight -f Dockerfile

Enable developer mode on the TV (more information on official [Samsung guide](https://developer.samsung.com/smarttv/develop/getting-started/using-sdk/tv-device.html)):

* Go to Apps.
* Press 12345 on the remote; a dialog should pop up.
* Set Developer mode to On; fill in the IP of the Docker host pc.
* Power off and power on the TV as instructed; go once again to Apps.
* Depending on your model, a "DEVELOP MODE" or similar message might appear.

Then you can run the docker image with
> docker run -it --rm Moonlight

Connect to your tv via Smart Development Bridge
> sdb connect YOUR_TV_IP

Confirm you successfully connected
> sdb devices

Install the package (DEVICE_ID is from previous command)
> tizen install -n MoonlightTizenOld.wgt -t DEVICE_ID

The app should now be installed on your TV
