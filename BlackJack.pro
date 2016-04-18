#-------------------------------------------------
#
# Project created by QtCreator 2016-02-17T16:35:01
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BlackJack
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Card.cpp \
    Suit.cpp \
    Deck.cpp \
    BlackJack.cpp \
    PixmapWidget.cpp \
    BlackJackStateMachine.cpp

HEADERS  += MainWindow.h \
    Card.h \
    Suit.h \
    Deck.h \
    Suits.h \
    FaceValues.h \
    Faces.h \
    BlackJack.h \
    PixmapWidget.h \
    Participants.h \
    BlackJackStateMachine.h \
    GameStates.h

FORMS    += MainWindow.ui

RESOURCES += \
    BlackJack.qrc

DISTFILES += \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
