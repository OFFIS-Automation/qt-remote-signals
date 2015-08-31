#ifndef BASECLASSWRITER_H
#define BASECLASSWRITER_H

#include "ConfigFileReader.h"

#include <QDir>
#include <QTextStream>



class BaseClassWriter
{
public:
    BaseClassWriter(const ConfigFileReader &parser, const QString& baseName, const QDir& targetDir);
    void writeClient(bool skipDateCheck = false);
    void writeServer(bool skipDateCheck = false);
protected:
    bool needsGeneration(const QString& className);

    void writeHeader(const QString &className, bool isClient);
    void writeImplementation(const QString &className, bool isClient);
    void writeMethod(QTextStream &stream, Method method, QString ns);
    void writeMethodParsing(QTextStream &stream, Method method);
    void methodSendStaticStart(QTextStream &stream, int methodId, int numtabs = 1);

protected:
    const ConfigFileReader &mParser;
    QString mClassName;
    QDir mTargetDir;
};

#endif // BASECLASSWRITER_H
