import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.1 as Platform

Item {
    id: window
    width: {
       parent.width ? parent.width : 640
    }
    height: {
        parent.height ? parent.height : 480
    }
    visible: true
    clip: true   

        Button {
            id: loadFileButton
            text: "Load File"

            onClicked: loadFileDialog.open();

            anchors {
                left: window.left
                leftMargin: 2
                bottomMargin: 4
            }
        }
        Button {
            id: newFileButton
            text: "New File"

            anchors {
                left: loadFileButton.right
                leftMargin: 2
                bottomMargin: 4
            }

            onClicked: {
                textEdit.clear()
                saveFileDialog.open()
            }
        }
        Button {
            id: fromUrlButton
            text: "From URL"

            onClicked: restButtonDialog.open()

            anchors {
                left: newFileButton.right
                leftMargin: 2
                bottomMargin: 4
            }
        }

        Rectangle {
            id: rectangle
            border {
                color: "black"
            }

            width: window.width - saveAsButton.width
            height: window.height - loadFileButton.height

            anchors {
                left: window.left
                bottom: window.bottom
                right: saveAsButton.left
                top: fromUrlButton.bottom
                leftMargin: 2
                topMargin: 2
                bottomMargin: 2
                rightMargin: 2
            }

            Flickable {
                  id: flick
                  width: rectangle.width
                  height: rectangle.height

                  contentWidth: textEdit.paintedWidth
                  contentHeight: textEdit.paintedHeight
                  clip: true

                  anchors {
                      left: parent.left
                      bottom: parent.bottom
                      leftMargin: 0
                      bottomMargin: 0
                  }

                  function ensureVisible(r) {
                      if (contentX >= r.x)
                          contentX = r.x;
                      else if (contentX+width <= r.x+r.width)
                          contentX = r.x+r.width-width;
                      if (contentY >= r.y)
                          contentY = r.y;
                      else if (contentY+height <= r.y+r.height)
                          contentY = r.y+r.height-height;
                  }
                  ScrollView {
                      width: rectangle.width
                      height: rectangle.height
                      ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                      TextEdit {
                          id: textEdit
                          text: ""
                          width: flick.width
                          wrapMode: Text.WrapAtWordBoundaryOrAnywhere

                          selectByMouse: true
                          selectByKeyboard: true
                          cursorVisible: true

                          textMargin: 1.5
                          font {
                              pixelSize: 15
                              family: "Courier"

                          }
                          tabStopDistance: 15

                          clip: true

                          onTextChanged: {
                              textEdit.text = text
                              jsonHandler.textFile = text
                          }
                      }
            }

        }}

        Button {
            id: saveButton
            text: "Save"

            onClicked: {
                if (jsonHandler.fileName) {
                    jsonHandler.saveFile(jsonHandler.fileName)
                } else {
                    saveFileDialog.open()
                }
            }

            anchors {
                bottom: saveAsButton.top
                right: window.right
                bottomMargin: 2
            }
        }
        Button {
            id: saveAsButton
            text: "Save As"

            anchors {
                bottom: validateButton.top
                right: window.right
                bottomMargin: 2
            }

            onClicked: saveFileDialog.open()
        }
        Button {
            id: validateButton
            text: "Validate"

            onClicked: {
                jsonHandler.initHighlighter(textEdit.textDocument)
                jsonHandler.validateJsonStruct()
                validateMessageDialog.open()
            }

            anchors {
                right: window.right
                bottom: window.bottom
                bottomMargin: 2
            }
        }

    FromUrlDialog {
        id: restButtonDialog
    }
    MyMessageDialog {
        id: validateMessageDialog
    }
    LoadFileDialog {
        id: loadFileDialog
    }
    SaveFileDialog {
        id: saveFileDialog
    }
}
