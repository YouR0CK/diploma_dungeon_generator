import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtDataVisualization 1.0
import "."

Item {
    id: mainview
    width: 1280
    height: 720

    property real fontSize: 12

    Rectangle {
        id: basicRect
        anchors.fill: parent

        Text {
            id: basicText
            text: qsTr("THIS IS A TEST MESSAGE")
        }

    }
}
