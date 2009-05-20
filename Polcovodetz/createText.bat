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

@echo ***********************COPYING FILES********************

copy Polcovodetz\Internationalization\*.qm debug\
copy Polcovodetz\Internationalization\*.qm release\

copy Scripts\*.script debug\
copy Scripts\*.script release\

copy Maps\*.map debug\
copy Maps\*.map release\

@echo ***********************DOCUMENTATION********************

doxygen Doxyfile > %TEMP%\logs\DoxyLog.log

