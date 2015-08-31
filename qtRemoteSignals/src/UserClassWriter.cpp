#include "UserClassWriter.h"

#include <QTextStream>

UserClassWriter::UserClassWriter(const ConfigFileReader &parser,
                                 const QString &baseName, const QDir &targetDir)
    : mParser(parser)
{
    mBaseName = baseName;
    mTargetDir = targetDir;
}

void UserClassWriter::writeClient() { write(mBaseName + "Client", true); }

void UserClassWriter::writeServer() { write(mBaseName + "Server", false); }

void UserClassWriter::write(const QString &className, bool isClient)
{
    QFileInfo fileInfo(mTargetDir.absoluteFilePath(className + ".h"));
    if (!fileInfo.exists()) {
        QFile file(fileInfo.absoluteFilePath());
        file.open(QFile::WriteOnly);
        QTextStream stream(&file);
        stream << "#ifndef " + className.toUpper() + "_H" << endl;
        stream << "#define " + className.toUpper() + "_H" << endl;
        stream << "#include \"" + className + "Base.h\"" << endl
               << endl;
        stream << "class " + className + " : public " + className + "Base"
               << endl;
        stream << "{" << endl
               << "public:" << endl;
        if (isClient) {
            stream << "\t" << className
                   << "(QIODevice* writeDevice, QIODevice* "
                      "readDevice = 0, bool initialize = "
                      "false)" << endl;
            stream << "\t\t:" << className
                   << "Base(writeDevice, readDevice, initialize) {}" << endl;
        } else {
            stream << "\t" << className << "(QIODevice* readDevice, QIODevice* "
                                           "writeDevice = 0, bool initialize = "
                                           "false)" << endl;
            stream << "\t\t:" << className
                   << "Base(readDevice, writeDevice, initialize) {}" << endl << endl;
            // abstract methods
            foreach(const Method& method, mParser.methods())
            {
                if(!method.isReverse && method.isBlocking)
                {
                    stream << "\tvirtual " << method.signature(true) << "{" << endl;
                    stream << "\t\t#error User implementation needed" << endl;
                    stream << "\t}" << endl;
                }
            }
        }

        stream << "};" << endl;
        stream << "#endif // " + className.toUpper() + "_H" << endl;
    }
}
