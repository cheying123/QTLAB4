#include "mastervier.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MasterVier w;
    w.show();
    return a.exec();
}
