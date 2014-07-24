
execute_process(COMMAND llvm-config --cxxflags OUTPUT_VARIABLE LLVM_CXX_FLAGS)
string(REGEX REPLACE "\n" " " LLVM_CXX_FLAGS "${LLVM_CXX_FLAGS}")
#message("LLVM_CXX_FLAGS=" ${LLVM_CXX_FLAGS} )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LLVM_CXX_FLAGS}")

execute_process(COMMAND llvm-config --ldflags OUTPUT_VARIABLE LLVM_LDFLAGS)
string(REGEX REPLACE "\n" " " LLVM_LDFLAGS "${LLVM_LDFLAGS}")
set(CMAKE_EXE_LINKER_FLAGS " ${CMAKE_EXE_LINKER_FLAGS} ${LLVM_LDFLAGS} -static-libgcc -static-libstdc++")

execute_process(COMMAND llvm-config --libs x86 jit mcjit OUTPUT_VARIABLE LLVM_LIBS) 
string(REGEX REPLACE "\n" "" LLVM_LIBS "${LLVM_LIBS}")

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    )

set(SRC_LIST
    main.cpp
    test_gc.cpp
    test_lexer.cpp
    test_parser.cpp
    )

add_executable(aclang-test
    ${SRC_LIST}
    )

target_link_libraries(aclang-test
    aclang
    ${LLVM_LIBS}
    )
