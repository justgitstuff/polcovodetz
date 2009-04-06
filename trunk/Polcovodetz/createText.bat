@echo off


path c:\Qt\4.5.0\bin;C:\Program Files\doxygen\bin

@echo ***********************TRANSLATION********************

lupdate Polcovodetz/Polcovodetz.pro
lrelease Polcovodetz/Polcovodetz.pro

copy Polcovodetz\Internationalization\*.qm debug\


@echo ***********************DOCUMENTATION********************

doxygen Doxyfile

