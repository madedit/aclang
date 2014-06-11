@set OLD_PATH=%PATH%
@set PATH=D:\cmake-2.8.10.2-win32-x86\bin\;d:\mingw\bin;d:\llvm\cmake_mingw\bin
cmake .. -G"MinGW Makefiles" -DCMAKE_CXX_COMPILER=g++.exe -DCMAKE_C_COMPILER=gcc.exe
rem -DCMAKE_EXE_LINKER_FLAGS="-mno-cygwin"
@set PATH=%OLD_PATH%
pause