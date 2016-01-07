#ifndef CONFIGUREDMETHOD_H
#define CONFIGUREDMETHOD_H

#include "Parameter.h"

#include <QStringList>

struct Method {
    QString signature(bool withReturnType = false) const;
    QStringList paramNames() const;

    QString returnType() const;

    int id;
    bool isReverse;
    bool isBlocking;
    Parameter returnValue;
    QString name;
    QList<Parameter> params;
};

#endif // CONFIGUREDMETHOD_H
