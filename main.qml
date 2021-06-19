import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.1 as Platform
import com.company.json 1.0

Item {
    id: window
    width: 640
    height: 480
    visible: true

    MessageDialog {
        visible: false
        id: validateMessageDialog
        text: jsonHandler.validateText
    }

    Dialog {
        id: restButtonDialog
        visible: false
        title: "Enter the url"
        // @disable-check M16
        standardButtons: StandardButton.Ok | StandardButton.Cancel

        onAccepted: {
            function get_url_request(url, callback) {
                    var http_request = new XMLHttpRequest();
                    http_request.onreadystatechange = (function(myxhr) {
                        return function() {
                            callback(myxhr);
                        }
                    })(http_request);
                    http_request.open('GET', url, true);
                    http_request.send('');
                }
            get_url_request(urlTextArea.text, function (resp) {
                textEdit.text = resp.responseText
                jsonHandler.initHighlighter(textEdit.textDocument)
            });
        }

        TextArea {
            id: urlTextArea
            placeholderText: "Your URL goes here!"
        }
    }

    Platform.FileDialog {
        id: loadFileDialog
        title: "Open File"
        nameFilters: [ "JSON files (*.json)" ]
        onAccepted: {

            console.log("Accepted: " + loadFileDialog.currentFile);

            jsonHandler.fileName = loadFileDialog.currentFile.toString().replace("file:///", "");
            textEdit.text = jsonHandler.textFile;
            jsonHandler.initHighlighter(textEdit.textDocument)
        }
        onRejected: { console.log("Rejected") }
    }

    Platform.FileDialog {
        id: saveFileDialog
        fileMode: Platform.FileDialog.SaveFile

        onAccepted: {
            jsonHandler.saveFile(currentFile.toString().replace("file:///", ""))
        }
    }

    ColumnLayout {
        id: topBottomColumn
        width: window.width * 0.9
        height: window.height * 0.9
        RowLayout {
            id: topButtonRow
            Layout.alignment: Qt.AlignTop
            width: topBottomColumn.width * 0.2
            height: topBottomColumn.height * 0.2

            Button {
                id: loadFileButton
                width: topButtonRow.width / 3
                text: "Load File"
                onClicked: loadFileDialog.open();
            }
            Button {
                id: newFileButton
                width: topButtonRow.width / 3
                text: "New File"
            }
            Button {
                id: fromUrlButton
                width: topButtonRow / 3
                text: "From URL"
                onClicked: restButtonDialog.open()
            }
        }

        RowLayout {
            id: textAndRightButtons
            Layout.alignment: Qt.AlignBottom
            width: topBottomColumn.width * 0.8
            height: topBottomColumn.height * 0.8

            Rectangle {
                id: rectangle
                anchors.left: parent.left

                Layout.alignment: Qt.AlignLeft
                height: textAndRightButtons.height
                width: textAndRightButtons.width * 0.7
                border {
                    color: "black"
                }

                Flickable {
                      id: flick

//                      width: 300; height: 200;
                      anchors.left: rectangle.left

                      width: rectangle.width
                      height: rectangle.height
                      contentWidth: textEdit.paintedWidth
                      contentHeight: textEdit.paintedHeight
                      clip: true

                      function ensureVisible(r)
                      {
                          if (contentX >= r.x)
                              contentX = r.x;
                          else if (contentX+width <= r.x+r.width)
                              contentX = r.x+r.width-width;
                          if (contentY >= r.y)
                              contentY = r.y;
                          else if (contentY+height <= r.y+r.height)
                              contentY = r.y+r.height-height;
                       }
                      TextEdit {
                          id: textEdit
                          text: ""
                          width: flick.width
                          font.pixelSize: 14
                          wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                          selectByMouse: true
                          selectByKeyboard: true

                          clip: true

                          onTextChanged: {
                              textEdit.text = text
                              jsonHandler.textFile = text
                          }
                      }
                }

            }

            ColumnLayout {
                anchors.right: parent.right
                id: leftButtons
                Layout.alignment: Qt.AlignBottom
                width: textAndRightButtons.width * 0.3

                Button {
                    id: saveButton
                    text: "Save"
                    onClicked: saveFileDialog.open()
                }
                Button {
                    id: saveAsButton
                    text: "Save As"
                }
                Button {
                    id: validateButton
                    text: "Validate"
                    onClicked: {
                        jsonHandler.validateJsonStruct()
                        validateMessageDialog.open()
                    }
                }
            }
        }
    }
}
