; This script was created using Pulover's Macro Creator
; www.macrocreator.com
;Author:CAS
;Version:1.1
#NoEnv
SetWorkingDir %A_ScriptDir%
CoordMode, Mouse, Window
SendMode Event
#SingleInstance Force
SetTitleMatchMode 2
#WinActivateForce
SetControlDelay -1
SetWinDelay 0
SetKeyDelay 1
SetMouseDelay -1
SetBatchLines -1

#include CaptureScreen.ahk
Menu, Tray, nostandard
Menu, Tray, add, SetImagePath, SetImagePath
Menu, Tray, add
Menu, Tray, add, Exit, Exit
global ImagePath := ".\ScreenShot\"
global LoopTimes :=5
global UdDely := 10
global ImageQuality :=10
global ScDely :=300
If !FileExist("config.ini"){
	IniWrite %ImagePath%,.\config.ini,Settings,ImagePath
	IniWrite %LoopTimes%,.\config.ini,Settings,LoopTimes
	IniWrite %UdDely%,.\config.ini,Settings,UdDely
	IniWrite %ImageQuality%,.\config.ini,Settings,ImageQuality
	IniWrite %ScDely%,.\config.ini,Settings,ScDely
}else{
	IniRead,ImagePath,.\config.ini,Settings,ImagePath
	IniRead,LoopTimes,.\config.ini,Settings,LoopTimes
	IniRead,UdDely,.\config.ini,Settings,UdDely
	IniRead,ImageQuality,.\config.ini,Settings,ImageQuality
	IniRead,ScDely,.\config.ini,Settings,ScDely,300
}
FileGetAttrib, Attributes, %ImagePath%
If !InStr(Attributes, "D"){
	MsgBox, ImagePath directory not exsist.Screenshot may not success.Please Choose one folder.
	Goto,SetImagePath
}
Return

F8::
InputBox, UserInput, LoopTimes, Please enter LoopTimes., , 180, 125
if !ErrorLevel{
    LoopTimes := UserInput
    IniWrite %LoopTimes%,.\config.ini,Settings,LoopTimes
}
return

F9::
Loop, %LoopTimes%
{
    WinActivate, Monster Hunter Rise ahk_class via
    Sleep, 333
    Send, {x Down}
    Sleep, UdDely
    Send, {x Up}
    Sleep, 5
    Send, {f Down}
    Sleep, UdDely
    Send, {f Up}
    Sleep, 5
    Send, {f Down}
    Sleep, UdDely
    Send, {f Up}
    ;Sleep, 400
    Sleep, 400
    Sleep, %ScDely%
    CaptureScreen(1,,ImagePath A_Index ".jpg",ImageQuality)
    Send, {a Down}
    Sleep, UdDely
    Send, {a Up}
    Sleep, 5
    Send, {f Down}
    Sleep, UdDely
    Send, {f Up}
    Sleep, 5
    Send, {a Down}
    Sleep, UdDely
    Send, {a Up}
    Sleep, 5
    Send, {f Down}
    Sleep, UdDely
    Send, {f Up}
    Sleep, 5
    Send, {f Down}
    Sleep, UdDely
    Send, {f Up}
    Sleep, 200
}
return

F10::
Loop, %LoopTimes%
{
    WinActivate, Monster Hunter Rise ahk_class via
    Sleep, 333
    Send, {x Down}
    Sleep, UdDely
    Send, {x Up}
    Sleep, 5
    Send, {f Down}
    Sleep, UdDely
    Send, {f Up}
    Sleep, 5
    Send, {f Down}
    Sleep, UdDely
    Send, {f Up}
    Sleep, 400
    Send, {a Down}
    Sleep, UdDely
    Send, {a Up}
    Sleep, 5
    Send, {f Down}
    Sleep, UdDely
    Send, {f Up}
    Sleep, 5
    Send, {a Down}
    Sleep, UdDely
    Send, {a Up}
    Sleep, 5
    Send, {f Down}
    Sleep, UdDely
    Send, {f Up}
    Sleep, 5
    Send, {f Down}
    Sleep, UdDely
    Send, {f Up}
    Sleep, 200
}
return

SetImagePath:
FileSelectFolder, OutputVar, , 3
If ErrorLevel{
return
}else{
if !(OutputVar ="")
    OutputVar := OutputVar . "\"
    ImagePath := OutputVar
    MsgBox Your ImagePath now:%ImagePath%
    IniWrite %ImagePath%,.\config.ini,Settings,ImagePath
    return
}

F12::
Exit:
IniWrite %ImagePath%,.\config.ini,Settings,ImagePath
IniWrite %LoopTimes%,.\config.ini,Settings,LoopTimes
IniWrite %UdDely%,.\config.ini,Settings,UdDely
IniWrite %ImageQuality%,.\config.ini,Settings,ImageQuality
IniWrite %ScDely%,.\config.ini,Settings,ScDely
ExitApp

F11::Pause


/*
PMC File Version 5.4.1
---[Do not edit anything in this section]---

[PMC Globals]|None||
[PMC Code v5.4.1]|F11||5|Window,2,Fast,0,1,Event,1,-1,-1|1|Macro1
Context=None|
Groups=开始:1
1|[Assign Variable]|uddely := 10|1|0|Variable|Expression||||1|
2|WinActivate||1|333|WinActivate||Monster Hunter Rise ahk_class via|||2|
3|a|{a Down}|1|0|Send|||||4|
4|[Pause]||1|%uddely%|Sleep|||||5|
5|a|{a Up}|1|0|Send|||||6|
6|[Pause]||1|5|Sleep|||||7|
7|f|{f Down}|1|0|Send|||||8|
8|[Pause]||1|%uddely%|Sleep|||||9|
9|f|{f Up}|1|0|Send|||||10|
10|[Pause]||1|5|Sleep|||||11|
11|a|{a Down}|1|0|Send|||||12|
12|[Pause]||1|%uddely%|Sleep|||||13|
13|a|{a Up}|1|0|Send|||||14|
14|[Pause]||1|5|Sleep|||||15|
15|f|{f Down}|1|0|Send|||||16|
16|[Pause]||1|%uddely%|Sleep|||||17|
17|f|{f Up}|1|0|Send|||||18|
18|[Pause]||1|5|Sleep|||||19|
19|f|{f Down}|1|0|Send|||||20|
20|[Pause]||1|%uddely%|Sleep|||||21|
21|f|{f Up}|1|0|Send|||||22|
22|[Pause]||1|200|Sleep|||||23|
23|x|{x Down}|1|0|Send|||||24|
24|[Pause]||1|%uddely%|Sleep|||||25|
25|x|{x Up}|1|0|Send|||||26|
26|[Pause]||1|5|Sleep|||||27|
27|f|{f Down}|1|0|Send|||||28|
28|[Pause]||1|%uddely%|Sleep|||||29|
29|f|{f Up}|1|0|Send|||||30|
30|[Pause]||1|5|Sleep|||||31|
31|f|{f Down}|1|0|Send|||||32|
32|[Pause]||1|%uddely%|Sleep|||||33|
33|f|{f Up}|1|0|Send|||||34|
34|[Pause]||1|400|Sleep|||||35|

*/
