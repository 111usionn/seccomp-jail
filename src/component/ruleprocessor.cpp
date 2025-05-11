#include "ruleprocessor.h"

RuleProcessor::RuleProcessor() {}

int RuleProcessor::setRule(QString &path)
{
    if(path.isEmpty())
    {
        return 0;
    }
    QUrl rule_url(path);
    QString localPath = rule_url.toLocalFile();
    loadRule(localPath);
    return 1;
}

void RuleProcessor::loadRule(QString &path)
{
    qDebug() << "loadRule()";
    QFile file(path);
    file.open(QFile::ReadOnly);
    QByteArray json = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(json);
    currentRules = doc.object();
    currentRulePath = path;
}

void RuleProcessor::createDefaultRule(int option)
{
    QFile file("./default.json");
    QJsonObject table;
    QString temp;
    for(int i = 0; i <= 453; i++)
    {
        temp = QString::number(i);
        QJsonArray temparr;
        temparr.append(QJsonValue(""));
        temparr.append(QJsonValue(""));
        temparr.append(QJsonValue(0));
        temparr.append(QJsonValue(""));
        if(!Watcher::seccomp_force_enable_calls(i))
        {
            temparr[0] = QJsonValue(option);
            table.insert(temp, temparr);
        }
        else
        {
            temparr[0] = QJsonValue(JAIL_SYS_CALL_PASS_FOREVER);
            table.insert(temp, temparr);
        }
    }
    QJsonDocument doc(table);
    QByteArray json = doc.toJson();
    if(!file.open(QFile::WriteOnly | QFile::Truncate))file.open(QFile::WriteOnly);
    file.write(json);
    file.close();
}

QJsonArray RuleProcessor::checkRule(int n)
{
    QString key;
    key = QString::number(n);
    if(currentRules.contains(key))
    {
        QJsonValue val = currentRules.value(key);
        if(val.isArray())
        {
            return val.toArray();
        }
    }
    QJsonValue val = JAIL_SYS_CALL_ABORT_FOREVER;
    QJsonArray arr;
    arr.append(val);
    arr.append(QJsonValue(""));
    arr.append(QJsonValue(0));
    arr.append(QJsonValue(""));
    return arr;
}

void RuleProcessor::saveCurrentRule(QString& saveAs)
{
    if(saveAs.isEmpty())//save
    {
        QFile file(currentRulePath);
        QJsonDocument doc(currentRules);
        QByteArray json = doc.toJson();
        if(!file.open(QFile::WriteOnly | QFile::Truncate))file.open(QFile::WriteOnly);
        file.write(json);
        file.close();
    }
    else//save as
    {
        QUrl rule_url(saveAs);
        QString localPath = rule_url.toLocalFile();
        QFile file(localPath);
        QJsonDocument doc(currentRules);
        QByteArray json = doc.toJson();
        if(!file.open(QFile::WriteOnly | QFile::Truncate))file.open(QFile::WriteOnly);
        file.write(json);
        file.close();
    }
}

int RuleProcessor::haveCurrentRule()
{
    return !currentRules.isEmpty();
}

QString RuleProcessor::getCurrentJson()
{
    QJsonObject filteredRules = currentRules;
    QJsonDocument doc(filteredRules);
    QByteArray t = doc.toJson();
    return QString(t);
}

QJsonObject RuleProcessor::getCurrentRules() const
{
    return currentRules;
}
