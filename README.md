# Moonlight for Samsung Tizen TVs older than 2020

This is an experimental branch in which I try to make moonlight run on old Samsung TVs (Tizen < 5.5).
If you have a newer Samsung TV please use [Moonlight-Chrome-Tizen](https://github.com/KyroFrCode/moonlight-chrome-tizen) instead.

The code has [moonlight-stream/moonlight-chrome](https://github.com/moonlight-stream/moonlight-chrome) and [SamsungDForum/moonlight-chrome](https://github.com/SamsungDForum/moonlight-chrome) as basis for the development. It is essentially a combination of the two codebases with some minor glue changes to make it work.

# Status
* Not production ready
* Basic connection works
    - only low bitrates. Need to investigate
* Remote control is janky
    - connecting to hosts
    - closing streams
    - feedback when selecting elements
    - etc...
* Debug code still present
* No idea about GameController support at TV

# Build
The project is not yet ready to be build for testing.