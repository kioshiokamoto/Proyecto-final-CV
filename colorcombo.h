#ifndef COLORCOMBO_H
#define COLORCOMBO_H
#include <QLabel>
#include <QColor>

class QMenu;
class QListWidget;

class ColorCombo : public QLabel
{
    Q_OBJECT
public:
    ColorCombo(QWidget *parent = nullptr);
    void adjustSize(const QSize &sz);
    void setCurrentColor(const QColor &color);

    QColor currentColor() const{
        return mCurrentColor;
    }


signals:
    void currentColorChanged(const QColor &color);

protected:
    void mousePressEvent(QMouseEvent *e) override;
private:
    QColor mCurrentColor;
    QMenu *mMenu;
    QMenu *makeMenu();
    QListWidget *mListWidget;
    QListWidget *makeListWidget();
    void displayColor(const QColor &color);
    void assignColors(QListWidget *listWidget);

};

#endif // COLORCOMBO_H
