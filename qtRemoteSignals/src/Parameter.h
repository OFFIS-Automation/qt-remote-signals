#ifndef PARAMETER
#define PARAMETER

#include <QString>

struct Parameter {
    QString name;
    QString type;
    bool isBasic;
    QString signature() const
    {
        if (isBasic){
            return QString("%1 %2").arg(type, name);
        } else {
            return QString("const %1& %2").arg(type, name);
        }
    }
};

#endif // PARAMETER

