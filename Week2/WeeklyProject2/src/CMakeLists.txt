project(cli)

find_package(Protobuf REQUIRED)

# All sources that also need to be tested in unit tests go into a static library
add_library(AccountData STATIC AccountData.cpp AccountData.h)
target_include_directories(AccountData PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(AccountData PRIVATE Cli users ProtoReadWrite ${PROTOBUF_LIBRARY})

add_library(users STATIC users.pb.cc users.pb.h)
target_include_directories(users PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(users PRIVATE ProtoReadWrite)

add_library(Transaction STATIC Transaction.cpp Transaction.h)
target_include_directories(Transaction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Cli STATIC Cli.cpp Cli.h)
target_include_directories(Cli PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Cli PRIVATE Transaction AccountData users AccountData ProtoReadWrite ${PROTOBUF_LIBRARY})

add_library(ProtoReadWrite STATIC ProtoReadWrite.cpp ProtoReadWrite.h)
target_include_directories(ProtoReadWrite PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ProtoReadWrite PRIVATE Cli users AccountData ${PROTOBUF_LIBRARY})

# The main program
add_executable(main main.cpp)
target_link_libraries(main PRIVATE Cli users AccountData ProtoReadWrite ${PROTOBUF_LIBRARY})