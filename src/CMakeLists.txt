
execute_process(COMMAND llvm-config --cxxflags OUTPUT_VARIABLE LLVM_CXX_FLAGS)
string(REGEX REPLACE "\n" " " LLVM_CXX_FLAGS "${LLVM_CXX_FLAGS}")
#message("LLVM_CXX_FLAGS=" ${LLVM_CXX_FLAGS} )

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${LLVM_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LLVM_CXX_FLAGS}")
 
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    )

set(SRC_LIST
    ac_ast.cpp
    ac_codegen.cpp
    ac_gc.cpp
    ac_hashvalue.cpp
    ac_lexer.cpp
    ac_msghandler.cpp
    ac_parser.cpp
    ac_stdlib.cpp
    ac_unichar.cpp
    ac_utf.cpp
    ac_utility.cpp
    ac_variable.cpp
    ac_vm.cpp
    MurmurHash3.cpp
    yyparser.cpp
    )

add_library(aclang
    ${SRC_LIST}
    )
