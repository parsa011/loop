file(GLOB test_sources "*.cpp")

function(l_add_test file_)
    string(REPLACE ".cpp" "" filename ${file_})
    add_executable(${filename} ${file_})
    target_link_libraries(${filename} PUBLIC loop)
    target_compile_features(${filename} INTERFACE cxx_std_20)
    enable_warns(${filename})
endfunction()

l_add_test(ast.cpp)
l_add_test(tokenizer.cpp)
l_add_test(test.cpp)
l_add_test(unit_test)
