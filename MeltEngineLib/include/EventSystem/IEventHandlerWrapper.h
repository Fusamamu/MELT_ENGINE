#pragma once
#include <string>
#include "Event.h"

namespace MELT
{
    class IEventHandlerWrapper
    {
    public:
        void Execute(const Event& e)
        {
            Call(e);
        }

        virtual std::string GetType() const = 0;
        virtual bool IsDestroyOnSuccess() const = 0;
    private:
        virtual void Call(const Event& e) = 0;
    };
}