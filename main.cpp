#include "bookwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BookWidget w;
    w.show();

    return a.exec();
}
