@echo off

path c:\Qt\4.5.0\bin;C:\Program Files\doxygen\bin

md %TEMP%\logs
echo LOG ARE SAVED TO %TEMP%\logs  

@echo ***********************BUILD PRO-FILES********************

cd Polcovodetz
qmake -project -o Polcovodetz.pro %TEMP%\logs\qmake.log
cd..

@echo ***********************TRANSLATION********************

lupdate Polcovodetz/Polcovodetz.pro > %TEMP%\logs\lupdate.log
lrelease Polcovodetz/Polcovodetz.pro > %TEMP%\logs\lrelease.log

copy Polcovodetz\Internationalization\*.qm debug\


@echo ***********************DOCUMENTATION********************

doxygen Doxyfile > %TEMP%\logs\DoxyLog.log

