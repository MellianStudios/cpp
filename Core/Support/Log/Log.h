#ifndef MELLIANCORE_LOG_H
#define MELLIANCORE_LOG_H

#include <memory>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class Log
{
private:
    static std::shared_ptr<spdlog::logger> m_core_logger;
public:
    static void init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        m_core_logger = spdlog::stdout_color_mt("Mellian");
        m_core_logger->set_level(spdlog::level::trace);
    }

    inline static std::shared_ptr<spdlog::logger> &getLogger()
    {
        return m_core_logger;
    }
};

#endif //MELLIANCORE_LOG_H

#define MEL_CRITICAL(...) ::Log::getLogger()->critical(__VA_ARGS__)
#define MEL_ERROR(...) ::Log::getLogger()->error(__VA_ARGS__)
#define MEL_WARN(...) ::Log::getLogger()->warn(__VA_ARGS__)
#define MEL_INFO(...) ::Log::getLogger()->info(__VA_ARGS__)
#define MEL_TRACE(...) ::Log::getLogger()->trace(__VA_ARGS__)
#define MEL_DEBUG(...) ::Log::getLogger()->debug(__VA_ARGS__)
