add_library(hc_stack INTERFACE)

target_include_directories(hc_stack INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(NOT HC_SKIP_TESTS)
    add_subdirectory(test)
endif()

install(TARGETS hc_stack EXPORT hc_exports)
install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN *.hpp)
