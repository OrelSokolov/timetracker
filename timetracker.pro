TEMPLATE = app
QT           += core gui xml svg

HEADERS       = src/window.h

SOURCES       = src/main.cpp \
                src/window.cpp

RESOURCES     = timetracker.qrc

CONFIG += release

OTHER_FILES += \
    README.md

# Pretty release configuration

  release:DESTDIR     = build/
  release:OBJECTS_DIR = $$DESTDIR/.obj
  release:MOC_DIR     = $$DESTDIR/.moc
  release:RCC_DIR     = $$DESTDIR/.rcc
  release:UI_DIR      = $$DESTDIR/.ui

