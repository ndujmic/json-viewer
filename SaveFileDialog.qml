import QtQuick 2.12
import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.1 as Platform

Platform.FileDialog {
    id: saveFileDialog
    fileMode: Platform.FileDialog.SaveFile

    onAccepted: {
        jsonHandler.initHighlighter(textEdit.textDocument)
        jsonHandler.saveFile(currentFile.toString().replace("file:///", ""))
    }
}
