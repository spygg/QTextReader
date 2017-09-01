#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QMouseEvent>
#include <QKeyEvent>

namespace Ui {
class BookWidget;
}

class BookWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookWidget(QWidget *parent = 0);
    ~BookWidget();

private:
    Ui::BookWidget *ui;


public:
    bool initBook(QString fileName);
    bool openPage(bool bNext);

protected:
    void mousePressEvent(QMouseEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void paintEvent(QPaintEvent *event);

private:
    QRect m_rectDraw;
    QString m_fileName;
    QTextEdit m_txtEdit;
    int m_iCurrentPage;

    QList <qint64> m_listBookMark;

    QFont m_font;
};

#endif // BOOKWIDGET_H
