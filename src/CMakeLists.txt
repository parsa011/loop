file(GLOB sources "*.cpp")
add_library(loop STATIC ${sources})
target_include_directories(loop PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_features(loop PUBLIC cxx_std_20)

if(gcc OR clang)
    target_link_libraries(loop stdc++fs)
endif()
