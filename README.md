# 🎮 YSConsoleGameEngine

**YSConsoleGameEngine**은 Windows 환경에서 C++를 사용하여 고성능 콘솔 게임을 개발할 수 있도록 돕는 경량화된 게임 엔진 라이브러리입니다.

Windows API의 저수준 기능들을 캡슐화하여 **더블 버퍼링(Double Buffering)**을 통한 부드러운 렌더링, 손쉬운 **에셋(스프라이트/폰트) 관리**, 그리고 **유니코드(한글) 출력**을 간편하게 처리할 수 있습니다.

---

## ✨ 주요 기능 (Features)

### 🚀 고성능 렌더링 (Flicker-Free Rendering)
- **더블 버퍼링 구현:** `CreateConsoleScreenBuffer`와 `WriteConsoleOutputW`를 활용하여 화면 깜빡임 없이 매끄러운 프레임 전환을 제공합니다.
- **고속 드로잉:** `std::vector` 기반의 스크린 버퍼를 사용하여 메모리 단에서 렌더링 후 화면에 즉시 반영합니다.

### 🌏 완벽한 유니코드 지원 (Unicode & Hangul Support)
- **한글 깨짐 방지:** `_O_U16TEXT` 모드를 기본으로 사용하여 한글 및 특수문자를 지원합니다.
- **자동 폭 보정:** 전각 문자(2칸, 한글 등)와 반각 문자(1칸, 영문/숫자)를 자동으로 판별하여, 문자열 출력 시 레이아웃이 깨지지 않도록 자동 보정(Leading/Trailing Byte 처리)합니다.

### 🎨 강력한 에셋 시스템 (Asset System)
- **TXT 스프라이트 로드:** 아스키 아트로 그려진 `.txt` 파일을 읽어 게임 오브젝트로 사용합니다.
- **색상 매핑 (Color Mapping):** 별도의 색상 데이터 파일을 통해 픽셀(글자) 단위로 정교한 색상을 입힐 수 있습니다.
- **커스텀 그래픽 폰트:** 직접 디자인한 폰트 파일을 로드하여 게임 타이틀이나 HUD에 그래픽 텍스트를 출력할 수 있습니다.

---

## 📦 설치 및 파일 구성 (Installation)

이 프로젝트는 정적 라이브러리 혹은 소스 코드 형태로 포함하여 사용할 수 있습니다. 아래 파일들을 프로젝트 디렉토리에 포함시키세요.

* `header.h`: 엔진의 클래스 및 열거형 선언부
*  `framework.h`: 필수 의존성 헤더
* `YSConsoleGameEngineLib.cpp`: 엔진 구현부 (소스 코드)

---

## 🚀 사용 예제 (Getting Started)

아래는 엔진을 사용하여 간단한 스프라이트를 렌더링하는 기본 예제입니다.

```cpp
#include "header.h"

int main() {
    // 1. 스크린 초기화 (더블 버퍼링 및 윈도우 크기 설정)
    Screen screen;
    screen.setTitle(L"My Console Game");

    // 2. 에셋(플레이어) 생성
    Asset player(10, 5); // x=10, y=5 위치 생성
    
    // player.txt 파일에서 모양 로드 (프로젝트 폴더에 파일 필요)
    player.LoadS("player.txt"); 
    player.setAllColor(Color::GREEN); // 전체 초록색 설정

    // 3. 게임 루프
    while (true) {
        // [로직 처리]
        // 예: 입력에 따라 player 좌표 이동 등...

        // [렌더링 파이프라인]
        screen.resetBuffer();       // 1. 버퍼 비우기
        
        player.Draw(&screen);       // 2. 플레이어 그리기 (메모리)
        
        screen.write(0, 0, L"Frame: Running...", Color::WHITE); // 3. UI 텍스트 출력

        screen.Display();           // 4. 화면 송출 (Swap Buffer)
    }

    return 0;
}
```
## 📂 에셋 파일 포맷 (Asset File Formats)

이 엔진은 별도의 이미지 포맷 대신 `.txt` 파일을 읽어 그래픽으로 변환합니다. 프로젝트 폴더에 텍스트 파일을 만들고 아래 규칙에 따라 작성하세요.

### 1. 스프라이트 파일 (`LoadS`용)
단순한 아스키 아트를 텍스트 파일에 저장하면 됩니다. `LoadS("filename.txt")`로 로드합니다.

