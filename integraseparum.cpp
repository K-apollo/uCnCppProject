#include "integraseparum.h"
#include "ui_integraseparum.h"
#include <QGuiApplication>
#include <QScreen>
#include <QMessageBox>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QLocale>
#include "vershistory.h"

Integraseparum::Integraseparum(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Integraseparum),
    iForm(new InitForm(this)),
    nForm(new NextForm(this)),
    layout(new QVBoxLayout),
    vHistoryBtn(new QPushButton("Version History", this)),
    statusBarTimer(new QTimer(this)),
    tManager(new TextManager())  // TextManager 클래스 사용
{
    ui->setupUi(this);

    // labelContents에 텍스트 설정
    ui->labelContents->setText(tManager->getText(0));

    // 콤보박스에 아이템 추가
    ui->comboBox->addItem(tManager->getText(1));  // "None"
    ui->comboBox->addItem(tManager->getText(2));  // "Separation"
    ui->comboBox->addItem(tManager->getText(3));  // "Integration"
    ui->comboBox->setCurrentIndex(0);

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Integraseparum::onCurIndex); // 콤보박스 인덱스 변경 시 onCurIndex 슬롯 호출
    ui->label->setLayout(layout);           // label을 widget으로 대체하고 layout 설정

    // VersionHistory 버튼을 statusbar에 추가
    vHistoryBtn->setFixedSize(vHistoryBtn->sizeHint());
    connect(vHistoryBtn, &QPushButton::clicked, this, &Integraseparum::showVersionHistory);
    ui->statusbar->addWidget(vHistoryBtn);

    updateVersHistoryBtn();     // 최신 버전 정보를 버튼에 표시

    connect(statusBarTimer, &QTimer::timeout, this, &Integraseparum::clearStatusBarMessage);  // 스테이터스바 메시지 타이머 연결

    // 초기 상태는 다이얼로그 숨김
    iForm->hide();
    nForm->hide();
}

Integraseparum::~Integraseparum()
{
    delete ui;
    delete tManager;  // 메모리 해제
}

void Integraseparum::resizeDialog(QWidget* dialog, int maxLabelWidth, int maxLabelHeight) {
    QSize originalSize = dialog->sizeHint();
    int originalWidth = originalSize.width();
    int originalHeight = originalSize.height();

    double widthRatio = static_cast<double>(maxLabelWidth) / originalWidth;
    double heightRatio = static_cast<double>(maxLabelHeight) / originalHeight;
    double scaleRatio = qMin(widthRatio, heightRatio);

    int newWidth = static_cast<int>(originalWidth * scaleRatio);
    int newHeight = static_cast<int>(originalHeight * scaleRatio);

    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    dialog->setMaximumSize(screenWidth, screenHeight);
    dialog->resize(newWidth, newHeight);
}

void Integraseparum::onCurIndex(int index)
{
    iForm->hide();
    nForm->hide();

    while (QLayoutItem *item = layout->takeAt(0))
    {
        item->widget()->setParent(nullptr);
        delete item;
    }

    int maxLabelWidth = ui->label->width();
    int maxLabelHeight = ui->label->height();

    if (index == 1)
    {
        if (layout->indexOf(iForm) == -1)
        {
            layout->addWidget(iForm);
        }
        resizeDialog(iForm, maxLabelWidth, maxLabelHeight);
        iForm->show();
    }
    else if (index == 2)
    {
        if (layout->indexOf(nForm) == -1)
        {
            layout->addWidget(nForm);
        }
        resizeDialog(nForm, maxLabelWidth, maxLabelHeight);
        nForm->show();
    }
}

void Integraseparum::showVersionHistory()
{
    // 최신 버전 정보에서 날짜를 제외한 부분을 추출하여 스테이터스바에 표시
    QString latestVersionDetails = vHistory.getVersionHistory().section('\n', 0, 0).split(" - ").last();
    ui->statusbar->showMessage(latestVersionDetails);
    statusBarTimer->start(10000); // 10초 후 스테이터스바 메시지 제거

    // 새로운 다이얼로그 창 생성
    QDialog *hDialog = new QDialog(this);
    QVBoxLayout *dLayout = new QVBoxLayout(hDialog);
    QLabel *hLabel = new QLabel(vHistory.getVersionHistory(), hDialog);
    dLayout->addWidget(hLabel);

    hDialog->setWindowTitle(tManager->getText(4));  // "Version History Details"
    hDialog->setLayout(dLayout);
    hDialog->setModal(false);
    hDialog->show();

    // 3초 후 다이얼로그 창 자동 닫힘
    QTimer::singleShot(3000, hDialog, &QDialog::close);
}

void Integraseparum::updateVersHistoryBtn()     // 최신 버전에서 날짜 추출
{
    QString latestDate = vHistory.getVersionHistory().section(' ', 1, 1);  // 날짜만 추출
    QString currentDate = QDate::currentDate().toString(tManager->getText(6));    // 현재 날짜를 yyyy.MM.dd 형식으로 가져오기

    // 버튼 텍스트에 최신 날짜 또는 현재 날짜 설정 (필요에 따라)
    if (!latestDate.isEmpty()) vHistoryBtn->setText(latestDate);
    else vHistoryBtn->setText(currentDate);
}

void Integraseparum::clearStatusBarMessage()    // 스테이터스바 메시지 제거를 위한 슬롯
{
    ui->statusbar->clearMessage();
}
