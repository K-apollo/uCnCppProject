#include "vershistory.h"
#include <QStringList>

VersHistory::VersHistory()
{
}

QString VersHistory::getVersionHistory()
{
    QString history;

    // 버전 정보와 업데이트 내용을 분리하여 저장
    QStringList versions = {
        "Vers. 2024.08.26. - KimSooHyun, Added new feature XYZ",
        "Vers. 2024.08.25. - KimSooHyun, Fixed bug #1234"
    };

    // 최신 버전이 가장 위에 오도록 정렬하고 각 정보를 분리하여 처리
    for (const QString &versionInfo : versions) {
        // 버전 정보와 사용자 이름을 분리 (기준: " - ")
        QStringList versionParts = versionInfo.split(" - ");
        QString version = versionParts[0];
        QString userAndContent = versionParts[1];

        // 사용자 이름과 업데이트 내용을 분리 (기준: ", ")
        QStringList userAndContentParts = userAndContent.split(", ");
        QString user = userAndContentParts[0];
        QString content = userAndContentParts[1];

        // 최종 출력 형태: "버전: 사용자 이름, 업데이트 내용"
        history += version + ": " + user + ", " + content + "\n";
    }

    return history;
}
