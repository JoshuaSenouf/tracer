import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

import QtGraphicalEffects 1.13

import viewport 1.0

Item
{
    id: root
    focus: true

    width: 1280
    height: 720

    MenuBar
    {
        id: menubar
        width: parent.width

        Menu
        {
            title: "File"

            Action
            {
                text: "Open..."
            }
            
            MenuSeparator {}

            Action
            {
                text: "Quit"
            }
        }
        Menu
        {
            title: "I/O"

            Action
            {
                text: "Export to..."
            }
            Action
            {
                text: "Render to..."
            }
        }
        Menu
        {
            title: "Help"

            Action
            {
                text: "&About"
            }
        }

        layer.enabled: true
        layer.effect: DropShadow
        {
            color: "#aa000000"
            transparentBorder: true
            verticalOffset: 1
        }
    }

    SplitView
    {
        id: splitHorizontal
        anchors.fill: parent
        anchors.topMargin: menubar.contentHeight + 5
        orientation: Qt.Horizontal

        Rectangle
        {
            id: scenegraphRect
            implicitWidth: 250
            SplitView.minimumWidth: 200
            color: "lightblue"

            Label
            {
                text: "Scene Graph"
                anchors.centerIn: parent
            }
        }

        SplitView
        {
            id: splitVertical
            orientation: Qt.Vertical
            SplitView.minimumWidth: 250
            SplitView.fillWidth: true

            Viewport
            {
                id: viewport
                SplitView.minimumWidth: 250
                SplitView.minimumHeight: 250
                SplitView.fillHeight: true
            }

            Rectangle
            {
                id: loggerRect
                implicitHeight: 250
                SplitView.minimumWidth: 100
                SplitView.minimumHeight: 200
                color: "lightgray"

                Label
                {
                    text: "Logger"
                    anchors.centerIn: parent
                }
            }
        }

        Rectangle
        {
            id: renderconfigRect
            implicitWidth: 250
            SplitView.minimumWidth: 200
            color: "lightgreen"

            Label
            {
                text: "Render Config"
                anchors.centerIn: parent
            }
        }
    }
}
