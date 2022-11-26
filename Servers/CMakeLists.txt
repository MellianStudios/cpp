add_executable(Auth Auth/Main.cpp)
add_executable(Chat Chat/Main.cpp)
add_executable(Guild Guild/Main.cpp)
add_executable(Instance Instance/Main.cpp)
add_executable(Mail Mail/Main.cpp)
add_executable(World World/Main.cpp)

target_include_directories(Auth PUBLIC "${PROJECT_SOURCE_DIR}/Core")
target_link_libraries(Auth PUBLIC Account)