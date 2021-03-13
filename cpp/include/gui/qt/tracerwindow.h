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
        TracerWindow(
            QWidget *parent = 0);

    private:
        void InitializeUI();
        void InitializeUICreation();
        void InitializeUISetup();
        void InitializeUIConnects();
        void InitializeUISettings();
        void InitializeUILayout();

        QAction *menu_bar_file_exit_action;
        QAction *menu_bar_help_about_action;

        QGridLayout *main_layout;
        QGridLayout *memo_layout;

        QMenu *menu_bar_file_menu;
        QMenu *menu_bar_help_menu;

        QMenuBar *menu_bar;

        QPushButton *tool_bar_format_clear_button;
        QPushButton *tool_bar_format_color_button;

        QStatusBar *status_bar;

        QWidget *main_widget;

    protected:
        void closeEvent(
            QCloseEvent *event) override;

    private slots:
        void ShowAboutWindow();
};

#endif // TRACERWINDOW_H
