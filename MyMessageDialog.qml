import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.1 as Platform

MessageDialog {
    visible: false
    id: validateMessageDialog
    text: jsonHandler.validateText ? jsonHandler.validateText : ""
}
