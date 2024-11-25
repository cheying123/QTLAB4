#ifndef MASTERVIER_H
#define MASTERVIER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MasterVier;
}
QT_END_NAMESPACE

class MasterVier : public QWidget
{
    Q_OBJECT

public:
    MasterVier(QWidget *parent = nullptr);
    ~MasterVier();

private:
    Ui::MasterVier *ui;
};
#endif // MASTERVIER_H
