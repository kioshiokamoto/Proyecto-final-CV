#include "colorcombo.h"
#include <QMenu>
#include <QImage>
#include <QPainter>
#include <QJsonArray>
#include <QJsonValue>
#include <QMouseEvent>
#include <QListWidget>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QResizeEvent>
#include <QJsonDocument>
#include <iostream>

ColorCombo::ColorCombo(QWidget *parent)
    : QLabel {parent}
{
    setFrameShape(QLabel::Box);
    mListWidget = makeListWidget();
    mMenu = makeMenu();

}
void ColorCombo::adjustSize(const QSize &sz)
{
    setMinimumSize(sz);
    setMaximumSize(sz);
}
void ColorCombo::setCurrentColor(const QColor &color)
{
    if(mCurrentColor != color){
        mCurrentColor = color;
        displayColor(mCurrentColor);
        emit currentColorChanged(mCurrentColor);
    }
}
void ColorCombo::mousePressEvent(QMouseEvent *e)
{
    mListWidget->setMinimumWidth(width());
    mMenu->popup(parentWidget()->mapToGlobal(pos()));
    QLabel::mousePressEvent(e);
}
QListWidget *ColorCombo::makeListWidget()
{
    QListWidget *listWidget = new QListWidget(this);
    listWidget->setMinimumSize(width(),250);
    assignColors(listWidget);
    connect(listWidget,&QListWidget::itemClicked,this,[&](QListWidgetItem *item){
        mCurrentColor = item->background().color();
        displayColor(mCurrentColor);
        mMenu->hide();
    });
    return listWidget;
}
QMenu *ColorCombo::makeMenu()
{
    QMenu *menu = new QMenu(this);
    QBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(mListWidget);
    vbox->setMargin(0);
    vbox->setSpacing(0);
    menu->setLayout(vbox);
    return menu;
}
void ColorCombo::displayColor(const QColor &color)
{
    QImage imgColor(size(),QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&imgColor);

    painter.fillRect(rect(),color);
    setPixmap(QPixmap::fromImage(imgColor));

}
void ColorCombo::assignColors(QListWidget *listWidget)
{
    QFile JSFile(":/colors.json");
    if(JSFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QJsonDocument doc = QJsonDocument::fromJson(JSFile.readAll());
        JSFile.close();
        QJsonArray colorsArray = doc.array();
        const int nColors = colorsArray.size();
        if(nColors>0){
            listWidget->clear();
            for(int iColor=0;iColor<nColors;++iColor){
                QJsonObject colorObj = colorsArray.at(iColor).toObject();
                QListWidgetItem *colorItem = new QListWidgetItem;
                colorItem->setText(colorObj["name"].toString());
                colorItem->setBackground(QColor(colorObj["hexvalue"].toString()));
                colorItem->setForeground(Qt::white);
                listWidget->addItem(colorItem);
            }

        }
    }
}
