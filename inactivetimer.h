#ifndef INACTIVETIMER_H
#define INACTIVETIMER_H

#include <QObject>
#include <QDateTime>

class InactiveTimer : public QObject
{
    Q_OBJECT
public:
    explicit InactiveTimer(int msecInactivityTimeout, QObject *parent);
    void notifyActivity();

public slots:
    void startTimer();

signals:
    void inactivityDetected();

private:
    int inactivityTimeout;
    QDateTime lastActivityDateTime;
    float static const inactivityTimerQtCorrection;

private slots:
    void checkInactivity();

};

#endif // INACTIVETIMER_H
