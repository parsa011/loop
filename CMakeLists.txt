cmake_minimum_required(VERSION 3.5)
project(LOOP CXX)



if(${CMAKE_CXX_COMPILER_ID} MATCHES ".*Clang")
    set(clang ON)
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
    set(gcc ON)
endif()

option(tests "compile unit tests" OFF)


function(enable_warns src)
    if(MSVC)
        set(opts /W4 /WX /premissive-)
    elseif(clang OR gcc)
        set(opts -Wextra -Wpedantic -Werror -Wall)
    else()
        message(AUTHOR_WARNING "couldn't detect compiler for warnings")
    endif()
    target_compile_options(${src} ${opts})
endfunction()

add_subdirectory(src)

if(tests)
    add_subdirectory(test)
endif()
