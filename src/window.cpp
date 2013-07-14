#include <iostream>
#include <QtGui>
#include <QPixmap>
#include <QApplication>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include "window.h"
#include "time.h"


Window::Window()
{
    //configure timer
    timer = new QTime;
    time = new Time;
    pauseTrackingAction=NULL;

    configureTrayIcon();
    configureButtons();
    configureLayout();

    setWindowTitle(tr("Time tracker 0.1"));
}

void Window::setVisible(bool visible)
{
    restoreAction->setEnabled(isMaximized() || !visible);
    QDialog::setVisible(visible);
}

void Window::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}


void Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        pauseTrackingAction->trigger();
        restoreAction->trigger();
        QApplication::setActiveWindow(this);
        break;
    default:
        ;
    }
}

void Window::configureLayout() {
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(timeLabel);
    mainLayout->addWidget(startButton);
    mainLayout->addWidget(pauseButton);
    mainLayout->addWidget(resetTimeButton);
    setLayout(mainLayout);
}

void Window::configureActions()
{
    showAboutAction = new QAction(tr("&About"), this);
    showAboutAction->setIcon(QIcon(":/images/About.png"));
    connect(showAboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    quitAction->setIcon(QIcon(":/images/Close.png"));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));


    startTrackingAction = new QAction(tr("Start tracking"), this);
    startTrackingAction->setIcon(QIcon(":/images/Play.png"));
    connect(startTrackingAction, SIGNAL(triggered()), this, SLOT(startTracking()));

    pauseTrackingAction = new QAction(tr("Pause tracking"), this);
    pauseTrackingAction->setIcon(QIcon(":/images/Pause.png"));
    connect(pauseTrackingAction, SIGNAL(triggered()), this, SLOT(pauseTracking()));
    pauseTrackingAction->setEnabled(false);

    resetTrackedTimeAction = new QAction(tr("Reset tracking result"), this);
    connect(resetTrackedTimeAction, SIGNAL(triggered()), this, SLOT(resetTrackingResult()));
    resetTrackedTimeAction->setEnabled(false);

}

void Window::showAbout(){
    QMessageBox about;
    //about.setParent(this);
    about.setWindowTitle(tr("Hi dear!"));
    about.setText(tr("This is timetracker for <b>bananateam</b> members.<br/>"
                "Find more on "
                "<a href='https://github.com/OrelSokolov/timetracker'>GitHub</a>"
                "<i><p align='right'>Orel Sokolov, 2013</p></i>"));
    about.setIconPixmap(QPixmap(":/images/Tracker.png"));
    about.exec();
}

void Window::configureTrayIconMenu()
{
    configureActions();
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(startTrackingAction);
    trayIconMenu->addAction(pauseTrackingAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(showAboutAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
}

void Window::configureButtons(){
    timeLabel = new QLabel("<h1>Are you ready?</h1>");
    resetTimeButton = new QPushButton(tr("&Reset"));
    startButton = new QPushButton(tr("&Start"));
    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setVisible(false);
    //resetTimeButton->setVisible(false);
    connect(startButton, SIGNAL(clicked()), startTrackingAction, SLOT(trigger()));
    connect(pauseButton, SIGNAL(clicked()), pauseTrackingAction, SLOT(trigger()));
    connect(resetTimeButton, SIGNAL(clicked()), resetTrackedTimeAction, SLOT(trigger()));

}

void Window::configureTrayIcon(){
    configureTrayIconMenu();
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    QIcon icon(":/images/Tracker.png");
    trayIcon->setIcon(icon);
    setWindowIcon(icon);
    trayIcon->setToolTip("Time tracker");
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon->setVisible(true);
}

void Window::startTracking() {
    std::cout<<"Started"<<std::endl;
    this->setVisible(false);
    timer->start();
    timeLabel->setText("Working...");
    pauseTrackingAction->setEnabled(true);
    startTrackingAction->setEnabled(false);
    resetTrackedTimeAction->setEnabled(false);
    //startButton->setVisible(false);
    startButton->setText(tr("&Continue"));
    startTrackingAction->setText("Continue tracking");
}

void Window::pauseTracking() {
    startTrackingAction->setEnabled(true);
    pauseTrackingAction->setEnabled(false);
    resetTrackedTimeAction->setEnabled(true);
    time->addMiliseconds(timer->elapsed());
    timeLabel->setText(time->toH1());
    this->setVisible(true);

}

void Window::resetTrackingResult() {
    std::cout<<"reset tracking"<<std::endl;
    time->reset();
    timeLabel->setText(time->toH1());
    startButton->setText(tr("&Start"));
    startTrackingAction->setText("Start tracking");
}

