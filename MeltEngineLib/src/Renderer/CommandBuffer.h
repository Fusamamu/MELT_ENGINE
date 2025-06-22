#ifndef COMMAND_BUFFER_H
#define COMMAND_BUFFER_H

#include "RenderCommand.h"

namespace MELT::GRAPHIC
{
    class CommandBuffer
    {
    public:
        void add(std::unique_ptr<ICommand> cmd)
        {
            m_commands.emplace_back(std::move(cmd));
        }

        void execute()
        {
            for (std::unique_ptr<ICommand>& _command : m_commands)
                _command->execute();
            m_commands.clear();
        }
    private:
        std::vector<std::unique_ptr<ICommand>> m_commands;
    };
}

#endif
