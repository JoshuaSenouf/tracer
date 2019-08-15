#ifndef GUI_H
#define GUI_H

#include <string>

#include "context.h"


struct ContextGUI : public Context
{
    ContextGUI();
    ContextGUI(CLIArgs cliArgs);

    virtual bool Initialize() override;
    virtual bool Execute() override;

    private:
        RenderGlobals _globals;
};

#endif // GUI_H
