#-------------------------------------------------
#
# Project created by QtCreator 2019-09-24T11:29:02
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CobraBot
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        chatparser.cpp \
        helpers.cpp \
        main.cpp \
        mainwindow.cpp \
        modtools.cpp \
        mustache.cpp \
        twitch.cpp

HEADERS += \
        chatparser.h \
        helpers.h \
        mainwindow.h \
        modtools.h \
        mustache.h \
        twitch.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../build-CobraBot-Desktop_Qt_5_13_0_GCC_64bit-Debug/config/caps.ini \
    config/twitch.ini \
    qdarkstyle/__init__.py \
    qdarkstyle/__main__.py \
    qdarkstyle/palette.py \
    qdarkstyle/pyqt5_style_rc.py \
    qdarkstyle/pyqt_style_rc.py \
    qdarkstyle/pyqtgraph_style_rc.py \
    qdarkstyle/pyside2_style_rc.py \
    qdarkstyle/pyside_style_rc.py \
    qdarkstyle/qss/_styles.scss \
    qdarkstyle/qss/_variables.scss \
    qdarkstyle/qss/main.scss \
    qdarkstyle/qtpy_style_rc.py \
    qdarkstyle/rc/arrow_down.png \
    qdarkstyle/rc/arrow_down@2x.png \
    qdarkstyle/rc/arrow_down_disabled.png \
    qdarkstyle/rc/arrow_down_disabled@2x.png \
    qdarkstyle/rc/arrow_down_focus.png \
    qdarkstyle/rc/arrow_down_focus@2x.png \
    qdarkstyle/rc/arrow_down_pressed.png \
    qdarkstyle/rc/arrow_down_pressed@2x.png \
    qdarkstyle/rc/arrow_left.png \
    qdarkstyle/rc/arrow_left@2x.png \
    qdarkstyle/rc/arrow_left_disabled.png \
    qdarkstyle/rc/arrow_left_disabled@2x.png \
    qdarkstyle/rc/arrow_left_focus.png \
    qdarkstyle/rc/arrow_left_focus@2x.png \
    qdarkstyle/rc/arrow_left_pressed.png \
    qdarkstyle/rc/arrow_left_pressed@2x.png \
    qdarkstyle/rc/arrow_right.png \
    qdarkstyle/rc/arrow_right@2x.png \
    qdarkstyle/rc/arrow_right_disabled.png \
    qdarkstyle/rc/arrow_right_disabled@2x.png \
    qdarkstyle/rc/arrow_right_focus.png \
    qdarkstyle/rc/arrow_right_focus@2x.png \
    qdarkstyle/rc/arrow_right_pressed.png \
    qdarkstyle/rc/arrow_right_pressed@2x.png \
    qdarkstyle/rc/arrow_up.png \
    qdarkstyle/rc/arrow_up@2x.png \
    qdarkstyle/rc/arrow_up_disabled.png \
    qdarkstyle/rc/arrow_up_disabled@2x.png \
    qdarkstyle/rc/arrow_up_focus.png \
    qdarkstyle/rc/arrow_up_focus@2x.png \
    qdarkstyle/rc/arrow_up_pressed.png \
    qdarkstyle/rc/arrow_up_pressed@2x.png \
    qdarkstyle/rc/base_icon.png \
    qdarkstyle/rc/base_icon@2x.png \
    qdarkstyle/rc/base_icon_disabled.png \
    qdarkstyle/rc/base_icon_disabled@2x.png \
    qdarkstyle/rc/base_icon_focus.png \
    qdarkstyle/rc/base_icon_focus@2x.png \
    qdarkstyle/rc/base_icon_pressed.png \
    qdarkstyle/rc/base_icon_pressed@2x.png \
    qdarkstyle/rc/branch_closed.png \
    qdarkstyle/rc/branch_closed@2x.png \
    qdarkstyle/rc/branch_closed_disabled.png \
    qdarkstyle/rc/branch_closed_disabled@2x.png \
    qdarkstyle/rc/branch_closed_focus.png \
    qdarkstyle/rc/branch_closed_focus@2x.png \
    qdarkstyle/rc/branch_closed_pressed.png \
    qdarkstyle/rc/branch_closed_pressed@2x.png \
    qdarkstyle/rc/branch_end.png \
    qdarkstyle/rc/branch_end@2x.png \
    qdarkstyle/rc/branch_end_disabled.png \
    qdarkstyle/rc/branch_end_disabled@2x.png \
    qdarkstyle/rc/branch_end_focus.png \
    qdarkstyle/rc/branch_end_focus@2x.png \
    qdarkstyle/rc/branch_end_pressed.png \
    qdarkstyle/rc/branch_end_pressed@2x.png \
    qdarkstyle/rc/branch_line.png \
    qdarkstyle/rc/branch_line@2x.png \
    qdarkstyle/rc/branch_line_disabled.png \
    qdarkstyle/rc/branch_line_disabled@2x.png \
    qdarkstyle/rc/branch_line_focus.png \
    qdarkstyle/rc/branch_line_focus@2x.png \
    qdarkstyle/rc/branch_line_pressed.png \
    qdarkstyle/rc/branch_line_pressed@2x.png \
    qdarkstyle/rc/branch_more.png \
    qdarkstyle/rc/branch_more@2x.png \
    qdarkstyle/rc/branch_more_disabled.png \
    qdarkstyle/rc/branch_more_disabled@2x.png \
    qdarkstyle/rc/branch_more_focus.png \
    qdarkstyle/rc/branch_more_focus@2x.png \
    qdarkstyle/rc/branch_more_pressed.png \
    qdarkstyle/rc/branch_more_pressed@2x.png \
    qdarkstyle/rc/branch_open.png \
    qdarkstyle/rc/branch_open@2x.png \
    qdarkstyle/rc/branch_open_disabled.png \
    qdarkstyle/rc/branch_open_disabled@2x.png \
    qdarkstyle/rc/branch_open_focus.png \
    qdarkstyle/rc/branch_open_focus@2x.png \
    qdarkstyle/rc/branch_open_pressed.png \
    qdarkstyle/rc/branch_open_pressed@2x.png \
    qdarkstyle/rc/checkbox_checked.png \
    qdarkstyle/rc/checkbox_checked@2x.png \
    qdarkstyle/rc/checkbox_checked_disabled.png \
    qdarkstyle/rc/checkbox_checked_disabled@2x.png \
    qdarkstyle/rc/checkbox_checked_focus.png \
    qdarkstyle/rc/checkbox_checked_focus@2x.png \
    qdarkstyle/rc/checkbox_checked_pressed.png \
    qdarkstyle/rc/checkbox_checked_pressed@2x.png \
    qdarkstyle/rc/checkbox_indeterminate.png \
    qdarkstyle/rc/checkbox_indeterminate@2x.png \
    qdarkstyle/rc/checkbox_indeterminate_disabled.png \
    qdarkstyle/rc/checkbox_indeterminate_disabled@2x.png \
    qdarkstyle/rc/checkbox_indeterminate_focus.png \
    qdarkstyle/rc/checkbox_indeterminate_focus@2x.png \
    qdarkstyle/rc/checkbox_indeterminate_pressed.png \
    qdarkstyle/rc/checkbox_indeterminate_pressed@2x.png \
    qdarkstyle/rc/checkbox_unchecked.png \
    qdarkstyle/rc/checkbox_unchecked@2x.png \
    qdarkstyle/rc/checkbox_unchecked_disabled.png \
    qdarkstyle/rc/checkbox_unchecked_disabled@2x.png \
    qdarkstyle/rc/checkbox_unchecked_focus.png \
    qdarkstyle/rc/checkbox_unchecked_focus@2x.png \
    qdarkstyle/rc/checkbox_unchecked_pressed.png \
    qdarkstyle/rc/checkbox_unchecked_pressed@2x.png \
    qdarkstyle/rc/line_horizontal.png \
    qdarkstyle/rc/line_horizontal@2x.png \
    qdarkstyle/rc/line_horizontal_disabled.png \
    qdarkstyle/rc/line_horizontal_disabled@2x.png \
    qdarkstyle/rc/line_horizontal_focus.png \
    qdarkstyle/rc/line_horizontal_focus@2x.png \
    qdarkstyle/rc/line_horizontal_pressed.png \
    qdarkstyle/rc/line_horizontal_pressed@2x.png \
    qdarkstyle/rc/line_vertical.png \
    qdarkstyle/rc/line_vertical@2x.png \
    qdarkstyle/rc/line_vertical_disabled.png \
    qdarkstyle/rc/line_vertical_disabled@2x.png \
    qdarkstyle/rc/line_vertical_focus.png \
    qdarkstyle/rc/line_vertical_focus@2x.png \
    qdarkstyle/rc/line_vertical_pressed.png \
    qdarkstyle/rc/line_vertical_pressed@2x.png \
    qdarkstyle/rc/radio_checked.png \
    qdarkstyle/rc/radio_checked@2x.png \
    qdarkstyle/rc/radio_checked_disabled.png \
    qdarkstyle/rc/radio_checked_disabled@2x.png \
    qdarkstyle/rc/radio_checked_focus.png \
    qdarkstyle/rc/radio_checked_focus@2x.png \
    qdarkstyle/rc/radio_checked_pressed.png \
    qdarkstyle/rc/radio_checked_pressed@2x.png \
    qdarkstyle/rc/radio_unchecked.png \
    qdarkstyle/rc/radio_unchecked@2x.png \
    qdarkstyle/rc/radio_unchecked_disabled.png \
    qdarkstyle/rc/radio_unchecked_disabled@2x.png \
    qdarkstyle/rc/radio_unchecked_focus.png \
    qdarkstyle/rc/radio_unchecked_focus@2x.png \
    qdarkstyle/rc/radio_unchecked_pressed.png \
    qdarkstyle/rc/radio_unchecked_pressed@2x.png \
    qdarkstyle/rc/toolbar_move_horizontal.png \
    qdarkstyle/rc/toolbar_move_horizontal@2x.png \
    qdarkstyle/rc/toolbar_move_horizontal_disabled.png \
    qdarkstyle/rc/toolbar_move_horizontal_disabled@2x.png \
    qdarkstyle/rc/toolbar_move_horizontal_focus.png \
    qdarkstyle/rc/toolbar_move_horizontal_focus@2x.png \
    qdarkstyle/rc/toolbar_move_horizontal_pressed.png \
    qdarkstyle/rc/toolbar_move_horizontal_pressed@2x.png \
    qdarkstyle/rc/toolbar_move_vertical.png \
    qdarkstyle/rc/toolbar_move_vertical@2x.png \
    qdarkstyle/rc/toolbar_move_vertical_disabled.png \
    qdarkstyle/rc/toolbar_move_vertical_disabled@2x.png \
    qdarkstyle/rc/toolbar_move_vertical_focus.png \
    qdarkstyle/rc/toolbar_move_vertical_focus@2x.png \
    qdarkstyle/rc/toolbar_move_vertical_pressed.png \
    qdarkstyle/rc/toolbar_move_vertical_pressed@2x.png \
    qdarkstyle/rc/toolbar_separator_horizontal.png \
    qdarkstyle/rc/toolbar_separator_horizontal@2x.png \
    qdarkstyle/rc/toolbar_separator_horizontal_disabled.png \
    qdarkstyle/rc/toolbar_separator_horizontal_disabled@2x.png \
    qdarkstyle/rc/toolbar_separator_horizontal_focus.png \
    qdarkstyle/rc/toolbar_separator_horizontal_focus@2x.png \
    qdarkstyle/rc/toolbar_separator_horizontal_pressed.png \
    qdarkstyle/rc/toolbar_separator_horizontal_pressed@2x.png \
    qdarkstyle/rc/toolbar_separator_vertical.png \
    qdarkstyle/rc/toolbar_separator_vertical@2x.png \
    qdarkstyle/rc/toolbar_separator_vertical_disabled.png \
    qdarkstyle/rc/toolbar_separator_vertical_disabled@2x.png \
    qdarkstyle/rc/toolbar_separator_vertical_focus.png \
    qdarkstyle/rc/toolbar_separator_vertical_focus@2x.png \
    qdarkstyle/rc/toolbar_separator_vertical_pressed.png \
    qdarkstyle/rc/toolbar_separator_vertical_pressed@2x.png \
    qdarkstyle/rc/transparent.png \
    qdarkstyle/rc/transparent@2x.png \
    qdarkstyle/rc/transparent_disabled.png \
    qdarkstyle/rc/transparent_disabled@2x.png \
    qdarkstyle/rc/transparent_focus.png \
    qdarkstyle/rc/transparent_focus@2x.png \
    qdarkstyle/rc/transparent_pressed.png \
    qdarkstyle/rc/transparent_pressed@2x.png \
    qdarkstyle/rc/window_close.png \
    qdarkstyle/rc/window_close@2x.png \
    qdarkstyle/rc/window_close_disabled.png \
    qdarkstyle/rc/window_close_disabled@2x.png \
    qdarkstyle/rc/window_close_focus.png \
    qdarkstyle/rc/window_close_focus@2x.png \
    qdarkstyle/rc/window_close_pressed.png \
    qdarkstyle/rc/window_close_pressed@2x.png \
    qdarkstyle/rc/window_grip.png \
    qdarkstyle/rc/window_grip@2x.png \
    qdarkstyle/rc/window_grip_disabled.png \
    qdarkstyle/rc/window_grip_disabled@2x.png \
    qdarkstyle/rc/window_grip_focus.png \
    qdarkstyle/rc/window_grip_focus@2x.png \
    qdarkstyle/rc/window_grip_pressed.png \
    qdarkstyle/rc/window_grip_pressed@2x.png \
    qdarkstyle/rc/window_minimize.png \
    qdarkstyle/rc/window_minimize@2x.png \
    qdarkstyle/rc/window_minimize_disabled.png \
    qdarkstyle/rc/window_minimize_disabled@2x.png \
    qdarkstyle/rc/window_minimize_focus.png \
    qdarkstyle/rc/window_minimize_focus@2x.png \
    qdarkstyle/rc/window_minimize_pressed.png \
    qdarkstyle/rc/window_minimize_pressed@2x.png \
    qdarkstyle/rc/window_undock.png \
    qdarkstyle/rc/window_undock@2x.png \
    qdarkstyle/rc/window_undock_disabled.png \
    qdarkstyle/rc/window_undock_disabled@2x.png \
    qdarkstyle/rc/window_undock_focus.png \
    qdarkstyle/rc/window_undock_focus@2x.png \
    qdarkstyle/rc/window_undock_pressed.png \
    qdarkstyle/rc/window_undock_pressed@2x.png \
    qdarkstyle/style.qss \
    qdarkstyle/svg/arrow_down.svg \
    qdarkstyle/svg/arrow_left.svg \
    qdarkstyle/svg/arrow_right.svg \
    qdarkstyle/svg/arrow_up.svg \
    qdarkstyle/svg/base_icon.svg \
    qdarkstyle/svg/base_palette.svg \
    qdarkstyle/svg/branch_closed.svg \
    qdarkstyle/svg/branch_end.svg \
    qdarkstyle/svg/branch_line.svg \
    qdarkstyle/svg/branch_more.svg \
    qdarkstyle/svg/branch_open.svg \
    qdarkstyle/svg/checkbox_checked.svg \
    qdarkstyle/svg/checkbox_indeterminate.svg \
    qdarkstyle/svg/checkbox_unchecked.svg \
    qdarkstyle/svg/line_horizontal.svg \
    qdarkstyle/svg/line_vertical.svg \
    qdarkstyle/svg/radio_checked.svg \
    qdarkstyle/svg/radio_unchecked.svg \
    qdarkstyle/svg/toolbar_move_horizontal.svg \
    qdarkstyle/svg/toolbar_move_vertical.svg \
    qdarkstyle/svg/toolbar_separator_horizontal.svg \
    qdarkstyle/svg/toolbar_separator_vertical.svg \
    qdarkstyle/svg/transparent.svg \
    qdarkstyle/svg/window_close.svg \
    qdarkstyle/svg/window_grip.svg \
    qdarkstyle/svg/window_minimize.svg \
    qdarkstyle/svg/window_undock.svg \
    qdarkstyle/utils/__init__.py \
    qdarkstyle/utils/images.py \
    qdarkstyle/utils/scss.py

include(QtAwesome/QtAwesome.pri)

RESOURCES += \
    qdarkstyle/style.qrc
