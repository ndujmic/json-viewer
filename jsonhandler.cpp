#include "jsonhandler.h"
#include "jsonhighlighter.h"
#include <exception>
#include <QDebug>
#include <QJsonParseError>
#include <QIODevice>

JsonHandler::JsonHandler()
{

}

void JsonHandler::initHighlighter(QQuickTextDocument *textDoc)
{
    JSONHighlighter *jsonHighlighter = new JSONHighlighter(textDoc->textDocument());
}

void JsonHandler::validateJsonStruct()
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDoc;
    QString offsetMessage;
    QString errorMessage;

    jsonDoc = QJsonDocument::fromJson(m_textFile.toUtf8(), &jsonParseError);

    if (jsonParseError.error == QJsonParseError::NoError) {
        offsetMessage = QString("");
    } else {
        offsetMessage = QString(" at character ").append(QString::number(jsonParseError.offset));
    }

    switch(jsonParseError.error) {
        case 0:
            errorMessage = QString("No error occurred");
            break;
        case 1:
            errorMessage = QString("There is a curly bracket missing");
            break;
        case 2:
            errorMessage = QString("There is a comma separator missing");
            break;
        case 3:
            errorMessage = QString("The array is not correctly terminated");
            break;
        case 4:
            errorMessage = QString("There is a colon separator missing");
            break;
        case 5:
            errorMessage = QString("The value is illegal");
            break;
        case 6:
            errorMessage = QString("There is illegal number at the end");
            break;
        case 7:
            errorMessage = QString("The number is not well formed");
            break;
        case 8:
            errorMessage = QString("Illegal escape sequence");
            break;
        case 9:
            errorMessage = QString("Illegal UTF8 sequence");
            break;
        case 10:
            errorMessage = QString("A string wasn't terminated with a quote");
            break;
        case 11:
            errorMessage = QString("An object was expected but couldn't be found");
            break;
        case 12:
            errorMessage = QString("The JSON document is too deeply nested for the parser to parse it");
            break;
        case 13:
            errorMessage = QString("The JSON document is too large for the parser to parse it");
            break;
        case 14:
            errorMessage = QString("The parsed document contains additional garbage characters at the end");
            break;
        default:
            errorMessage = QString("There was an unspecified error");

    }

    setvalidateText(errorMessage.append(offsetMessage));
}

void JsonHandler::saveFile(QString file)
{
    setfileName(file);
    QFile save_file(file);
    save_file.open(QFile::WriteOnly);
    save_file.write(textFile().toUtf8());
    save_file.close();
}

QString JsonHandler::fileContentAsString()
{
    QFile fileContent(m_fileName);

    QString fileToReturn = "";
    fileContent.setFileName(m_fileName);
    if (fileContent.exists()) {
        if (fileContent.open(QIODevice::ReadOnly | QIODevice::Text)) {
            fileToReturn = fileContent.readAll();
        }
    }
    else {
    }
    fileContent.close();
    return fileToReturn;
}
