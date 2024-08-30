#ifndef INTEGRASEPARUM_H
#define INTEGRASEPARUM_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QDate>
#include "initform.h"
#include "nextform.h"
#include "vershistory.h"
#include "textmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Integraseparum;
}
QT_END_NAMESPACE

class Integraseparum : public QMainWindow
{
    Q_OBJECT

public:
    Integraseparum(QWidget *parent = nullptr);
    ~Integraseparum();

private slots:
    void onCurIndex(int index);
    void showVersionHistory();

private:
    void resizeDialog(QWidget* dialog, int maxLabelWidth, int maxLabelHeight);
    void updateVersHistoryBtn();
    void clearStatusBarMessage();

    Ui::Integraseparum *ui;
    InitForm       *iForm;
    NextForm       *nForm;
    QVBoxLayout    *layout;
    QPushButton    *vHistoryBtn;
    VersHistory    vHistory;
    QTimer         *statusBarTimer;
    TextManager    *tManager;
};
#endif // INTEGRASEPARUM_H
