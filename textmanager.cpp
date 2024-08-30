#include "textmanager.h"

TextManager::TextManager()
{
    // 텍스트 배열 초기화
    texts[0] = QObject::tr("Click to select!");           // 클릭하여 선택하세요.
    texts[1] = QObject::tr("None");                       // 없음
    texts[2] = QObject::tr("Separation");                 // 분리
    texts[3] = QObject::tr("Integration");                // 통합
    texts[4] = QObject::tr("Version History Details");    // 버전 기록 세부 정보
    texts[5] = QObject::tr("Version History");            // 버전 기록
    texts[6] = QObject::tr("yyyy.MM.dd.");                // 날짜 형식
    texts[7] = QObject::tr("Show Version History");       // 버전 기록 표시
    texts[8] = QObject::tr("Button Clicked");             // 버튼 클릭됨
    texts[9] = QObject::tr("Dialog Closing");             // 다이얼로그 닫힘
    texts[10] = QObject::tr("Status Bar Message");        // 상태 표시줄 메시지
}

QString TextManager::getText(int index) const
{
    if (index >= 0 && index < 11)
        return texts[index];
    else
        return QString();
}
