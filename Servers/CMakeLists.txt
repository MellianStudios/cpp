add_executable(Auth Auth/Main.cpp)
add_executable(Chat Chat/Main.cpp)
add_executable(Guild Guild/Main.cpp)
add_executable(Instance Instance/Main.cpp)
add_executable(Mail Mail/Main.cpp)
add_executable(Manager Manager/Main.cpp)
add_executable(World World/Main.cpp)

target_include_directories(Auth PUBLIC "${PROJECT_SOURCE_DIR}/Core")
target_link_libraries(Auth PUBLIC Account)

target_include_directories(Manager PUBLIC "${PROJECT_SOURCE_DIR}/Core")
target_link_libraries(Manager PUBLIC MigrationManager Command)

target_include_directories(World PUBLIC "${PROJECT_SOURCE_DIR}/Core")
target_link_libraries(World PUBLIC BlizzardLoader)

if (NOT EXISTS ${SERVER_TARGET_PATH})
    add_custom_command(TARGET Auth POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${SERVER_TARGET_PATH})
endif ()

if (EXISTS "${PROJECT_SOURCE_DIR}/.env")
    add_custom_command(TARGET Auth POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/.env ${SERVER_TARGET_PATH}/.env)
else ()
    add_custom_command(TARGET Auth POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/.env.example ${SERVER_TARGET_PATH}/.env)
endif ()

add_custom_command(TARGET Auth POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Auth> ${SERVER_TARGET_PATH})
add_custom_command(TARGET Chat POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Chat> ${SERVER_TARGET_PATH})
add_custom_command(TARGET Guild POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Guild> ${SERVER_TARGET_PATH})
add_custom_command(TARGET Instance POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Instance> ${SERVER_TARGET_PATH})
add_custom_command(TARGET Mail POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Mail> ${SERVER_TARGET_PATH})
add_custom_command(TARGET Manager POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Manager> ${SERVER_TARGET_PATH})
add_custom_command(TARGET World POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:World> ${SERVER_TARGET_PATH})