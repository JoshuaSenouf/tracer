#include <spdlog/spdlog.h>

#include "gui/qt/tracerwindow.h"


/// Initialization of the Qt Window.
WindowQt::WindowQt(
    QWidget *parent)
    : QMainWindow(parent)
{
    // We create, setup and layout all our Qt related elements.
    InitializeUI();

    spdlog::debug(
        "WindowQt() - "
        "The Qt window has been successfully initialized.");
}

/// Call upon each step of the UI and widgets initialization.
void WindowQt::InitializeUI()
{
    InitializeUICreation();
    InitializeUISetup();
    InitializeUIConnects();
    InitializeUISettings();
    InitializeUILayout();

    spdlog::debug(
        "InitializeUI() - "
        "The UI has been successfully initialized.");
}

/// Create all the necessary Qt related elements, mostly widgets and layouts.
void WindowQt::InitializeUICreation()
{
    // Window
    main_widget = new QWidget();

    // MenuBar
    menu_bar = new QMenuBar();
    menu_bar_file_menu = menu_bar->addMenu("&File");
    menu_bar_help_menu = menu_bar->addMenu("&Help");
    menu_bar_file_exit_action = menu_bar_file_menu->addAction(
        "Exit", this, &QMainWindow::close);
    menu_bar_help_about_action = menu_bar_help_menu->addAction(
        "About", this, &WindowQt::ShowAboutWindow);

    // StatusBar
    status_bar = new QStatusBar();

    // Layouts
    main_layout = new QGridLayout();

    spdlog::debug(
        "InitializeUICreation() - "
        "The widgets have been successfully created.");
}

/// Set up the Qt related elements to ensure their proper behavior for the user.
void WindowQt::InitializeUISetup()
{
    // Window
    main_widget->setObjectName("main_widget");
    setCentralWidget(main_widget);

    // MenuBar
    menu_bar->setObjectName("menu_bar");
    setMenuBar(menu_bar);
    menu_bar_file_exit_action->setShortcut(Qt::CTRL + Qt::Key_Q);

    // StatusBar
    status_bar->setObjectName("status_bar");
    setStatusBar(status_bar);
    status_bar->setStyleSheet("background: gray");
    status_bar->showMessage("\"Tracer\" is ready to use!");

    spdlog::debug("InitializeUISetup() - "
        "The widgets have been successfully set up.");
}

/// Connect the Qt related elements to their dedicated slots.
void WindowQt::InitializeUIConnects()
{
    spdlog::debug(
        "InitializeUIConnects() - "
        "The widgets have been successfully connected to their slots.");
}

/// Set the settings and values of the Qt related elements.
void WindowQt::InitializeUISettings()
{
    spdlog::debug(
        "InitializeUISettings() - "
        "The widgets' settings and values have been successfully set.");
}

/// Layout the Qt related elements.
void WindowQt::InitializeUILayout()
{
    // MenuBar
    menu_bar->addMenu(menu_bar_file_menu);
    menu_bar->addMenu(menu_bar_help_menu);
    menu_bar_file_menu->addAction(menu_bar_file_exit_action);
    menu_bar_help_menu->addAction(menu_bar_help_about_action);

    // Main Layout

    setWindowTitle("Tracer - GUI");
    resize(800, 600);
    main_widget->setLayout(main_layout);

    spdlog::debug(
        "InitializeUILayout() - "
        "The widgets have been successfully layout.");
}

/// Display a simple message box with some general information about the application.
void WindowQt::ShowAboutWindow()
{
    QMessageBox::information(
        this,
        "About",
        "Tracer by Joshua Senouf\n\nEmail: joshua.senouf@gmail.com\nTwitter: @JoshuaSenouf",
        QMessageBox::Ok
    );

    spdlog::debug("ShowAboutWindow() - "
        "The \"About\" message box has been successfully executed.");
}

/// Overriding the native Qt close event in order to allow us to save the state of the application first.
void WindowQt::closeEvent(QCloseEvent *event)
{
    event->accept();
}
