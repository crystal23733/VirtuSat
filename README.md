# VirtuSat

가상 위성과 지상국이 실시간으로 통신하는 C 기반 시뮬레이션 프로젝트  
(Ground Station ↔ Satellite, TCP/IP 통신, 구조체 패킷, 명령 송수신)

---

## 🛰️ 프로젝트 소개

VirtuSat은 실제 인공위성 통신처럼  
- **"위성" 프로그램**과 **"지상국" 프로그램**이
- 네트워크(인터넷 또는 같은 PC)로
- 센서 데이터/명령어를 주고받는 C 프로젝트입니다.

실제 산업(위성·방산·임베디드 등)에서 사용하는  
네트워크/메모리/구조체/멀티스레드 등 실무 기술을 배울 수 있습니다.

---

## 📦 폴더 구조

```plaintext
VirtuSat/
├── include/              # 공통 헤더 파일 (.h)
│   ├── common.h          # 공통 정의 (구조체, 상수 등)
│   └── protocol.h        # 메시지 포맷 정의
│
├── src/                  # 소스 코드
│   ├── main_satellite.c  # 위성 프로그램 진입점
│   ├── main_ground.c     # 지상국 프로그램 진입점
│   ├── network.c         # TCP 통신 함수
│   ├── sensor.c          # 센서값 시뮬레이션
│   └── command.c         # 명령 처리 모듈
│
├── build/                # 빌드 결과 바이너리 저장
│   ├── satellite         # 위성 실행 파일
│   └── ground            # 지상국 실행 파일
│
├── data/                 # 로그나 CSV 저장
│   └── ground_log.csv
│
├── diagrams/             # 설계도 (flowchart, sequence)
│   └── architecture.png
│
├── README.md             # 프로젝트 설명
├── Makefile              # 빌드 자동화
└── config.h              # 컴파일 옵션, 설정값

````

---

## ⚙️ 주요 기능

* **위성**

  * 랜덤 센서 데이터(온도, 전압, GPS 등) 생성
  * TCP/IP로 지상국에 주기적으로 데이터 전송
  * 지상국의 명령어 수신 및 응답

* **지상국**

  * 위성 접속 및 데이터 수신
  * 명령어 전송 및 응답 수신
  * 수신 데이터 파일(CSV) 저장, 로그 관리

---

## 🏁 빠른 시작 (윈도우, VSCode 기준)

1. **환경 준비**

   * C 컴파일러(GCC/MinGW 등)
   * VSCode 또는 Vim 등 편집기

2. **빌드**

   ```bash
   make
   ```

   * 또는 직접:
     `gcc -o build/satellite src/main_satellite.c ...`
     `gcc -o build/ground src/main_ground.c ...`

3. **실행**

   * 터미널 1:

     ```
     build\satellite.exe
     ```
   * 터미널 2:

     ```
     build\ground.exe
     ```

---

## 🗺️ 개발 순서

1. **설계** (요구사항 정의, 아키텍처/시퀀스 다이어그램)
2. **모듈 개발** (센서, 네트워크, 명령 처리 등)
3. **기능별 테스트 및 통합**
4. **최종 포트폴리오 문서화**
