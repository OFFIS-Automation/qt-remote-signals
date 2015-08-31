#ifndef USERCLASSWRITER_H
#define USERCLASSWRITER_H

#include <QDir>

#include "ConfigFileReader.h"

class UserClassWriter
{
public:
    UserClassWriter(const ConfigFileReader& parser, const QString& baseName, const QDir& targetDir);
    void writeClient();
    void writeServer();
protected:
    void write(const QString& className, bool isClient);
    const ConfigFileReader& mParser;
    QString mBaseName;
    QDir mTargetDir;
};

#endif // USERCLASSWRITER_H
