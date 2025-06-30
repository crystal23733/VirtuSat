# 사용할 컴파일러 설정
CC = gcc # C 파일용 컴파일러
CXX = g++ # C++ 파일용 컴파일러

# 공통 컴파일 옵션
CFLAGS = -Wall -g -Iinclude # C: 경고 표시, 디버깅 정보, include 디렉토리 포함
CXXFLAGS = -Wall -g -Iinclude # C++: 위와 동일

# 파일 그룹 설정 (필요 시 .cpp 파일 추가 가능)
SRC_SAT_C = src/main_satellite.c src/network.c src/sensor.c src/protocol.c
SRC_GND_C = src/main_ground.c src/network.c src/protocol.c

SRC_SAT_CPP =     # 예: src/satellite_helper.cpp
SRC_GND_CPP =     # 예: src/ground_logger,cpp

# 타겟(출력 실행파일) 이름
TARGET_SAT = build/satellite
TARGET_GND = build/ground

# 기본 타겟: 위성과 지상국 둘 다 컴파일
all: satellite ground

# 위성 프로그램 빌드
satellite: $(SRC_SAT_C)
	$(CC) $(CFLAGS) $(SRC_SAT_C) -o $(TARGET_SAT)

ground: $(SRC_GND_C)
	$(CC) $(CFLAGS) $(SRC_GND_C) -o $(TARGET_GND)

# 파일 삭제 (정리용)
clean:
	rm -f $(TARGET_SAT) $(TARGET_GND)
