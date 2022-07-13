TARGET = "Helper Chess"

INCLUDEPATH += include

HEADERS += include/window/Controller.hpp \
           include/window/Connect.hpp \
           include/window/Window.hpp \
           include/window/Viewer.hpp \
           include/thread/ClientThread.hpp \
           include/chess/Chessboard.hpp \
           include/chess/Piece.hpp \
           include/tool/BezierCurve.hpp \
           include/tool/Math.hpp \
           include/tool/Byte.hpp \
           include/net/DataPack.hpp \
           include/net/Server.hpp \
           include/net/Client.hpp

SOURCES += src/window/Controller.cpp \
           src/window/Connect.cpp \
           src/window/Window.cpp \
           src/window/Viewer.cpp \
           src/thread/ClientThread.cpp \
           src/chess/Chessboard.cpp \
           src/chess/Piece.cpp \
           src/tool/BezierCurve.cpp \
           src/tool/Math.cpp \
           src/tool/Byte.cpp \
           src/net/DataPack.cpp \
           src/net/Server.cpp \
           src/net/Client.cpp \
           src/HelperChess.cpp

QT += core \
      widgets

CONFIG += console

LIBS += -lwsock32
