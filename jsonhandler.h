#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QObject>
#include <QQuickTextDocument>
#include <QDebug>
#include <QString>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class JsonHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString textFile READ textFile WRITE setTextFile NOTIFY textFileChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setfileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString validateText READ validateText WRITE setvalidateText NOTIFY validateTextChanged)



public:
    JsonHandler();
    Q_INVOKABLE void initHighlighter(QQuickTextDocument* textDoc);
    Q_INVOKABLE void saveFile(QString file);
    Q_INVOKABLE void validateJsonStruct();

    QString fileName() const
    {
        return m_fileName;
    }

    QString textFile() const
    {
        return m_textFile;
    }

    QString validateText() const
    {
        return m_validateText;
    }

public slots:

    void setfileName(QString fileName)
    {
        if (m_fileName == fileName)
            return;

        m_fileName = fileName;
        setTextFile(get_loaded_file());
        emit fileNameChanged(m_fileName);
    }

    void setTextFile(QString textFile)
    {
        if (m_textFile == textFile)
            return;

        m_textFile = textFile;
        emit textFileChanged(m_textFile);
    }

    void setvalidateText(QString validateText)
    {
        if (m_validateText == validateText)
            return;

        m_validateText = validateText;
        emit validateTextChanged(m_validateText);
    }

signals:
    void fileNameChanged(QString fileName);

    void textFileChanged(QString textFile);

    void validateTextChanged(QString validateText);

private:
    QString get_loaded_file();

    QString m_fileName;
    QString m_textFile;
    void initHighlighter();
    QString m_validateText;

    //JSON from REST API
    QNetworkAccessManager * networkManager = new QNetworkAccessManager();
    QNetworkReply * networkReply;
    QByteArray * mDataBuffer;
};

#endif // JSONHANDLER_H
