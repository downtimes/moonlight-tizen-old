# Moonlight for Samsung Tizen TVs older than 2020

This is an experimental branch in which I try to make moonlight run on old Samsung TVs (Tizen < 5.5).
If you have a newer Samsung TV please use [Moonlight-Chrome-Tizen](https://github.com/KyroFrCode/moonlight-chrome-tizen) instead.

The code has [moonlight-stream/moonlight-chrome](https://github.com/moonlight-stream/moonlight-chrome) 
and [SamsungDForum/moonlight-chrome](https://github.com/SamsungDForum/moonlight-chrome) as basis for the development. 
It is essentially a combination of the two codebase with some minor glue code to make it work.

The codebase could use some proper refactoring. Since I can't get the TV simulator to run properly with with a Tizen
version that is low enough, and NaCl debugging requires a [Samsung TV developer model](https://developer.samsung.com/smarttv/develop/extension-libraries/nacl/managing-nacl-projects/debugging-nacl-projects.html)
my capabilities are sadly a little limited.
Especially the problem of the decoder with higher resolutions is pretty hard to debug with just printf.
Chrome sadly also dropped support for NaCl completely and even wiped out the documentation.

# Status
* Not production ready
* Basic connection works
    - max 1080p, the decoder dies with higher resolutions
* Remote control is janky
    - pairing with hosts
    - etc...
* Debug code still present
* Haven't tried to connect a Gamepad to TV yet

# Build
The project is not yet ready to be tested.