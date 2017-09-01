#include "bookwidget.h"
#include "ui_bookwidget.h"
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QScreen>
#include <QPainter>


BookWidget::BookWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookWidget)
{
    ui->setupUi(this);

#if 0
   QSize iconSize(32, 32);
   QScreen *screen = qApp->primaryScreen();
   m_font = qApp->font();

   //m_font.setLetterSpacing(QFont::AbsoluteSpacing, 5);

   int pixelSize = (m_font.pointSize() * screen->logicalDotsPerInch()) / 72;
   QSize screenSize = screen->size();
   if(screenSize.width() > 960 || screenSize.height() > 960)
   {
       iconSize *= ((qreal)pixelSize) / 20;
   }
    m_rectDraw = QRect(0, 0, screenSize.width(), screenSize.height());
    setGeometry(m_rectDraw);

#else
    m_rectDraw = QRect(0, 0, 500, 620);
    setGeometry(m_rectDraw);

    m_rectDraw = QRect(50, 10, 400, 600);
#endif

     initBook(":/file/novel");
}

BookWidget::~BookWidget()
{
    delete ui;
}

bool BookWidget::initBook(QString fileName)
{
    m_fileName = fileName;
    m_listBookMark.clear();
    m_listBookMark.append(0);
    m_iCurrentPage = 0;
    openPage(true);

}

bool BookWidget::openPage(bool bNext)
{
    if(bNext)
    {
        m_iCurrentPage++;
    }
    else
    {
        m_iCurrentPage--;
        if(m_iCurrentPage < 1)
        {
            m_iCurrentPage = 1;
            return false;
        }
    }

    QFile file(m_fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "file not exist";
        return false;
    }

    QTextStream stream(&file);
    qint64 iPos = 0;
    iPos = m_listBookMark.at(m_iCurrentPage - 1);

    stream.seek(iPos);

    int iLine = 0;
    m_txtEdit.clear();
    while(iLine < 50)
    {
       QString line;

       while(1)
       {
           line += stream.read(1);
            if(line.contains("\n") || line.length() > 24)
            {
                iLine++;
                line.replace('\n', ' ');
                break;
            }
       }
       m_txtEdit.append(line);

       if(stream.atEnd())
       {
           break;
       }

       iLine++;
    }

    if(bNext)
    {
        qint64 iCurrentPost = stream.pos();
        if(iCurrentPost > m_listBookMark.at(m_listBookMark.size() - 1))
        {
            m_listBookMark.append(iCurrentPost);
        }
    }


    update();
}


void BookWidget::mousePressEvent ( QMouseEvent * e )
{
    int m_width = geometry().width();
    if (e->pos().x() < m_width / 4)
    {
         openPage(false);
    }
    else if (e->pos().x() > (m_width - m_width / 4))
    {

        openPage(true);
    }
}

void BookWidget::keyReleaseEvent(QKeyEvent * e)
{
    if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Right)
    {
        openPage(true);
    }
    else if (e->key() == Qt::Key_Left)
    {
        openPage(false);
    }


}

void BookWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //QRectF rect(50,10,400,600);


    //设置一个矩形
    painter.drawRect(m_rectDraw);
    //为了更直观地看到字体的位置，我们绘制出这个矩形
    painter.setPen(QColor(Qt::black));
    //设置画笔颜色为红色

    QString strText = m_txtEdit.toPlainText();
    painter.setFont(m_font);
    painter.drawText(m_rectDraw, strText);
}
