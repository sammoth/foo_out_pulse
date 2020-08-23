# foo_out_pulse
PulseAudio output for foobar2000 using the native TCP protocol, for use in Wine.

## Advantages
Foobar works very well in Wine, but Wine's default Pulseaudio output has some disadvantages:
- While the Wine application is performing IO-heavy tasks, such as writing tags in foobar, the
buffer seems to be liable to underrun, causing audio dropouts,
- Existing output components will automatically resample audio to the reported output sample
rate of the playback device. Pulseaudio supports changing the device sample rate to match the
currently playing client even when running in shared mode using the `avoid-resampling` option,
so this isn't optimal
- foobar will have a generic device icon in the system mixer


## Setup
At the moment this component tries to connect to 127.0.0.1 using Pulse's native TCP protocol.
First you have to enable the module for this protocol for the Pulse daemon by editing either
`/etc/pulse/default.pa` or `~/.config/pulse/default.pa` and adding or editing the following line:

`load-module module-native-protocol-tcp auth-ip-acl=127.0.0.1`

Understand the security implications of this before making this change.

For the icon to appear in the mixer, you will need to place a png of foobar's icon in, for example, `~/.icons/hicolor/256x256/apps/`



<img src="screenshot.png" width="660">
