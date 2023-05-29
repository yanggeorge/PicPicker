//
// Created by 杨明 on 2023/5/29.
//

#ifndef PICKPIC_LOG_H
#define PICKPIC_LOG_H

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>

// if not define _DEBUG, logging to file
//#define _DEBUG

namespace QT_LOG {
    //default log filename
    static int m_LogLevel = 1;
    static QString m_LogFile = QString("%1.log").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    QMutex m_LogMutex;

    void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
        if (type < m_LogLevel) {
            return;
        }

        QString log_info;
        switch (type) {
            case QtDebugMsg:
                log_info = QString("%1 [Debug]").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                break;

            case QtWarningMsg:
                log_info = QString("%1 [Warning]").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                break;

            case QtCriticalMsg:
                log_info = QString("%1 [Critical]").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                break;

            case QtFatalMsg:
                log_info = QString("%1 [Fatal]").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                abort();

            case QtInfoMsg:
                log_info = QString("%1 [Info]").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                break;
        }
        QString fileName = QString(context.file).section(QDir::separator(), -1);
        if (fileName.length() > 0) {
            log_info += QString(" %1:%2 - %3").arg(fileName).arg(context.line).arg(msg);
        } else {
            log_info += QString(" - %1").arg(msg);
        }

        m_LogMutex.lock();

        QFile outFile(m_LogFile);
        outFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
        QTextStream ts(&outFile);
        ts << log_info << Qt::endl;
        outFile.flush();
        outFile.close();

        m_LogMutex.unlock();
    }

    void logInit(QString logFile = "", int logLevel = QtWarningMsg) {
#ifndef _DEBUG  // output to console when debugging, else to file
        m_LogLevel = logLevel;

        if (!logFile.isEmpty()) {
            m_LogFile = logFile;
        }
        qInstallMessageHandler(customMessageHandler);
#endif
    }
}


#endif //PICKPIC_LOG_H
