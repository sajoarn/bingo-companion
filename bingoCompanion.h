// Copyright (C) 2022 Sandra Arnold
// sajoarn@gmail.com

#ifndef BINGOCOMPANION_H
#define BINGOCOMPANION_H

#include <QWidget>
#include <QLabel>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE
class Button;

class BingoCompanion : public QWidget
{
    Q_OBJECT

public:
    BingoCompanion(QWidget *parent = nullptr);

private slots:
    void numberClicked();
    void clearAll();
    void loadLastGame();

private:
    void setButtonBackgroundClicked(Button* button);
    void clearButtonBackground(Button* button);
    QString getLabelFromIndex(int index);
    Button *createButton(const QString &text, const char *member);

    QLabel *entry;

    enum bingoDefinitions { 
        LimitB = 15,
        LimitI = 30,
        LimitN = 45,
        LimitG = 60,
        LimitO = 75
    };

    std::vector<int> clickedNumbers;
    std::vector<int> previousNumbers;

    Button *bingoButtons[LimitO];
};

#endif
