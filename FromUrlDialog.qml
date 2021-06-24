import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.1 as Platform

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
