# Byeongjeom Highschool Dinner Checker 
This program is for byeongjeom highschool 

## 알림
1. 이 프로그램은 리눅스에서 테스트되었습니다. 모든 코드는 윈도우에서 작동하도록 짜여졌으나, 설정 파일은 리눅스에 맞춰져 있기에 윈도우에서 사용하기 위해서는 윈도우에 맞는 설정 파일을 구성해야 합니다.
2. app 폴더의 내용은 실사용을 위한 flask 프로그램 폴더이고, app_qr 폴더는 qrcode 생성기 flask 프로그램 폴더, app_test 폴더는 테스트 및 디버깅을 위해 생성한 flask 프로그램 폴더입니다.
3. app, app_qr, app_test 의 프로그램은 각각 포트 8080, 8081, 8082가 지정되어 있습니다.
4. 비디오를 이용한 qr코드 인식은 https 에서만 정상적으로 작동합니다. 만약 https 지원이 불가능한 상황이라면 app/templates/index.html 의 ```
```
<video id="qr-video" width="516" height="387" style="display: block; margin: 0 auto;" muted autoplay playsinline></video>
```
부분을
```
<!--
<video id="qr-video" width="516" height="387" style="display: block; margin: 0 auto;" muted autoplay playsinline></video>
-->
```
와 같이 주석문처리해주세요.
5. 라이브러리 컴파일시 CPython 헤더 파일의 경로가 달라 오류가 발생할 수 있습니다. 적절한 위치에 있는 Python.h 헤더 파일을 include 해주세요.

## 설치 

### git 설치 후 clone 하기 
``` 
git clone https://github.com/CVEzeroday/dinner_check.git 
``` 
혹은 오른쪽 상단 code 클릭 후 Download ZIP 으로 다운로드 

### 파이썬 모듈 설치하기 
#### Linux 
``` 
cd dinner_check 
./install.sh 
``` 
#### Windows PowerShell 
``` 
cd dinner_check 
mkdir data 
python setup.py install 
``` 

### 파이썬에서 사용하기 
``` 
import dinnerchecker 
``` 

## 프로그램 실행

### 이 과정을 수행하기 위해서는 필요한 파이썬 모듈 및 자체 제작 파이썬 모듈이 설치되어 있어야 합니다.
```
python -m pip install flask waitress chardet
```

### 메인 앱 실행하기
```
./app/start.sh
./app_qr/start.sh
```

## 함수

### initializeJsonFile()
1. 입력: none
2. 입력값 자료형: none
3. 출력: 0 (고정)
4. 출력값 자료형: number
5. 설명:
- 새로운 날짜의 json 파일을 생성함
- 전 날짜의 학생 입력 정보들은 유지함

### saveStudentData(id, name, isChecked) 
1. 입력: (학번, 이름, 체크여부)
2. 입력값 자료형: (number, string, bool) 
3. 출력: 0 (고정) 
4. 출력값 자료형: number 
5. 설명: 
- json 파일에 학생을 추가함 


### uncheckStudent(id) 
1. 입력: (학번) 
2. 입력값 자료형: (number) 
3. 출력: 
- 0: 정상적으로 실행됨 
- 1: 입력한 학번의 학생 데이터가 없음 
4. 출력값 자료형: number 
5. 설명: 
- 입력한 학번의 학생의 체크 데이터를 false로 변경함 


### checkStudent(id) 
1. 입력: (학번) 
2. 입력값 자료형: (number) 
3. 출력: 
- 0: 정상적으로 실행됨 
- 1: 입력한 학번의 학생 데이터가 없음 
4. 출력값 자료형: number 
5. 설명: 
- 입력한 학번의 학생의 체크 데이터를 true로 변경함 


### getSpecificStudentData(id) 
1. 입력: (학번) 
2. 입력값 자료형: (number) 
3. 출력: 
``` 
{ 
      "studentNumber": 학번 (number), 
          "name": 이름 (string), 
          "isChecked": 체크 여부 (bool), 
          "date": 체크 시간 (string) 
} 
``` 
4. 출력값 자료형: Dictionary 
5. 설명: 
- 입력한 학번의 학생의 학번, 이름, 체크 데이터, 체크 시간을 딕셔너리 형식으로 반환함 
- 주의: 여러 명의 학생 데이터가 필요한 경우, 이 함수를 여러 번 호출하는 것은 성능적으로 손해가 발생하므로 getStudentsData를 사용하는 것을 권장 


### getSpecificStudentDataofDate(date, id) 
1. 입력: (날짜, 학번) 
2. 입력값 자료형: (string, int) 
3. 출력: 
``` 
{ 
      "studentNumber": 학번 (number), 
          "name": 이름 (string), 
          "isChecked": 체크 여부 (bool), 
          "date": 체크 시간 (string) 
} 
``` 
4. 출력값 자료형: Dictionary 
5. 설명: 
- 특정 날짜의 입력한 학번의 학생의 학번, 이름, 체크 데이터, 체크 시간을 딕셔너리 형식으로 반환함 
- 날짜를 입력할 때는 "20230504" 와 같은 형식으로 해야 함 (필수) 
- 주의: 여러 명의 학생 데이터가 필요한 경우, 이 함수를 여러 번 호출하는 것은 성능적으로 손해가 발생하므로 getStudentsDataofDate를 사용하는 것을 권장 


### getStudentsData() 
1. 입력: none 
2. 입력값 자료형: none 
3. 출력:  
``` 
[ 
      { 
            "studentNumber": 학번 (number), 
                "name": 이름 (string), 
                "isChecked": 체크 여부 (bool), 
                "date": 체크 시간 (string) 
                  }, 
                  ... 
] 
``` 
4. 출력값 자료형: List of Dictionary 
5. 설명: 
- 모든 학생의 데이터를 리스트 형식으로 반환함 


### getStudentsDataofDate(date) 
1. 입력: (날짜) 
2. 입력값 자료형: (string) 
3. 출력: 
``` 
[ 
      { 
            "studentNumber": 학번 (number), 
            "name": 이름 (string), 
            "isChecked": 체크 여부 (bool), 
            "date": 체크 시간 (string) 
              }, 
              ... 
] 
``` 
4. 출력값 자료형: List of Dictionary 
5. 설명: 
- 특정 날짜의 모든 학생의 데이터를 리스트 형식으로 반환함 
- 날짜를 입력할 때는 "20230504" 와 같은 형식으로 해야 함 (필수) 

### resetJsonFile()
1. 입력: none
2. 입력값 자료형: none
3. 출력: 0 (고정)
4. 출력값 자료형: number
5. 설명:
- 새로운 날짜의 json 파일을 생성함
- 그 날짜의 json 파일의 학생 정보들을 초기화함 (체크가 풀림)
- 전 날짜의 학생 입력 정보들은 유지함
