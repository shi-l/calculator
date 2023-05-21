import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
ApplicationWindow {
    id:window
    property int maxWidth: 600
    property int minWdith: 360
    property int baseToSeniorWidth: 600
    //计算机功能  1:基本  2:高级
    property int calculatorFunction: 1
    minimumHeight: editArea.height + buttonArea.height + 150
    minimumWidth: minWdith
    visible: true
    title: qsTr("计算器")



    menuBar: MenuBar{
        id:menuBarArea
        Menu{
            id: menuArea
            title: "功能"
            Button{
                text: "基本"
                onClicked: {
                    menuArea.close()
                    calculatorFunction = 1
                    base.expand()
                    senior.hide()
                    buttonArea.widthChanged()
                }
            }
            Button{
                text: "高级"
                onClicked: {
                    menuArea.close()
                    calculatorFunction = 2
                    base.shrink()
                    senior.show()
                    buttonArea.widthChanged()
                }
            }
            Button{
                text: "逆波兰表达式"
                onClicked: {
                    menuArea.close()
                    var s = Calculator.get_postfix(textEdit.text);
                    if(s === ""){

                    }else{
                        resultText.insert(resultText.length,s + "\n");
                    }
                }
            }
        }
    }



    Rectangle {
        id: resultArea

        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        height: parent.height - editArea.height - buttonArea.height
        width: parent.width < maxWidth ? parent.width : maxWidth
        border.color: "white"
        border.width: 1
        color: "#D1d7da"


        ScrollView{
            id:resultView
            anchors.fill: parent
            TextEdit {
                id: resultText
                readOnly: true

                anchors.fill: parent

                text: ""
                color: "black"
                font.pixelSize: 22
                font.family: "Open Sans Regular"
                //                fontSizeMode: Text.Fit
                selectByMouse: true
            }
        }



    }

    Rectangle {
        id: editArea

        anchors.bottom: buttonArea.top
        anchors.horizontalCenter: parent.horizontalCenter
        height: 80
        width: parent.width < maxWidth ? parent.width : maxWidth
        border.color: "white"
        border.width: 1
        color: "#D1d7da"

        ScrollView
        {
            id: editView
            anchors.fill: parent
            TextEdit {

                id: textEdit
                anchors.fill: parent
                focus: true

                text: ""
                color: "black"
                font.pixelSize: 30
                font.family: "Open Sans Regular"
                selectByMouse: true
                //回车键和等于键均视为计算结果
                Keys.onPressed: function(event){
                    if(event.key === Qt.Key_Equal || event.key === Qt.Key_Return || event.key === Qt.Key_Enter){
                        get_result.clicked();
                        event.accepted = true
                    }
                }

            }
        }


    }
    Rectangle {
        id: buttonArea
        visible: true

        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        height: 250
        width: parent.width < maxWidth ? parent.width : maxWidth
        border.color: "white"
        border.width: 1
        color: "white"
        onWidthChanged: {
            if(calculatorFunction == 2){
                if(window.width > baseToSeniorWidth ){
                    senior.visible = true;
                    base.shrink()
                }else{
                    senior.visible = false;
                    base.expand()
                }
            }
        }

        Rectangle{
            anchors.fill: parent


            Grid{
                id:base
                function expand(){

                    width = Qt.binding(function(){return parent.width})
                }
                function shrink(){

                    width = Qt.binding(function(){return (parent.width - 10) / 2})
                }

                columns: 5
                anchors.left: parent.left
                anchors.top: parent.top
                height: buttonArea.height
                width: parent.width
                property int parentWidth: width
                SimpleButton{
                    onClicked: {
                        textEdit.clear();

                    }

                    text: "clear"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "("
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: ")"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "mod"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "π"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "7"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "8"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "9"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "/"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "√"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "4"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "5"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "6"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "*"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,"^2");
                    }

                    text: "×²"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "1"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "2"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "3"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "-"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "+"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "0"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "."
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }

                    text: "%"
                }
                SimpleButton{
                    id: get_result
                    onClicked: {
                        var s = Calculator.do_calculator(textEdit.text);
                        if(s === ""){

                        }else if(!isNaN(s) && s !== ""){
                            resultText.insert(resultText.length, textEdit.text + "\t" + '=' + "\t" + s + "\n")
                        }else{
                            resultText.insert(resultText.length,s + "\n");
                        }

                    }

                    text: "="
                }
            }

            Grid{
                id:senior
                function show(){
                    visible = true;
                }
                function hide(){
                    visible = false;
                }
                visible: false
                columns: 5
                anchors.left: base.right
                anchors.leftMargin: +10
                anchors.top: parent.top
                height: buttonArea.height
                width:(parent.width - 10) / 2
                property int parentWidth: width
                //                SimpleButton{
                //                    id: up
                //                    onClicked: {
                //                        color = color.toString() === "#ffffff"? "#aaaaaa" : "#ffffff"
                //                        down.color = "#ffffff"
                //                    }
                //                    text: "↓n"
                //                }
                //                SimpleButton{
                //                    id: down
                //                    onClicked: {
                //                        color = color.toString() === "#ffffff"? "#aaaaaa" : "#ffffff"
                //                        up.color = "#ffffff"
                //                    }
                //                    text: "↑n"
                //                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "cos"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "sin"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "tan"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "arcsin"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "arccos"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "arctan"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "cosh"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "sinh"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "tanh"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "xʸ"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "e"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,"²");
                    }
                    text: "ln"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "log"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,"!");
                    }
                    text: "x!"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "abs"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "₁"
                }
                SimpleButton{
                    onClicked: {
                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "₂"
                }
                SimpleButton{
                    onClicked: {

                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "₃"
                }
                SimpleButton{
                    onClicked: {

                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "₄"
                }
                SimpleButton{
                    onClicked: {

                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "₅"
                }
                SimpleButton{
                    onClicked: {

                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "₆"
                }
                SimpleButton{
                    onClicked: {

                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "₇"
                }
                SimpleButton{
                    onClicked: {

                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "₈"
                }
                SimpleButton{
                    onClicked: {

                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "₉"
                }
                SimpleButton{
                    onClicked: {

                        textEdit.insert(textEdit.cursorPosition,text);
                    }
                    text: "₀"
                }
            }
        }
    }
}
