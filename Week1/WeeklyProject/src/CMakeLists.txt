project(cli)

# All sources that also need to be tested in unit tests go into a static library
add_library(User STATIC User.cpp User.h)
target_include_directories(User PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_library(Cli STATIC Cli.cpp Cli.h)
target_include_directories(Cli PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Cli PRIVATE User)

# The main program
add_executable(main main.cpp)
target_link_libraries(main PRIVATE Cli)