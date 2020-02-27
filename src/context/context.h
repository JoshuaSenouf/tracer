#ifndef CONTEXT_H
#define CONTEXT_H

#include "cli_helper.h"


struct Context
{
    Context();

    virtual bool Initialize() = 0;
    virtual bool Execute() = 0;

    CLIArgs _args;
};

#endif // CONTEXT_H
