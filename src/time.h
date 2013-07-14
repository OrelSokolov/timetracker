#ifndef TIME_H
#define TIME_H

#include <QString>
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

#endif // TIME_H
