#include "inactivetimer.h"
#include <QTimer>

float const InactiveTimer::inactivityTimerQtCorrection(1.005);

InactiveTimer::InactiveTimer(int msecInactivityTimeout, QObject *parent = 0) :
    QObject(parent),
    inactivityTimeout(msecInactivityTimeout),
    lastActivityDateTime(QDateTime::currentDateTime())
{
}

void InactiveTimer::notifyActivity()
{
    lastActivityDateTime = QDateTime::currentDateTime();
    startTimer();
}

void InactiveTimer::startTimer()
{
    QTimer::singleShot(static_cast<int>(inactivityTimeout * inactivityTimerQtCorrection),
                       this, SLOT(checkInactivity()));
}

void InactiveTimer::checkInactivity()
{
    if (lastActivityDateTime.msecsTo(QDateTime::currentDateTime()) > inactivityTimeout)
    {
        emit inactivityDetected();
    }
}
