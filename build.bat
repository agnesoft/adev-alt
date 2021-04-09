@echo off

set PROJECTS_ROOT=%cd%\projects

mkdir build
cd build
mkdir bin

set BUILD_ROOT=%cd%
set ASTL_INCLUDE_PATH=%PROJECTS_ROOT%\astl\include
set CPP_FLAGS=/nologo /W4 /WX /std:c++latest /EHsc /I"%ASTL_INCLUDE_PATH%" /headerUnit "%ASTL_INCLUDE_PATH%\astl.hpp=%BUILD_ROOT%\astl\astl.hpp.ifc"

REM astl
mkdir astl
cd astl
cl.exe %CPP_FLAGS% /c /exportHeader /Fo /TP "%ASTL_INCLUDE_PATH%\astl.hpp"
cd ..

REM astl_test
cl.exe %CPP_FLAGS% /Fe"%BUILD_ROOT%\bin\astl_test.exe" "%PROJECTS_ROOT%\astl\test\main.cpp" "%BUILD_ROOT%\astl\astl.obj"

REM atest
mkdir atest
cd atest
cl.exe %CPP_FLAGS% /c /Fo /internalPartition "%PROJECTS_ROOT%\atest\source_location.cpp"
cl.exe %CPP_FLAGS% /c /Fo /internalPartition "%PROJECTS_ROOT%\atest\data.cpp"
cl.exe %CPP_FLAGS% /c /Fo /internalPartition "%PROJECTS_ROOT%\atest\stringify.cpp"
cl.exe %CPP_FLAGS% /c /Fo /internalPartition "%PROJECTS_ROOT%\atest\printer.cpp"
cl.exe %CPP_FLAGS% /c /Fo /internalPartition "%PROJECTS_ROOT%\atest\reporter.cpp"
cl.exe %CPP_FLAGS% /c /Fo /internalPartition "%PROJECTS_ROOT%\atest\expect_base.cpp"
cl.exe %CPP_FLAGS% /c /Fo /internalPartition "%PROJECTS_ROOT%\atest\expect_tomatch.cpp"
cl.exe %CPP_FLAGS% /c /Fo /internalPartition "%PROJECTS_ROOT%\atest\expect_tothrow.cpp"
cl.exe %CPP_FLAGS% /c /Fo /internalPartition "%PROJECTS_ROOT%\atest\matcher.cpp"
cl.exe %CPP_FLAGS% /c /Fo /internalPartition "%PROJECTS_ROOT%\atest\expect.cpp"
cl.exe %CPP_FLAGS% /c /Fo /internalPartition "%PROJECTS_ROOT%\atest\test_runner.cpp"
cl.exe %CPP_FLAGS% /c /Fo /interface /TP "%PROJECTS_ROOT%\atest\atest.cpp"
lib.exe /NOLOGO source_location.obj data.obj stringify.obj printer.obj reporter.obj expect_base.obj expect_tomatch.obj expect_tothrow.obj matcher.obj expect.obj test_runner.obj atest.obj /OUT:atest.lib
cd ..

REM atest_test
mkdir atest_test
cd atest_test
cl.exe %CPP_FLAGS% /Fe"%BUILD_ROOT%\bin\atest_test.exe" /ifcSearchDir "%BUILD_ROOT%\atest" "%PROJECTS_ROOT%\atest\test\atest_test.cpp" "%PROJECTS_ROOT%\atest\test\expect_tobe_test.cpp" "%PROJECTS_ROOT%\atest\test\expect_tothrow_test.cpp" "%PROJECTS_ROOT%\atest\test\expect_tomatch_test.cpp" "%PROJECTS_ROOT%\atest\test\printer_test.cpp" "%PROJECTS_ROOT%\atest\test\bad_test_suite.cpp" "%BUILD_ROOT%\atest\atest.lib" "%BUILD_ROOT%\astl\astl.obj"
cd ..

cd ..
