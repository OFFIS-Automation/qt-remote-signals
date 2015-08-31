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
    void writeRunnables(QTextStream &stream, const QString &className);
    void writeMethod(QTextStream &stream, Method method, QString ns);
    void writeMethodParsing(QTextStream &stream, Method method, const QString &className);
    void methodSendStaticStart(QTextStream &stream, int methodId, int numtabs = 1);
    void writeRunnableInvoking(QTextStream& stream, const Method& method);
    void writeSignalEmit(QTextStream& stream, const Method& method);
protected:
    const ConfigFileReader &mParser;
    QString mClassName;
    QDir mTargetDir;
};

#endif // BASECLASSWRITER_H
