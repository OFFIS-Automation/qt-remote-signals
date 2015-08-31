#include "ConfigFileReader.h"

#include <QTextStream>
#include <QCryptographicHash>
#include <QDebug>
#include <QFile>
#include <QFileInfo>

ConfigFileReader::ConfigFileReader()
{

}

void ConfigFileReader::parse(const QString& definitionFile)
{
    mLastModified= QFileInfo(definitionFile).lastModified();
    QFile file(definitionFile);
    file.open(QFile::ReadOnly);
    QTextStream stream(&file);
    QByteArray hashData;
    while (!stream.atEnd()) {
        QString line = stream.readLine().trimmed();
        if (line.isEmpty() || line.startsWith('/'))
            continue;
        hashData.append(line.toLocal8Bit());
        if (line.startsWith("#include")) {
            line.replace("#include", "");
            mIncludes << line.trimmed();
        } else
            mMethods << parseLine(line);
    }
    QByteArray hash =
        QCryptographicHash::hash(hashData, QCryptographicHash::Md5).toHex();
    mId.id1 = hash.mid(0, 15).toULongLong(0, 16);
    mId.id2 = hash.mid(16).toULongLong(0, 16);
    qWarning() << "Found " << mMethods.size() << " methods. ID:"
               << QString("0x%1%2").arg(mId.id1, 16).arg(mId.id2, 16);
    file.close();
}

quint64 ConfigFileReader::createId(const QList<Method> &methods)
{
    quint64 numMethods = methods.size();
    quint64 numParams = 0;
    quint64 numChars = 0;
    foreach (const Method &method, methods) {
        numChars += method.signature().length();
        numParams += method.params.size();
    }
    quint64 part1 = 100000 * numMethods + numParams;
    part1 = part1 << 32;
    return part1 | numChars;
}

Parameter ConfigFileReader::createParameter(QString param)
{
    QStringList basicTypes;
    basicTypes << "int"
               << "uint"
               << "short"
               << "ushort"
               << "char"
               << "uchar"
               << "long"
               << "ulong"
               << "quint64"
               << "qint64";
    Parameter paramType;
    param = param.trimmed();
    param.replace("unsigned long long", "quint64");
    param.replace("long long", "qint64");
    param.replace("unsigned ", "u");

    int split = param.lastIndexOf(' ');
    paramType.name = param.mid(split + 1).trimmed();
    paramType.type = param.mid(0, split).trimmed();
    paramType.isBasic = basicTypes.contains(paramType.type);
    return paramType;
}

Method ConfigFileReader::parseLine(const QString &line)
{
    static int id = 1;
    Method method;
    method.id = id++;
    int start = line.indexOf('(');
    int end = line.indexOf(')');
    method.name = line.mid(0, start);
    method.isReverse = false;
    method.isBlocking = false;
    if (method.name.startsWith("signal ")) {
        method.name.remove(0, 7);
    } else if (method.name.startsWith("slot ")) {
        method.isReverse = true;
        method.name.remove(0, 5);
    } else if (method.name.startsWith('-')) // DEPRECATED
    {
        method.isReverse = true;
        method.name.remove(0, 1);
    } else if (method.name.contains(" ")) {
        int space = method.name.lastIndexOf(' ');
        method.returnValue = createParameter(method.name.mid(0, space));
        method.name = method.name.mid(space + 1);
        method.isBlocking = true;
    }

    QString paramsLine = line.mid(start + 1, end - start - 1);
    QStringList params = paramsLine.split(",", QString::SkipEmptyParts);
    QString prebuffer = "";
    foreach (QString param, params) {

        param = param.trimmed();
        if (param.isEmpty())
            continue;
        param = prebuffer + param;
        prebuffer = "";
        if (param.count("<") > param.count(">")) {
            prebuffer = param + ", ";
            continue;
        }

        method.params << createParameter(param);
    }
    return method;
}

