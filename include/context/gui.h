#ifndef GUI_H
#define GUI_H

#include <string>

#include <QtWidgets/QApplication>

#include "render_helper.h"
#include "tracerwindow.h"

#include "context.h"


struct ContextGUI : public Context
{
    ContextGUI();
    ContextGUI(CLIArgs cliArgs);

    virtual bool Initialize() override;
    virtual bool Execute() override;

    private:
        RenderGlobals _globals;

        QApplication *_qtApp;

        TracerWindow *_tracerWindow;
};

#endif // GUI_H
