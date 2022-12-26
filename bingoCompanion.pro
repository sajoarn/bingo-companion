QT += widgets

HEADERS       = button.h \
                bingoCompanion.h
SOURCES       = button.cpp \
                bingoCompanion.cpp \
                main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/bingoCompanion
INSTALLS += target