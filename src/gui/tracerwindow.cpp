#include <spdlog/spdlog.h>

#include "tracerwindow.h"


/// Initialization of the Qt Window.
TracerWindow::TracerWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // We create, setup and layout all our Qt related elements.
    initUi();

    spdlog::debug("TracerWindow() - "
        "The Qt window has been successfully initialized.");
}

/// Call upon each step of the UI and widgets initialization.
void TracerWindow::initUi()
{
    initUiCreation();
    initUiSetup();
    initUiConnects();
    initUiSettings();
    initUiLayout();

    spdlog::debug("initUi() - "
        "The UI has been successfully initialized.");
}

/// Create all the necessary Qt related elements, mostly widgets and layouts.
void TracerWindow::initUiCreation()
{
    // Window
    mainWidget = new QWidget();

    // MenuBar
    menuBar = new QMenuBar();
    menuBarFileMenu = menuBar->addMenu("&File");
    menuBarHelpMenu = menuBar->addMenu("&Help");
    menuBarFileExitAction = menuBarFileMenu->addAction(
        "Exit", this, &QMainWindow::close);
    menuBarHelpAboutAction = menuBarHelpMenu->addAction(
        "About", this, &TracerWindow::showAboutWindow);

    // StatusBar
    statusBar = new QStatusBar();

    // Layouts
    mainLayout = new QGridLayout();

    spdlog::debug("initUiCreation() - "
        "The widgets have been successfully created.");
}

/// Set up the Qt related elements to ensure their proper behavior for the user.
void TracerWindow::initUiSetup()
{
    // Window
    mainWidget->setObjectName("mainWidget");
    setCentralWidget(mainWidget);

    // MenuBar
    menuBar->setObjectName("menuBar");
    setMenuBar(menuBar);
    menuBarFileExitAction->setShortcut(Qt::CTRL + Qt::Key_Q);

    // StatusBar
    statusBar->setObjectName("statusBar");
    setStatusBar(statusBar);
    statusBar->setStyleSheet("background: gray");
    statusBar->showMessage("\"Tracer\" is ready to use!");

    spdlog::debug("initUiSetup() - "
        "The widgets have been successfully set up.");
}

/// Connect the Qt related elements to their dedicated slots.
void TracerWindow::initUiConnects()
{
    spdlog::debug("initUiConnects() - "
        "The widgets have been successfully connected to their slots.");
}

/// Set the settings and values of the Qt related elements.
void TracerWindow::initUiSettings()
{
    spdlog::debug("initUiSettings() - "
        "The widgets' settings and values have been successfully set.");
}

/// Layout the Qt related elements.
void TracerWindow::initUiLayout()
{
    // MenuBar
    menuBar->addMenu(menuBarFileMenu);
    menuBar->addMenu(menuBarHelpMenu);
    menuBarFileMenu->addAction(menuBarFileExitAction);
    menuBarHelpMenu->addAction(menuBarHelpAboutAction);

    // Main Layout

    setWindowTitle("Tracer - GUI");
    resize(800, 600);
    mainWidget->setLayout(mainLayout);

    spdlog::debug("initUiLayout() - "
        "The widgets have been successfully layout.");
}

/// Display a simple message box with some general information about the application.
void TracerWindow::showAboutWindow()
{
    QMessageBox::information(
        this,
        "About",
        "Tracer by Joshua Senouf\n\nEmail: joshua.senouf@gmail.com\nTwitter: @JoshuaSenouf",
        QMessageBox::Ok
    );

    spdlog::debug("showAboutWindow() - "
        "The \"About\" message box has been successfully executed.");
}

/// Overriding the native Qt close event in order to allow us to save the state of the application first.
void TracerWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}
