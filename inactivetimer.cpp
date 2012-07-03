#include "inactivetimer.h"

int const InactiveTimer::totalTickerSteps(5);

InactiveTimer::InactiveTimer(int msecInactivityTimeout, QObject *parent = 0) :
    QObject(parent),
    inactivityTimeout(msecInactivityTimeout),
    ticker(new QTimer(this)),
    currentTicker(0)
{
    ticker->setInterval(inactivityTimeout / totalTickerSteps);
    connect(ticker, SIGNAL(timeout()), this, SLOT(tick()));
}

void InactiveTimer::startTicker()
{
    if (!ticker->isActive())
    {
        ticker->start();
    }
}

void InactiveTimer::notifyActivity()
{
    clearTickerSteps();
    startTicker();
}

void InactiveTimer::clearTickerSteps()
{
    currentTicker = 0;
}

void InactiveTimer::tick()
{
    ++currentTicker;
    if (currentTicker > totalTickerSteps)
    {
        emit inactivityDetected();
        ticker->stop();
    }
}

bool InactiveTimer::isActionPresence()
{
    return ticker->isActive();
}

void InactiveTimer::emulateInactivity()
{
    emit inactivityDetected();
    ticker->stop();
}
