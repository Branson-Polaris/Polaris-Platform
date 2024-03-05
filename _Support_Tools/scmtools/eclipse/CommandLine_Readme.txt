About the Jazz SCM Commmand Line Interpretter. 

The Jazz SCM command line is built for linux and windows as "scm" and "scm.exe" 
respectively.  These should run out of the box for those platforms if downloaded 
through with the full rich Eclipse client.  

If you are using a different jvm than the one shipped with the RTC client, you may 
need to change the path to your jdk in the "scm.ini" file.   Set the path by opening "scm.ini", 
and modifying the line following "-vm" to the absolute path to your Java binary.
If you are using a non-IBM VM, you may also need to remove some of the -X options from 
"scm.ini".
 
New in 2.0.0.1, for improved command line performance you can run using "lscm.bat" or 
"lscm", which we call the lightweight scm command line.  This will create a daemon 
process on your machine, to reduce the startup time and improve the execution time 
for most commands.  You may need to replace the JAVA variable in these scripts 
to point towards the java that you run on your machine.  If you are using a non-IBM VM, 
you may need to remove some of the -X options from the script.      

If you are running the "lscm" script on a something other than 32-bit Linux, you may
need to update the line :
  SCM_DAEMON_PATH="${PRGPATH}/scm"
to 
  SCM_DAEMON_PATH="${PRGPATH}/scm.sh"

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
NEW in 404:
===========
Native Launcher for z/OS:
=-=-=-=-=-=-=-=-=-=-=-=-=
The native launcher that was introduced in 403 (see below) was not available for z/OS. But, with
v404 release, the native launcher has been made available even for z/OS.

64-bit Native Launcher for some platforms:
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
In 403 release, the native launcher on all supported platforms was a 32-bit application. However,
RTC ships 64-bit zips for most of these platforms. For some platforms, we ship both 32-bit and 64-bit
zips.

Starting 404 release, the 64-bit zips would have 64-bit native launcher, and 32-bit zips would
have the 32-bit native launcher. One exception to this is the Windows platform, where in both the
Win64 and Win32 zips contain the *32-bit* launcher.

Below is the list of dependencies pertaining to 64-bit native launcher on the respective platforms:
* Linux-x86-64:
    Compiler used: g++ 4.1.2
    Dependencies:
        RPM Package libstdc++-4.1.2-50.el5 (64-bit)
        RPM Package glibc-2.5.58 (64-bit)
        RPM Package libgcc-4.1.2-50.el5 (64-bit)
    Dependency Dump:
        linux-vdso.so.1 =>  (0x00007fff505fc000)
        libstdc++.so.6 => /usr/lib64/libstdc++.so.6 (0x0000003b2ee00000)
        libm.so.6 => /lib64/libm.so.6 (0x0000003b1d800000)
        libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x0000003b2a600000)
        libc.so.6 => /lib64/libc.so.6 (0x0000003b1cc00000)
        /lib64/ld-linux-x86-64.so.2 (0x0000003b1c800000)

        NOTE: Info on linux-vdso - http://www.ibm.com/developerworks/library/l-lpic1-v3-102-3/

* Linux-PowerPC:
    Compiler used: g++ 4.4.7
    Dependencies:
        RPM Package libstdc++-4.4.7-3.el6.ppc64  (64-bit)
        RPM Package glibc-2.12-1.107.el6.ppc64  (64-bit)
        RPM Package libgcc-4.4.7-3.el6.ppc64 (64-bit)
    Dependency Dump:
        linux-vdso64.so.1 =>  (0x0000040000000000)
        libstdc++.so.6 => /usr/lib64/libstdc++.so.6 (0x000000803bf70000)
        libm.so.6 => /lib64/libm.so.6 (0x000000803a680000)
        libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x000000803b250000)
        libc.so.6 => /lib64/libc.so.6 (0x000000803a420000)
        /lib64/ld64.so.1 (0x000000004b130000)

* Linux-System/z:
    Compiler used: g++ 4.1.2
    Dependencies:
        RPM Package libstdc++-4.1.2-50.el5  (64-bit)
        RPM Package glibc-2.5.81 (64-bit)
        RPM Package libgcc-4.1.2-50.el5 (64-bit)
    Dependency Dump:
        libstdc++.so.6 => /usr/lib64/libstdc++.so.6 (0x000000492e742000)
        libm.so.6 => /lib64/libm.so.6 (0x000000492e34e000)
        libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x000000492e724000)
        libc.so.6 => /lib64/libc.so.6 (0x000000492e1c9000)
        /lib/ld64.so.1 (0x000002aaaaaaa000)

* Mac OS:
    Compiler used: i686-apple-darwin10-g++ (GCC) 4.2.1 
    Dependencies (All 64-bit libraries):
        /usr/lib/libiconv.2.dylib (compatibility version 7.0.0, current version 7.0.0)
        /usr/lib/libstdc++.6.dylib (compatibility version 7.0.0, current version 7.9.0)
        /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 125.2.11)

* AIX:
    Compiler used: Visual Age Compiler Suite (IBM XL C/C++ for AIX, V11.1 (5724-X13) Version: 11.01.0000.0000)
    Dependencies (All 64-bit libraries):
         /usr/lib/libc.a(shr_64.o)
         /usr/lib/libC.a(shr_64.o)
         /usr/lib/libC.a(ansi_64.o)
         /usr/lib/libiconv.a(shr4_64.o)
         /unix
         /usr/lib/libcrypt.a(shr_64.o)
         /usr/lib/libC.a(shrcore_64.o)
         /usr/lib/libC.a(ansicore_64.o)

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
NEW in 403:
===========
Native Launcher in LSCM:
=-=-=-=-=-=-=-=-=-=-=-=-
Starting with 403-M4, we have included a native launcher (a 32-bit c++ application) 
that is invoked by lscm script, by default. However, the java launcher is also bundled alongwith.

