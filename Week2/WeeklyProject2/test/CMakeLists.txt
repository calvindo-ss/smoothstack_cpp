project(tests)

# The test program
#add_executable(tests tests.cpp)
#target_link_libraries(tests PRIVATE User Cli)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
#target_link_libraries(tests gtest_main)
add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE Cli users AccountData ProtoReadWrite ${PROTOBUF_LIBRARY} gtest_main)
#target_link_libraries(tests gtest_main)
add_test(NAME example_test COMMAND example)
