cmake_minimum_required(VERSION 3.10)
project(Lua VERSION 5.4.6 LANGUAGES C)

file(GLOB LUA_SOURCES ${LUA_DIR}/*.c)

set(LUA_DIR cherry/vendor/lua)

set(LUA_SOURCES
    ${LUA_DIR}/lapi.c
    ${LUA_DIR}/lcode.c
    ${LUA_DIR}/lctype.c
    ${LUA_DIR}/ldebug.c
    ${LUA_DIR}/ldo.c
    ${LUA_DIR}/ldump.c
    ${LUA_DIR}/lfunc.c
    ${LUA_DIR}/lgc.c
    ${LUA_DIR}/llex.c
    ${LUA_DIR}/lmem.c
    ${LUA_DIR}/lobject.c
    ${LUA_DIR}/lopcodes.c
    ${LUA_DIR}/lparser.c
    ${LUA_DIR}/lstate.c
    ${LUA_DIR}/lstring.c

    ${LUA_DIR}/ltable.c
    ${LUA_DIR}/ltm.c
    ${LUA_DIR}/lundump.c
    ${LUA_DIR}/lvm.c
    ${LUA_DIR}/lzio.c
    ${LUA_DIR}/ltests.c
    ${LUA_DIR}/lauxlib.c
    ${LUA_DIR}/lbaselib.c

    ${LUA_DIR}/ldblib.c
    ${LUA_DIR}/liolib.c
    ${LUA_DIR}/lmathlib.c
    ${LUA_DIR}/loslib.c
    ${LUA_DIR}/ltablib.c
    ${LUA_DIR}/lstrlib.c
    ${LUA_DIR}/lutf8lib.c

    ${LUA_DIR}/loadlib.c
    ${LUA_DIR}/lcorolib.c
    ${LUA_DIR}/linit.c)

add_library(lua ${LUA_SOURCES})

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

target_compile_definitions(lua 
    PUBLIC LUA_USE_LINUX
    # PUBLIC LUA_USE_READLINE
)

target_compile_options(lua PRIVATE 
    -Wfatal-errors -Wall -Wextra -Wshadow -Wundef -Wwrite-strings -Wredundant-decls -Wdisabled-optimization -Wdouble-promotion -Wmissing-declarations -Wlogical-op -Wno-aggressive-loop-optimizations -Wdeclaration-after-statement -Wmissing-prototypes -Wnested-externs -Wstrict-prototypes -Wc++-compat -Wold-style-definition
)

# target_compile_options(lua PRIVATE "-fno-stack-protector -fno-common -march=native")

find_library(LIB_DL dl)
if(NOT LIB_DL)
    message(FATAL_ERROR "Could not find libdl. Please install it.")
endif()

set(USE_READLINE OFF)
if(USE_READLINE)
    find_package(Readline REQUIRED)
    if(NOT Readline_FOUND)
        message(FATAL_ERROR "Could not find libreadline. Please install it.")
    endif()
endif()

target_link_libraries(lua ${LIB_DL} ${Readline_LIBRARIES})
find_library(LIBM m)
target_link_libraries(lua ${LIBM})

if (USE_READLINE)
    target_include_directories(lua PRIVATE ${Readline_INCLUDE_DIRS})
endif()


