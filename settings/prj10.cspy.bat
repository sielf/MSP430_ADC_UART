@REM This batch file has been generated by the IAR Embedded Workbench
@REM C-SPY Debugger, as an aid to preparing a command line for running
@REM the cspybat command line utility using the appropriate settings.
@REM
@REM You can launch cspybat by typing the name of this batch file followed
@REM by the name of the debug file (usually an ELF/DWARF or UBROF file).
@REM Note that this file is generated every time a new debug session
@REM is initialized, so you may want to move or rename the file before
@REM making changes.
@REM 


"C:\Programm\IAR Systems\Embedded Workbench 6.0\common\bin\cspybat" "C:\Programm\IAR Systems\Embedded Workbench 6.0\430\bin\430proc.dll" "C:\Programm\IAR Systems\Embedded Workbench 6.0\430\bin\430fet.dll"  %1 --plugin "C:\Programm\IAR Systems\Embedded Workbench 6.0\430\bin\430bat.dll" --backend -B "-p" "C:\Programm\IAR Systems\Embedded Workbench 6.0\430\config\MSP430G2553.ddf" "--iv_base" "0xFFE0" "-d" "fet" "--erase_main_and_info" "--derivative" "MSP430G2xx3" "--protocol" "automatic" "--eem" "EMEX_LOW" "--port" "Automatic" "--connection" "ti_usb" "--settlingtime=0" "--msp430_dll" "msp430.dll" "--vccDefault" "3.3" 


