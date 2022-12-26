// Copyright (C) 2022 Sandra Arnold
// sajoarn@gmail.com

#include "bingoCompanion.h"
#include "button.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QtMath>
#include <QRegularExpression>

BingoCompanion::BingoCompanion(QWidget *parent)
    : QWidget(parent)
{
    entry = new QLabel("");
    entry->setAlignment(Qt::AlignLeft);

    QFont font = entry->font();
    font.setPointSize(font.pointSize() + 8);
    entry->setFont(font);

    for (int i = 0; i < LimitO; ++i)
    {
        bingoButtons[i] = createButton(getLabelFromIndex(i), SLOT(numberClicked()));
    }

    Button *clearAllButton = createButton(tr("Clear All"), SLOT(clearAll()));
    Button *loadLastGameButton = createButton(tr("Load Previous"), SLOT(loadLastGame()));

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(entry, 0, 0, 1, 2);
    mainLayout->addWidget(loadLastGameButton, 0, 11, 1, 2);
    mainLayout->addWidget(clearAllButton, 0, 13, 1, 2);

    for (int i = 0; i < LimitO; ++i) {
        int row =  1 + std::floor(i / 15);
        int column = i % 15;
        mainLayout->addWidget(bingoButtons[i], row, column);
    }

    mainLayout->addWidget(bingoButtons[0], 5, 1);

    setLayout(mainLayout);

    setWindowTitle(tr("BingoCompanion"));
}

void BingoCompanion::numberClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());

    setButtonBackgroundClicked(clickedButton);
    QString temp;
    QRegularExpression re("\\d+");
    QRegularExpressionMatch match = re.match(clickedButton->text());
    if(match.hasMatch())
    {
        temp = match.captured(0);
    }

    clickedNumbers.push_back(temp.toInt() - 1);

    entry->setText(clickedButton->text());
}

void BingoCompanion::clearAll()
{
    previousNumbers = clickedNumbers;
    clickedNumbers.clear();

    for (int i = 0; i < LimitO; ++i)
    {
        clearButtonBackground(bingoButtons[i]);
    }

    entry->setText("");
}

void BingoCompanion::loadLastGame()
{
    clickedNumbers = previousNumbers;

    // Clear out all currently selected numbers
    for (int i = 0; i < LimitO; ++i)
    {
        clearButtonBackground(bingoButtons[i]);
    }

    // Set previous selected number backgrounds
    for(int i : clickedNumbers)
    {
        setButtonBackgroundClicked(bingoButtons[i]);
    }

    entry->setText(getLabelFromIndex(clickedNumbers.back()));
}

void BingoCompanion::setButtonBackgroundClicked(Button* button)
{
    button->setStyleSheet(QString("background-color: blue;"));
}

void BingoCompanion::clearButtonBackground(Button* button)
{
    button->setStyleSheet("");
}

QString BingoCompanion::getLabelFromIndex(int index)
{
    QString label;

    std::map<int, char> bingoLetter =
     {
        {0, 'B'},
        {1, 'I'},
        {2, 'N'},
        {3, 'G'},
        {4, 'O'}
    }; 

    label = bingoLetter[std::floor(index / 15)] + QString::number(index + 1);

    return label;
}

Button *BingoCompanion::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}
