#ifndef TRACERWINDOW_H
#define TRACERWINDOW_H

#include <fstream>
#include <iostream>
#include <string>

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include <QMainWindow>


class TracerWindow : public QMainWindow
{
    Q_OBJECT

    public:
        TracerWindow(QWidget *parent = 0);

    private:
        void initUi();
        void initUiCreation();
        void initUiSetup();
        void initUiConnects();
        void initUiSettings();
        void initUiLayout();

        QAction *menuBarFileExitAction;
        QAction *menuBarHelpAboutAction;

        QGridLayout *mainLayout;
        QGridLayout *memoLayout;

        QMenu *menuBarFileMenu;
        QMenu *menuBarHelpMenu;

        QMenuBar *menuBar;

        QPushButton *toolBarFormatClearButton;
        QPushButton *toolBarFormatColorButton;

        QStatusBar *statusBar;

        QWidget *mainWidget;

    protected:
        void closeEvent(QCloseEvent *event) override;

    private slots:
        void showAboutWindow();
};

#endif // TRACERWINDOW_H
