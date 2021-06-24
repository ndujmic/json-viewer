import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.1 as Platform

Platform.FileDialog {
    id: loadFileDialog
    title: "Open File"
    nameFilters: [ "JSON files (*.json)" ]
    onAccepted: {
        jsonHandler.fileName = loadFileDialog.currentFile.toString().replace("file:///", "");
        textEdit.text = jsonHandler.textFile;
        jsonHandler.initHighlighter(textEdit.textDocument)
    }
}
