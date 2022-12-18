include(FetchContent)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG ad0e89cbfb4d0c1ce4d097e134eb7be67baebb36 #1.11.0
)

FetchContent_MakeAvailable(spdlog)


FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.11.2
)

FetchContent_MakeAvailable(json)
