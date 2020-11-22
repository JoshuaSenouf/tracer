#ifndef CONTEXT_H
#define CONTEXT_H

#include "utility/cli_helper.h"


class Context
{
    public:
        Context();

        virtual bool Initialize() = 0;
        virtual bool Execute() = 0;

    protected:
        CLIArgs args_;
};

#endif // CONTEXT_H
