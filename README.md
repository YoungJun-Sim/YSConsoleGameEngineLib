보내주신 코드(`CYS.h`, `CYS.cpp`, `main.cpp`)를 완벽하게 분석했습니다.

이 라이브러리의 핵심 기능은 **Windows API를 활용한 더블 버퍼링(Double Buffering)**, **유니코드 지원**, 그리고 **객체 지향적인 화면/에셋 관리**입니다.

GitHub `README.md`에 바로 사용할 수 있도록, **프로젝트 소개, 주요 특징, 설치법, API 문서, 예제 코드** 순서로 정리해 드립니다.

-----

### 📝 GitHub README.md 초안

아래 내용을 복사해서 `README.md` 파일을 만드시면 됩니다.

````markdown
# CYS Console Game Library

**CYS**는 C++와 Windows API를 기반으로 제작된 **경량 콘솔 게임 엔진 라이브러리**입니다.
복잡한 Win32 API 설정을 감추고, 객체 지향적인 인터페이스를 통해 쉽고 빠르게 콘솔 게임을 개발할 수 있도록 돕습니다.

## ✨ 주요 특징 (Features)

* **더블 버퍼링 (Double Buffering):** 화면 깜빡임(Flickering) 없는 부드러운 렌더링을 지원합니다.
* **유니코드/한글 지원:** `std::wstring`과 `_O_U16TEXT` 모드를 사용하여 한글 및 특수문자가 깨지지 않습니다.
* **스프라이트 시스템:** 텍스트 파일로부터 아스키 아트(ASCII Art)를 로드하거나 직접 지정하여 그릴 수 있습니다.
* **자동 클리핑 (Clipping):** 화면 밖으로 나가는 오브젝트를 자동으로 계산하여 렌더링 오류를 방지합니다.
* **화면 제어:** 폰트 변경, 화면 크기 고정, 창 크기 조절 방지 등의 기능을 API로 제공합니다.

## 📦 설치 및 적용 (Installation)

이 프로젝트는 헤더 파일과 소스 파일로 구성되어 있습니다.

1. `CYS.h`와 `CYS.cpp` 파일을 프로젝트 폴더에 복사합니다.
2. 사용하려는 코드(예: `main.cpp`)에서 헤더를 포함합니다.
3. 컴파일 시 `CYS.cpp`도 함께 빌드되어야 합니다.

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

```

---

### 💡 팁: 설명을 더 풍성하게 하려면?

작성해 드린 초안에 더해 아래 내용도 추가하면 좋습니다.

1.  **스크린샷/GIF:** `main.cpp`를 실행했을 때 "CYS project Hello World"가 움직이는 화면을 캡처(GIF)해서 `README.md` 최상단에 넣으면 훨씬 매력적으로 보입니다.
2.  **Asset 파일 예시:** `asset.txt` 같은 파일을 하나 만들어서, 어떻게 텍스트로 그림을 저장하는지 보여주면 사용자가 이해하기 쉽습니다.

이 내용 그대로 깃허브에 올리셔도 되고, 수정하고 싶은 부분이 있다면 말씀해 주세요!
```
