# UGreen_IR_Remote_Arduino
Arduino Uno project, use IR transmitter to simulate UGreen 50745(HDMI 4x1 switcher) remoter.

## Description
UGreen 50745 is a 4in 1out HDMI video processer. It could not only switch different input but also have 3 different multi-view mode to combine input sources.
This project is also a test, and will be a part of my SmartHomeTools.

Reference
According the analyse with [Arduino-IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote)

The Remoter commands as list below

Buttons: 
|Button|Protocol|Address|Command|Raw-Data|remark|Control URL|
|--|--|--|--|--|--|--|
|Power|NEC|0x0|0x45|0xBA45FF00|32 bits LSB first|http://IPaddress/run/13/|
|ScreenShow|NEC|0x0|0x47|0xB847FF00|32 bits LSB first|http://IPaddress/run/0/|
|IN 1|NEC|0x0|0x44|0xBB44FF00|32 bits LSB first|http://IPaddress/run/2/|
|IN 2|NEC|0x0|0x40|0xBB40FF00|32 bits LSB first|http://IPaddress/run/3/|
|IN 3|NEC|0x0|0x07|0xF807FF00|32 bits LSB first|http://IPaddress/run/4/|
|IN 4|NEC|0x0|0x15|0xEA15FF00|32 bits LSB first|http://IPaddress/run/5/|
|CH - |NEC|0x0|0x43|0xBC43FF00|32 bits LSB first|http://IPaddress/run/6/|
|CH + |NEC|0x0|0x09|0xF609FF00|32 bits LSB first|http://IPaddress/run/7/|
|2 in 1|NEC|0x0|0xC|0xF30CFF00|32 bits LSB first|http://IPaddress/run/8/|
|4 in 1|NEC|0x0|0x18|0xE718FF00|32 bits LSB first|http://IPaddress/run/9/|
|1+3|NEC|0x0|0x08|0xF708FF00|32 bits LSB first|http://IPaddress/run/10/|
|Fullscreen|NEC|0x0|0x1C|0xE31CFF00|32 bits LSB first|http://IPaddress/run/11/|
|Audio|NEC|0x0|0x5E|0xA15EFF00|32 bits LSB first|http://IPaddress/run/12/|
|720/1080|NEC|0x0|0x5A|0xA55AFF00|32 bits LSB first|http://IPaddress/run/1/|
