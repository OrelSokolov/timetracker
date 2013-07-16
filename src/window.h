#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>
#include <QDialog>
#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QTime>
#include "time.h"


class Window : public QDialog
{
    Q_OBJECT

public:
    Window();

    void setVisible(bool visible);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showAbout();
    void showResult();

    void startTracking();
    void pauseTracking();
    void resetTrackingResult();

private:
    void configureActions();
    void configureTrayIcon();
    void configureTrayIconMenu();
    void configureLayout();
    void configureButtons();

    QLabel *timeLabel;
    QPushButton *resetTimeButton;
    QPushButton *startButton;
    QPushButton *pauseButton;

    QAction *showAboutAction;
    QAction *showResultAction;
    QAction *quitAction;

    QAction *startTrackingAction;
    QAction *pauseTrackingAction;
    QAction *resetTrackedTimeAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QTime *timer;
    Time *time;

    QIcon pauseIcon;
    QIcon playIcon;
    QIcon aboutIcon;
    QIcon logoIcon;
};

#endif
