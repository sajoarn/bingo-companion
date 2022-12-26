// Copyright (C) 2022 Sandra Arnold
// sajoarn@gmail.com

#include <QApplication>

#include "bingoCompanion.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    BingoCompanion bingo;
    bingo.show();
    return app.exec();
}
