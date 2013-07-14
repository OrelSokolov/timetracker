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

class Time{
    public:
        Time(){
           miliseconds = 0;
        }
        void addMiliseconds(long arg){ miliseconds+=arg; }
        QTime toQTime(){
            QTime t(0,0,0);
            return t.addMSecs(miliseconds);
        };
        QString toQString() {
            return this->toQTime().toString(QString("hh:mm:ss"));
        }
        QString toH1(){ return QString("<h1>")+this->toQString()+QString("</h1>");}
        long getMiliseconds(){return miliseconds;}
        void reset() {miliseconds=0;}
    private:
        long miliseconds;
};

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
    QAction *restoreAction;
    QAction *quitAction;

    QAction *startTrackingAction;
    QAction *pauseTrackingAction;
    QAction *resetTrackedTimeAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QTime *timer;
    Time *time;
};

#endif
