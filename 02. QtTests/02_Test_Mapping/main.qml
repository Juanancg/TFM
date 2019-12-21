import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
//import "./Triangle.qml"

Item {
    id: main
    visible: true
    width: 1000
    height: 720


    property int pos_x_pedida: 0
    property int pos_y_pedida: 0
    property int pos_x: 0
    property int pos_y: 0
    property int delta_x: 0
    property int delta_y: 0
    property int angle: 0
    property int total_steps: 0
    property int step: 0
    property var array_pos
    property bool b_start: false
    property bool state_machine: false


    Rectangle {
        id: map
        x: 192
        y: 28
        width: 782
        height: 522
        color: "#e1f5fe"
        radius: 1
        border.color: "#0277bd"
        border.width: 7
        Component.onCompleted: {
            dataMovement.set_map_coordinates(8, 8, map.width - 33, map.height - 38);
            console.log("Completed Running!")
        }

        Image {
            id: triangle
            rotation: 0
            width: 25
            height: 30
            x: 467
            y: 362
            source: "/images/triangle.png"
        }
    }

    Rectangle {
        id: posicionDeseada
        x: 26
        y: 28
        width: 140
        height: 151
        color: "#ffffff"
        radius: 8
        border.color: "#0277bd"
        border.width: 4

        Text {
            id: elementX
            y: 11
            text: qsTr("X:")
            anchors.verticalCenter: textFieldX.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 20
            font.pixelSize: 18
        }

        TextField {
            id: textFieldX
            height: 27
            text: qsTr("0")
            font.pointSize: 10
            anchors.top: parent.top
            anchors.topMargin: 18
            anchors.left: elementX.right
            anchors.leftMargin: 12
            anchors.right: parent.right
            anchors.rightMargin: 20
        }

        TextField {
            id: textFieldY
            height: 27
            text: qsTr("0")
            font.pointSize: 10
            anchors.top: textFieldX.bottom
            anchors.topMargin: 18
            anchors.right: textFieldX.right
            anchors.rightMargin: 0
            anchors.left: textFieldX.left
            anchors.leftMargin: 0
        }

        Text {
            id: elementY
            y: 56
            text: qsTr("Y:")
            anchors.verticalCenter: textFieldY.verticalCenter
            anchors.left: elementX.left
            anchors.leftMargin: 0
            font.pixelSize: 18
        }

        Button {
            id: startButton
            x: 73
            width: 55
            height: 25
            text: qsTr("Start")
            font.pointSize: 12
            anchors.right: textFieldY.right
            anchors.rightMargin: 0
            anchors.top: textFieldY.bottom
            anchors.topMargin: 18

            onClicked: {
                b_start = true
                pos_x_pedida = textFieldX.text
                pos_y_pedida = textFieldY.text
                if (dataMovement.bplanningMovement(triangle.x, triangle.y, textFieldX.text, textFieldY.text)) {
                    total_steps = dataMovement.getTotalSteps();

                    if (pos_x_pedida != triangle.x && pos_y_pedida != triangle.y) {


                        pos_x = dataMovement.getPosX(step);
                        delta_x = dataMovement.getDeltaX(step);
                        pos_y = dataMovement.getPosY(step);
                        delta_y = dataMovement.getDeltaY(step);
                        angle = dataMovement.getPosAngle(step);
                    }
                }
            }

        }

        Rectangle {
            id: posicionActual
            y: 207
            height: 98
            color: "#ffffff"
            radius: 8
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            Text {
                id: elementX1
                y: 11
                text: qsTr("X:")
                font.pixelSize: 18
                anchors.leftMargin: 20
                anchors.left: parent.left
                anchors.verticalCenter: textValueX.verticalCenter
            }

            Text {
                id: elementY1
                y: 56
                text: qsTr("Y:")
                font.pixelSize: 18
                anchors.leftMargin: 0
                anchors.left: elementX1.left
                anchors.verticalCenter: textValueY.verticalCenter
            }

            Text {
                id: textValueX
                x: 0
                height: 22
                text: triangle.x
                horizontalAlignment: Text.AlignRight
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.top: parent.top
                anchors.topMargin: 18
                anchors.leftMargin: 12
                font.pixelSize: 18
                anchors.left: elementX1.right
            }

            Text {
                id: textValueY
                x: 40
                y: 3
                height: 22
                text: triangle.y
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 18
                anchors.leftMargin: 0
                anchors.topMargin: 18
                anchors.left: textValueX.left
                anchors.rightMargin: 0
                anchors.right: textValueX.right
                anchors.top: textValueX.bottom
            }
            border.width: 4
            border.color: "#0277bd"
        }

    }

    Timer {
        interval: 10; running: true; repeat: true
        onTriggered: {


            if (b_start) {
                if (pos_x_pedida == triangle.x && pos_y_pedida == triangle.y) {

                    console.log("[LOGGER] Llegada al destino! xpedida = " + pos_x_pedida + ", ypedida = " + pos_y_pedida)
                    b_start = false

                } else {
                    pos_x = dataMovement.getPosX(step);
                    delta_x = dataMovement.getDeltaX(step);
                    pos_y = dataMovement.getPosY(step);
                    delta_y = dataMovement.getDeltaY(step);
                    angle = dataMovement.getPosAngle(step);

                    if (angle != triangle.rotation) {
                        triangle.rotation = angle
                    }

                    if (pos_x != triangle.x) {
                        //console.log("pos_x = " + pos_x + " triangle.x = " + triangle.x)
                        if (delta_x < 0) {
                            triangle.x -= 1
                        } else if (delta_x > 0) {
                            triangle.x += 1
                        }

                    } else if (pos_y != triangle.y) {
console.log("5")
                        if (delta_y < 0) {
                            triangle.y -= 1
                        } else if (delta_y > 0) {
                            triangle.y += 1
                        }

                    } else {
                        console.log("[LOGGER] Step " + step + " has been completed!")
                        step += 1
                    }

                }

            }
        }



    }
}

/*##^##
Designer {
    D{i:5;anchors_x:8}D{i:6;anchors_width:81;anchors_x:30;anchors_y:8}D{i:7;anchors_width:81;anchors_x:30;anchors_y:53}
D{i:8;anchors_x:8}D{i:9;anchors_height:25;anchors_width:140;anchors_x:26;anchors_y:107}
}
##^##*/