**예시 (`player.txt`):**
```text
  O  
 /|\ 
 / \ 
````

### 2\. 색상 데이터 파일 (`LColor`용)

각 글자(픽셀)에 입힐 색상 코드를 숫자로 적습니다. 스프라이트 파일과 줄바꿈 형식이 일치해야 합니다. (숫자는 띄어쓰기로 구분)

**예시 (`player_color.txt`):**

```text
  14             
 10 10 10        
 9   9           
```

*(위 예시: 머리는 노란색(14), 몸통은 초록색(10), 다리는 파란색(9)으로 칠해짐)*

### 3\. 커스텀 폰트 파일 (`LoadF`용)

그래픽 폰트는 **한 글자당 4줄**의 높이를 가져야 합니다. 엔진은 텍스트 파일을 4줄씩 끊어서 하나의 글자(스프라이트)로 인식합니다.

**예시 (`font.txt`):**

```text
 __  
/  \ 
|__| 
     
 __  
|__) 
|__) 
     
```

*(위 예시: A와 B를 순서대로 정의함)*

-----

## 📚 API Reference

### 🖥️ Screen Class (화면 및 렌더링 관리)

| 함수명 | 설명 |
| :--- | :--- |
| `Screen()` | **생성자**. 유니코드 모드를 켜고 더블 버퍼링용 스크린 2개를 초기화합니다. |
| `setWindowSize(w, h)` | 콘솔 창의 너비(w)와 높이(h)를 설정합니다. |
| `setFont(w, h, name)` | 폰트 크기(가로/세로)와 글꼴 이름(예: L"Consolas")을 설정합니다. |
| `setTitle(wstring)` | 콘솔 창의 상단 제목을 변경합니다. |
| `resetBuffer()` | 버퍼를 배경색으로 초기화합니다. (매 프레임 시작 시 호출 권장) |
| `Display()` | 메모리에 그려진 버퍼를 실제 모니터 화면으로 전송(Swap)합니다. |
| `write(x, y, str, col)` | 지정된 좌표에 문자열을 출력합니다. (한글 자동 보정 지원) |
| `setBackground(char)` | `resetBuffer()` 시 채워질 기본 배경 문자를 설정합니다. |
| `disableResize()` | 사용자가 마우스로 창 크기를 조절하지 못하도록 막습니다. |

### 👾 Asset Class (오브젝트 및 스프라이트 관리)

| 함수명 | 설명 |
| :--- | :--- |
| `Asset(x, y)` | 좌표 (x, y)에 위치한 에셋 객체를 생성합니다. |
| `LoadS(filepath)` | 텍스트 파일에서 **일반 스프라이트** 모양을 로드합니다. |
| `LoadF(filepath)` | 텍스트 파일에서 **커스텀 폰트** 데이터를 로드합니다. (4줄 단위 청크) |
| `LColor(filepath)` | 색상 데이터 파일(숫자 배열)을 로드하여 스프라이트에 적용합니다. |
| `setAllColor(color)` | 스프라이트 전체를 **단색**으로 설정합니다. |
| `Draw(Screen*)` | `Screen` 객체를 통해 현재 에셋을 버퍼에 그립니다. |
| `inputStr(Screen*, x, y, str)` | `LoadF`로 로드된 커스텀 폰트를 사용하여, (x, y)에 그래픽 문자열을 출력합니다. |
| `setX(n) / setY(n)` | 에셋의 X, Y 좌표를 변경합니다. |

-----

## 🎨 색상 코드표 (Color Reference)

`header.h`의 `enum Color`를 사용하거나 아래의 정수값을 사용할 수 있습니다.

| Value | Color Name | Preview | Value | Color Name | Preview |
| :---: | :--- | :--- | :---: | :--- | :--- |
| **0** | **BLACK** | ⚫ 검정 | **8** | **DARK\_GRAY** | ⚫ 어두운 회색 |
| **1** | **DARK\_BLUE** | 🔵 어두운 파랑 | **9** | **BLUE** | 🔵 파랑 |
| **2** | **DARK\_GREEN** | 🟢 어두운 초록 | **10** | **GREEN** | 🟢 초록 |
| **3** | **DARK\_SKY** | 🔵 어두운 하늘 | **11** | **SKY** | 💠 하늘색 |
| **4** | **DARK\_RED** | 🔴 어두운 빨강 | **12** | **RED** | 🔴 빨강 |
| **5** | **DARK\_PURPLE** | 🟣 어두운 보라 | **13** | **PURPLE** | 🟣 보라 |
| **6** | **DARK\_YELLOW** | 🟡 어두운 노랑 | **14** | **YELLOW** | 🟡 노랑 |
| **7** | **GRAY** | ⚪ 회색 | **15** | **WHITE** | ⚪ 흰색 |

-----

## 📝 라이선스 (License)

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

```
```
