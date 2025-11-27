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
* `CYS.h`, `framework.h`: 필수 의존성 헤더
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
