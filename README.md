
````markdown
# CYS Console Game Library

**CYS**는 C++와 Windows API를 기반으로 제작된 **경량 콘솔 게임 엔진 라이브러리**입니다.
복잡한 Win32 API 설정을 감추고, 객체 지향적인 인터페이스를 통해 쉽고 빠르게 콘솔 게임을 개발할 수 있도록 돕습니다.

```cpp
#include "CYS.h"
````

## 📚 API Reference

### 1\. Screen 클래스

화면 렌더링, 버퍼 관리, 콘솔 설정을 담당하는 핵심 클래스입니다.

| 함수명 | 설명 |
| --- | --- |
| **`Screen()`** | 생성자. 더블 버퍼링 초기화, 유니코드 모드 설정, 커서 숨김 처리를 수행합니다. |
| **`setWindowSize(w, h)`** | 콘솔 창의 크기와 내부 버퍼의 크기를 `w` (너비), `h` (높이)로 설정합니다. |
| **`setFont(x, y, name)`** | 폰트의 크기(픽셀 단위)와 글꼴(예: `L"Consolas"`)을 변경합니다. 정사각형 타일을 위해 1:2 비율 추천. |
| **`disableResize()`** | 사용자가 마우스로 콘솔 창의 크기를 조절하지 못하도록 막습니다. |
| **`resetBuffer()`** | 백 버퍼(Back Buffer)를 공백으로 초기화합니다. 매 프레임 그리기 전에 호출해야 합니다. |
| **`write(x, y, str)`** | 특정 좌표 `(x, y)`에 문자열 `str`을 버퍼에 기록합니다. (화면 출력 X, 메모리 기록 O) |
| **`Display()`** | 버퍼에 기록된 내용을 실제 콘솔 화면에 출력하고 버퍼를 교체(Swap)합니다. |
함수명,설명
Screen(),"생성자. 더블 버퍼링 초기화, 유니코드 모드 설정, 커서 숨김 처리를 수행합니다."
"setWindowSize(w, h)","콘솔 창의 크기와 내부 버퍼의 크기를 w (너비), h (높이)로 설정합니다."
setTitle(str),콘솔 창의 상단 제목(Title Bar) 텍스트를 변경합니다.
"setFont(x, y, name)","폰트의 크기(픽셀 단위)와 글꼴(예: L""Consolas"")을 변경합니다. (추천: 10, 20)"
disableResize(),사용자가 마우스로 콘솔 창의 크기를 조절하지 못하도록 막습니다. (게임 중 레이아웃 유지용)
enableResize(),콘솔 창 크기 조절 기능을 다시 활성화합니다.
resetBuffer(),백 버퍼(Back Buffer)를 공백으로 초기화합니다. 매 프레임 그리기 전에 호출해야 합니다.
"write(x, y, str)","특정 좌표 (x, y)에 문자열 str을 버퍼에 기록합니다. (화면 출력 X, 메모리 기록 O)"
"Draw(x, y, sprite)","좌표 (x, y)에 문자열 벡터(스프라이트)를 그립니다."
Display(),버퍼에 기록된 내용을 실제 콘솔 화면에 출력하고 버퍼를 교체(Swap)합니다.
"getWindowX(), getWindowY()",현재 설정된 게임 화면의 너비(Width)와 높이(Height)를 반환합니다.
"getMaxX(), getMaxY()","현재 모니터 해상도 기준, 콘솔 창이 가질 수 있는 최대 너비와 높이를 반환합니다."
printMaxallowed(),내 컴퓨터에서 허용되는 최대 콘솔 크기를 출력합니다. (디버깅용)
"gotoxy(x, y)",커서를 해당 좌표로 이동시킵니다. (주로 내부 렌더링용으로 사용됨)
release(),사용한 콘솔 리소스(핸들)를 해제합니다. (소멸자에서 자동 호출됨)
### 2\. Asset 클래스

게임 내 등장하는 오브젝트(플레이어, 적, 배경 등)를 관리합니다.

| 함수명 | 설명 |
| --- | --- |
| **`Load(path)`** | 텍스트 파일(.txt)을 읽어 스프라이트로 변환합니다. UTF-8 파일을 자동으로 wstring으로 변환합니다. |
| **`SetSprite(vector)`** | 코드 상에서 직접 문자열 배열을 통해 스프라이트 모양을 설정합니다. |
| **`setX(n)`, `setY(n)`** | 에셋의 위치 좌표를 설정합니다. |
| **`Draw(Screen*)`** | `Screen` 객체의 포인터를 받아, 해당 화면 버퍼에 자신의 현재 위치와 모양을 그립니다. |

-----

## 🚀 사용 예제 (Example Usage)

`main.cpp`의 기본적인 게임 루프 구조입니다.

```cpp
#include "CYS.h"
#include <memory>

int main() {
    // 1. Screen 객체 생성 (화면 초기화)
    auto s = std::make_unique<Screen>();

    // 2. 화면 설정 (크기 및 폰트)
    s->setWindowSize(1920/10, 1080/20); // 192x54 크기
    s->setFont(10, 20, L"Consolas");    // 폰트 크기 설정
    s->disableResize();                 // 창 크기 조절 잠금

    // 3. Asset 생성 및 스프라이트 설정
    Asset player(0, 0);
    player.SetSprite({ 
        L"  ( ^-^)  ",
        L" /| CYS |\\ ",
        L"  |__|__|  " 
    });

    int x = 0;

    // 4. 게임 루프
    while (true) {
        // [Step 1] 버퍼 초기화 (이전 프레임 지우기)
        s->resetBuffer();

        // [Step 2] 로직 업데이트
        player.setX(x++);
        if (x > s->getWindowX()) x = -10; // 화면 끝에 닿으면 루프

        // [Step 3] 그리기 (백 버퍼에 기록)
        player.Draw(s.get());

        // [Step 4] 화면 출력 (더블 버퍼 스왑)
        s->Display();

        Sleep(50); // 프레임 제어
    }

    return 0;
}
```

## ⚠️ 주의 사항 (Requirements)

  * **OS:** Windows (Windows API `windows.h` 사용)
  * **Encoding:** 소스 파일 및 에셋 텍스트 파일은 **UTF-8** 또는 **UTF-16**을 권장합니다.
  * **IDE:** Visual Studio (MSVC 컴파일러 권장)

<!-- end list -->

