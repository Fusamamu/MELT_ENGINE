#ifndef LOGGER_H
#define LOGGER_H

#include "Core.h"

namespace MELT
{
    struct LogEntry
    {
        std::string message;
        spdlog::level::level_enum level;
    };

    class LogSink : public spdlog::sinks::base_sink<std::mutex>
    {
    public:
        const std::vector<LogEntry>& get_entries() const { return m_entries; }

        void clear()
        {
            std::lock_guard<std::mutex> lock(this->mutex_);
            m_entries.clear();
        }

    protected:
        void sink_it_(const spdlog::details::log_msg& msg) override
        {
            spdlog::memory_buf_t formatted;
            formatter_->format(msg, formatted);
            //std::lock_guard<std::mutex> lock(this->mutex_);

            if (m_entries.size() >= max_lines)
                m_entries.erase(m_entries.begin());

            m_entries.push_back({
                fmt::to_string(formatted),
                msg.level
            });
        }

        void flush_() override { }

    private:
        std::vector<LogEntry> m_entries;
        size_t max_lines = 1000;
    };

    class Logger
    {
    public:
        Logger() = default;
        ~Logger() = default;

        const MELT::LogSink& log_sink(){
            return *m_engine_log_sink;
        }

        void init()
        {
            m_engine_log_sink = std::make_shared<MELT::LogSink>();
            auto _console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

            auto _logger = std::make_shared<spdlog::logger>(
                "melt_engine",
                spdlog::sinks_init_list{
                        m_engine_log_sink,
                        _console_sink
                });
            spdlog::set_default_logger(_logger);
            spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
            spdlog::set_level(spdlog::level::debug);
        }

        void log(const std::string& message)
        {
            spdlog::info(message);
        }

        void clear()
        {
            m_engine_log_sink->clear();
        }
    private:
        std::shared_ptr<MELT::LogSink> m_engine_log_sink;
    };
}

#endif //LOGGER_H
