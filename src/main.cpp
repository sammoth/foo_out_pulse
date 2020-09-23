#include "stdafx.h"
// PCH ^

const char* about = "Copyright (c) sammoth, 2020\n"
"\n"
"This component uses PulseAudio, licensed under the LGPL v2.1, see:\n"
"https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html\n"
"\n"
"Source code is provided at:\n"
"https://github.com/sammoth/foo_out_pulse/releases";

DECLARE_COMPONENT_VERSION("Pulseaudio Output", "0.6.1-beta",
                          about);
VALIDATE_COMPONENT_FILENAME("foo_out_pulse.dll");
