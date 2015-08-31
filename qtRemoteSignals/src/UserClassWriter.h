#ifndef USERCLASSWRITER_H
#define USERCLASSWRITER_H

#include <QDir>



class UserClassWriter
{
public:
    UserClassWriter(const QString& baseName, const QDir& targetDir);
    void writeClient();
    void writeServer();
protected:
    void write(const QString& className, bool isClient);
    QString mBaseName;
    QDir mTargetDir;
};

#endif // USERCLASSWRITER_H
