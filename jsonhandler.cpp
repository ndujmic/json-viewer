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
    QHash<QString, int> jsonErrorHash;

    jsonDoc = QJsonDocument::fromJson(m_textFile.toUtf8(), &jsonParseError);

    qDebug() << jsonParseError.error;

    if (jsonParseError.error == QJsonParseError::NoError) {
        setvalidateText(QString("No error"));
    } else if (jsonParseError.error == QJsonParseError::UnterminatedObject) {
        setvalidateText(QString("There is a curly bracket missing at character ").append(QString::number(jsonParseError.offset)));
    } else if (jsonParseError.error == QJsonParseError::MissingNameSeparator) {
        setvalidateText(QString("There is a comma separator missing at character ").append(QString::number(jsonParseError.offset)));
    } else if (jsonParseError.error == QJsonParseError::UnterminatedArray) {
        setvalidateText(QString("The array is not correctly terminated at character ").append(QString::number(jsonParseError.offset)));
    } else if (jsonParseError.error == QJsonParseError::MissingValueSeparator) {
        setvalidateText(QString("There is a colon separator missing at character ").append(QString::number(jsonParseError.offset)));
    } else if (jsonParseError.error == QJsonParseError::IllegalValue) {
        setvalidateText(QString("The value is illegal at character ").append(QString::number(jsonParseError.offset)));
    } else if (jsonParseError.error == QJsonParseError::TerminationByNumber) {
        setvalidateText(QString("There illegal number at the end at character ").append(QString::number(jsonParseError.offset)));
    } else if (jsonParseError.error == QJsonParseError::IllegalNumber) {
        setvalidateText(QString("The number is not well formed at character ").append(QString::number(jsonParseError.offset)));
    } else if (jsonParseError.error == QJsonParseError::IllegalEscapeSequence) {
        setvalidateText(QString("Illegal escape sequence at character ").append(QString::number(jsonParseError.offset)));
    } else if (jsonParseError.error == QJsonParseError::IllegalUTF8String) {
        setvalidateText(QString("Illegal UTF8 sequence at character ").append(QString::number(jsonParseError.offset)));
    } else if (jsonParseError.error == QJsonParseError::UnterminatedString) {
        setvalidateText(QString("A string wasn't terminated with a quote at character ").append(QString::number(jsonParseError.offset)));
    } else if (jsonParseError.error == QJsonParseError::MissingObject) {
        setvalidateText(QString("An object was expected but couldn't be found at character ").append(QString::number(jsonParseError.offset)));
    } else if (jsonParseError.error == QJsonParseError::DeepNesting) {
        setvalidateText(QString("The JSON document is too deeply nested for the parser to parse it."));
    } else if (jsonParseError.error == QJsonParseError::DocumentTooLarge) {
        setvalidateText(QString("The JSON document is too large for the parser to parse it."));
    } else if (jsonParseError.error == QJsonParseError::GarbageAtEnd) {
        setvalidateText(QString("The parsed document contains additional garbage characters at the end."));
    } else {
        setvalidateText(QString("There was an unspecified error."));
    }
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
