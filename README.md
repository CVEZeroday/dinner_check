# Byeongjeom Highschool Dinner Checker
This program is for byeongjeom highschool

## 설치

1. git 설치 후 clone 하기
```
git clone https://github.com/CVEzeroday/dinner_check.git
```
혹은 오른쪽 상단 code 클릭 후 Download ZIP 으로 다운로드

2. 파이썬 모듈 설치하기
### Linux
```
cd dinner_check
./install.sh
```
### Windows PowerShell
```
cd dinner_check
mkdir data
python setup.py install
```

3. 파이썬에서 사용하기
```
import dinnerchecker
```

## 함수

### initializeJsonFile()
1. 입력: none
2. 입력값 자료형: none
3. 출력: 0 (고정)
4. 출력값 자료형: number
5. 설명:
- 새로운 날짜의 json 파일을 생성함
- 그 날짜의 json 파일의 학생 정보들을 초기화함 (체크가 풀림)
- 전 날짜의 학생 입력 정보들은 유지함


### saveStudentData(id, name, isChecked)
1. 입력: (학번, 이름, 체크여부)
2. 입력값 자료형: (number, string, bool)
3. 출력: 0 (고정)
4. 출력값 자료형: number
5. 설명:
- json 파일에 학생을 추가함


### uncheckStudent(id)
1. 입력: (학번)
2. 입력값 자료형: (number)
3. 출력:
- 0: 정상적으로 실행됨
- 1: 입력한 학번의 학생 데이터가 없음
4. 출력값 자료형: number
5. 설명:
- 입력한 학번의 학생의 체크 데이터를 false로 변경함


### checkStudent(id)
1. 입력: (학번)
2. 입력값 자료형: (number)
3. 출력:
- 0: 정상적으로 실행됨
- 1: 입력한 학번의 학생 데이터가 없음
4. 출력값 자료형: number
5. 설명:
- 입력한 학번의 학생의 체크 데이터를 true로 변경함


### getSpecificStudentData(id)
1. 입력: (학번)
2. 입력값 자료형: (number)
3. 출력:
```
{
  "studentNumber": 학번 (number),
  "name": 이름 (string),
  "isChecked": 체크 여부 (bool),
  "date": 체크 시간 (string)
}
```
4. 출력값 자료형: Dictionary
5. 설명:
- 입력한 학번의 학생의 학번, 이름, 체크 데이터, 체크 시간을 딕셔너리 형식으로 반환함
- 주의: 여러 명의 학생 데이터가 필요한 경우, 이 함수를 여러 번 호출하는 것은 성능적으로 손해가 발생하므로 getStudentsData를 사용하는 것을 권장


### getSpecificStudentDataofDate(date, id)
1. 입력: (날짜, 학번)
2. 입력값 자료형: (string, int)
3. 출력:
```
{
  "studentNumber": 학번 (number),
  "name": 이름 (string),
  "isChecked": 체크 여부 (bool),
  "date": 체크 시간 (string)
}
```
4. 출력값 자료형: Dictionary
5. 설명:
- 특정 날짜의 입력한 학번의 학생의 학번, 이름, 체크 데이터, 체크 시간을 딕셔너리 형식으로 반환함
- 날짜를 입력할 때는 "20230504" 와 같은 형식으로 해야 함 (필수)
- 주의: 여러 명의 학생 데이터가 필요한 경우, 이 함수를 여러 번 호출하는 것은 성능적으로 손해가 발생하므로 getStudentsDataofDate를 사용하는 것을 권장


### getStudentsData()
1. 입력: none
2. 입력값 자료형: none
3. 출력: 
```
[
  {
    "studentNumber": 학번 (number),
    "name": 이름 (string),
    "isChecked": 체크 여부 (bool),
    "date": 체크 시간 (string)
  },
  ...
]
```
4. 출력값 자료형: List of Dictionary
5. 설명:
- 모든 학생의 데이터를 리스트 형식으로 반환함


### getStudentsDataofDate(date)
1. 입력: (날짜)
2. 입력값 자료형: (string)
3. 출력:
```
[
  {
    "studentNumber": 학번 (number),
    "name": 이름 (string),
    "isChecked": 체크 여부 (bool),
    "date": 체크 시간 (string)
  },
  ...
]
```
4. 출력값 자료형: List of Dictionary
5. 설명:
- 특정 날짜의 모든 학생의 데이터를 리스트 형식으로 반환함
- 날짜를 입력할 때는 "20230504" 와 같은 형식으로 해야 함 (필수)


### deleteStudentData(id)
1. 입력: (학번)
2. 입력값 자료형: (number)
3. 출력:
- 0: 정상적으로 실행됨
- 1: 입력한 학번의 학생 데이터가 없음
4. 출력값 자료형: number
5. 설명:
- 입력한 학번의 학생 데이터를 삭제함
- 이전 날짜의 학생 데이터는 삭제되지 않음
- 주의: 한 번 삭제하면 복구할 수 없음