To force the lscm script to invoke the java launcher, set the environment variable
LSCM_USE_JAVA_FEC to any value (it just needs to be defined). The lscm script has the
necessary logic of checking this environment variable and running the java launcher, if
it is set; otherwise, it uses the native launcher (if it is available for your platform).

Available Platforms:
--------------------
The native launcher is currently made available for the following platforms:
Windows, Linux (System/z, x86 and Power PC), Solaris (Sparc), Mac OS and AIX.

As of this release, please note that it is not available for z/OS and IBM i platforms.

For details on the supported platforms, such as exact versions / flavours of OS,
please see the official platform support page: https://jazz.net/library/article/811/

Platform Specific Notes (including Pre-Requisites):
---------------------------------------------------
1. Windows:
    Compiler used: Microsoft VC++ 2008
    Dependencies:
        On some older versions of Windows (like Windows XP SP2), you might have to install
        Microsoft VC++ 2008 Redistributable package x86 (32-bit). This is freely available
        for download (http://www.microsoft.com/en-in/download/details.aspx?id=29)

2. Linux-x86:
    Compiler used: g++ 4.1.2
    Dependencies:
        RPM Package libstdc++-4.1.2.50.el5 (i386)  (32-bit)
        RPM Package glibc-2.5.58 (i686)  (32-bit)
    Dependency Dump:
        linux-gate.so.1 =>  (0xffffe000)
        libstdc++.so.6 => /usr/lib/libstdc++.so.6 (0x00983000)
        libm.so.6 => /lib/libm.so.6 (0x0063c000)
        libgcc_s.so.1 => /lib/libgcc_s.so.1 (0x00c50000)
        libc.so.6 => /lib/libc.so.6 (0x004bf000)
        /lib/ld-linux.so.2 (0x004a0000)

        NOTE: Info on linux-gate - http://www.trilithium.com/johan/2005/08/linux-gate/

3. Linux-PowerPC:
    Compiler used: g++ 4.4.6
    Dependencies:
        RPM Package libstdc++-4.4.6.3.el6 (ppc)  (32-bit)
        RPM Package glibc-2.12.1.47.el6_2.9 (ppc)  (32-bit)
    Dependency Dump:
        linux-vdso32.so.1 =>  (0x00100000)
        libstdc++.so.6 => /usr/lib/libstdc++.so.6 (0x0feb0000)
        libm.so.6 => /lib/libm.so.6 (0x0fcd0000)
        libgcc_s.so.1 => /lib/libgcc_s.so.1 (0x0fc90000)
        libc.so.6 => /lib/libc.so.6 (0x40020000)
        /lib/ld.so.1 (0x202f0000)

4. Linux-System/z:
    Compiler used: g++ 4.1.2
    Dependencies:
        RPM Package libstdc++-4.1.2.50.el5 (s390)  (32-bit)
        RPM Package glibc-2.5.81 (s390)  (32-bit)
    Dependency Dump:
        libstdc++.so.6 => /usr/lib/libstdc++.so.6 (0x47927000)
        libm.so.6 => /lib/libm.so.6 (0x4770b000)
        libgcc_s.so.1 => /lib/libgcc_s.so.1 (0x477d0000)
        libc.so.6 => /lib/libc.so.6 (0x475bd000)
        /lib/ld.so.1 (0x55555000)

5. Solaris-SPARC:
     Compiler used: g++ v3.4.3
     Dependencies (All 32-bit libraries):
         libsocket.so.1 =>        /lib/libsocket.so.1
         libnsl.so.1 =>   /lib/libnsl.so.1
         libstdc++.so.6 =>        /usr/sfw/lib/libstdc++.so.6
         libm.so.2 =>     /lib/libm.so.2
         libgcc_s.so.1 =>         /usr/sfw/lib/libgcc_s.so.1
         libc.so.1 =>     /lib/libc.so.1
         libmp.so.2 =>    /lib/libmp.so.2
         libmd.so.1 =>    /lib/libmd.so.1
         libscf.so.1 =>   /lib/libscf.so.1
         libdoor.so.1 =>  /lib/libdoor.so.1
         libuutil.so.1 =>         /lib/libuutil.so.1
         libgen.so.1 =>   /lib/libgen.so.1
         /platform/sun4v/lib/libc_psr.so.1
         /platform/sun4v/lib/libmd_psr.so.1

         NOTE: On Solaris, note that native launcher is built using gcc, and not
         the native compiler.

6. Mac OS:
    Compiler used: i686-apple-darwin10-g++ (GCC) 4.2.1 
    Dependencies (All 32-bit libraries):
        /usr/lib/libiconv.2.dylib (compatibility version 7.0.0, current version 7.0.0)
        /usr/lib/libstdc++.6.dylib (compatibility version 7.0.0, current version 7.9.0)
        /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 125.2.11)

7. AIX:
    Compiler used: Visual Age Compiler Suite (IBM XL C/C++ for AIX, V11.1 (5724-X13) Version: 11.01.0000.0000)
    Dependencies (All 32-bit libraries):
         /usr/lib/libc.a(shr.o)
         /usr/lib/libC.a(shr.o)
         /usr/lib/libC.a(ansi_32.o)
         /usr/lib/libiconv.a(shr4.o)
         /unix
         /usr/lib/libcrypt.a(shr.o)
         /usr/lib/libC.a(shrcore.o)
         /usr/lib/libC.a(ansicore_32.o)
