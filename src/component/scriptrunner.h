#ifndef SCRIPTRUNNER_H
#define SCRIPTRUNNER_H
#include "global.h"
class ScriptRunner
{
public:
    ScriptRunner();
    int run(int pid, seccomp_data& data, QList<QString>& dargs, QString user_script);
};

#endif // SCRIPTRUNNER_H
