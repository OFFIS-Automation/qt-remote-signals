// OFFIS Automation Framework
// Copyright (C) 2013-2014 OFFIS e.V.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http:#www.gnu.org/licenses/>.

#include <QCoreApplication>

#include "Method.h"
#include "ConfigFileReader.h"
#include "BaseClassWriter.h"
#include "UserClassWriter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();
    if (args.size() < 3) {
        QTextStream(stdout) << "Usage: RemoteSignals definitionFile "
                               "codeTargetDir [--server-only|--client-only] "
                               "[--force]" << endl;
        return 1;
    }
    QString definitionFile = args[1];
    QDir targetDir(args[2]);
    QStringList params;
    for (int i = 3; i < args.size(); i++)
        params << args[i];

    QString className = QFileInfo(definitionFile).baseName();
    ConfigFileReader parser;
    parser.parse(definitionFile);
    BaseClassWriter baseWriter(parser, className, targetDir);
    UserClassWriter userWriter(parser, className, targetDir);
    if (!params.contains("--server-only")) {
        baseWriter.writeClient(params.contains("--force"));
        userWriter.writeClient();
    }
    if (!params.contains("--client-only")) {
        baseWriter.writeServer(params.contains("--force"));
        userWriter.writeServer();
    }

    QDir srcDir(a.applicationDirPath());
    QFile::remove(targetDir.absoluteFilePath("RemoteSignals.h"));
    QFile::remove(targetDir.absoluteFilePath("RemoteSignals.cpp"));
    QFile::copy(srcDir.absoluteFilePath("RemoteSignals.h"),
                targetDir.absoluteFilePath("RemoteSignals.h"));
    QFile::copy(srcDir.absoluteFilePath("RemoteSignals.cpp"),
                targetDir.absoluteFilePath("RemoteSignals.cpp"));
    return 0;
}
