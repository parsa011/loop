file(GLOB sources "*.cpp")
add_library(loop STATIC ${sources})
target_include_directories(loop PUBLIC ${CMAKE_SOURCE_DIR}/include)

if(gnu)
    target_link_libraries(loop stdc++fs)
elseif(clang)
    target_link_libraries(loop c++fs)
endif()
