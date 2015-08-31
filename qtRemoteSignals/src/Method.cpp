#include "Method.h"


QString Method::signature() const
{
    QString sig;
    sig += name;
    sig += "(";
    QStringList paramSigs;
    foreach (const Parameter &param, params)
        paramSigs << param.signature();
    sig += paramSigs.join(", ");
    sig += ")";
    return sig;
}

QStringList Method::paramNames() const
{
    QStringList names;
    foreach (const Parameter &param, params)
        names << param.name;
    return names;
}

QString Method::returnType() const
{
    if (returnValue.name.isEmpty())
        return "void";
    else
        return returnValue.name;
}
