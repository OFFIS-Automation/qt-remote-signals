#ifndef CONFIGFILEREADER_H
#define CONFIGFILEREADER_H

#include "Method.h"

#include <QDateTime>
#include <QString>

class ConfigFileReader
{
public:
    struct ID {
        quint64 id1;
        quint64 id2;
    };

    ConfigFileReader();
    void parse(const QString &definitionFile);
    ID id() const { return mId; }
    const QList<Method>& methods() const { return mMethods; }
    const QList<QString>& includes() const { return mIncludes; }
    const QDateTime& lastConfigUpdate() const { return mLastModified; }
protected:
    quint64 createId(const QList<Method> &methods);
    Parameter createParameter(QString param);
    Method parseLine(const QString &line);
    QList<Method> mMethods;
    QList<QString> mIncludes;
    ID mId;
    QDateTime mLastModified;
};

#endif // CONFIGFILEREADER_H
