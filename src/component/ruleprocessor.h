#ifndef RULEPROCESSOR_H
#define RULEPROCESSOR_H

#include <QObject>
#include "watcher.h"
class RuleProcessor
{
public:
    RuleProcessor();
    int setRule(QString& path);
    void loadRule(QString& path);
    void createDefaultRule(int option);
    QJsonArray checkRule(int n);
    int updateRule(int n, int option, QString& script_base64);
    int updateExitRule(int n, int option, QString newReval);
    void saveCurrentRule(QString& saveAs);
    int haveCurrentRule();
    QString getCurrentJson();

    QJsonObject getCurrentRules() const;

private:
    QJsonObject currentRules;
    QString currentRulePath;
};

inline int RuleProcessor::updateRule(int n, int option, QString& script_base64)
{
    QString nr = QString::number(n);
    if(Watcher::seccomp_force_enable_calls(n)) return 0;
    if(currentRules.contains(nr))
    {
        QJsonArray arr = currentRules[nr].toArray();
        if(option < 5)
        {
            arr[0] = option;
            arr[1] = QJsonValue("");
        }
        else
        {
            QByteArray qba = script_base64.toUtf8();
            QString base64code = qba.toBase64();
            //QJsonArray temp = {5, script_base64};
            arr[0] = 5;
            arr[1] = QJsonValue(base64code);
        }
        currentRules[nr] = arr;
        return 1;
    }
    else
    {
        return 0;
    }
}
inline int RuleProcessor::updateExitRule(int n, int option, QString newReval)
{
    QString nr = QString::number(n);
    if(Watcher::seccomp_force_enable_calls(n)) return 0;
    if(currentRules.contains(nr))
    {
        QJsonArray arr = currentRules[nr].toArray();
        arr[2] = option;
        if(option != JAIL_SYS_CALL_EXIT_CHANGE)
        {
            arr[3] = QJsonValue("");
        }
        else
        {
            qint64 v = newReval.toLong();
            arr[3] = QJsonValue(v);
        }
        currentRules[nr] = arr;
        return 1;
    }
    else
    {
        return 0;
    }
}
#endif // RULEPROCESSOR_H
