


if(ENABLE_TESTS)
	add_executable(test-filter1 ${CMAKE_SOURCE_DIR}/tests/test-filters.cpp)
	target_link_libraries(test-filter1 acidcam Threads::Threads)
	target_compile_options(test-filter1 PRIVATE ${COMPILER_FLAGS})
	add_executable(test-image ${CMAKE_SOURCE_DIR}/tests/test-image-filters.cpp)
	target_link_libraries(test-image acidcam Threads::Threads)
	target_compile_options(test-image PRIVATE ${COMPILER_FLAGS})
	add_executable(test-subfilter ${CMAKE_SOURCE_DIR}/tests/test-subfilter.cpp)
	target_link_libraries(test-subfilter acidcam Threads::Threads)
	target_compile_options(test-subfilter PRIVATE ${COMPILER_FLAGS})
endif()


if(ENABLE_TESTS)
	enable_testing()
	add_test(NAME test1 COMMAND $<TARGET_FILE:test-filter1>)
	add_test(NAME test2 COMMAND $<TARGET_FILE:test-image>)
	add_test(NAME test3 COMMAND $<TARGET_FILE:test-subfilter>)
endif()