from flask import Flask, render_template, request, jsonify
import dinnerchecker as d
import csv, os, shutil, chardet
from waitress import serve

student_csv_data = []

app = Flask(__name__)

def detect_encoding(file_path):
    with open(file_path, 'rb') as f:
        result = chardet.detect(f.read())
    return result['encoding']

@app.route("/")
def index():
    return render_template("index.html")


@app.route("/studentp", methods=['POST'])
def studentp():
    try:
        student_number = int(request.form["student_number"])
        student_data = dict(d.getSpecificStudentData(student_number))
        isChecked = student_data["isChecked"]
        result = d.checkStudent(student_number)
        if result == 0:
            if isChecked == False:
                return jsonify({"str":"{}번 학생 출석이 완료되었습니다.".format(student_number), "num": student_number})
            else:
                return jsonify({"str":"{}번 학생은 이미 출석이 확인된 학생입니다.".format(student_number), "num": -1})
        else:
            return jsonify({"str":"{}번 학생은 등록되지 않은 학생입니다. 입력을 확인해주세요.".format(student_number), "num": -1})
    except ValueError:
        return jsonify({"str":"입력값은 정수여야 합니다.", "num": -1})


@app.route("/t_choose")
def t_choose():
    return render_template("t_choose.html")

@app.route("/button_handler", methods=["POST"])
def button_handler():
    button_name = request.form["button"]

    if button_name == "학생등록":
        return render_template("t_choose_1.html")
    elif button_name == "개별 학생 추가 등록":
        return render_template("t_choose_2.html")
    elif button_name == "특정학생 출석기록":
        return render_template("t_choose_3.html")
    #elif button_name == "학생데이터 제거":
    #    return render_template("t_choose_4.html")
    elif button_name == "학생데이터 제거":
        return render_template("t_choose_7.html")
    elif button_name == "오늘일자 출석부 출력":
        return t_choose_5_1()
    elif button_name == "이전날짜 출석부 출력":
        return render_template("t_choose_6.html")


@app.route("/t_choose_7", methods=["POST"])
def t_choose_7():
    date= request.form["day"]
    all_students_delete(date)
    return render_template("t_choose_7_1.html")

def all_students_delete(day):
    file_name = "./data/backup_student_dinner_data.json"
    if  os.path.exists(file_name):   
        os.remove(file_name)
        day = int(day)
        for i in range(day,20230600, -1):
            source_file = f"./data/{i}_student_dinner_data.json"  # 원본 JSON 파일의 경로와 파일명
            destination_file = f"./data/old_data"  # 이동할 JSON 파일의 경로와 파일명
            if os.path.exists(source_file):
                destination_path = os.path.join(
                    destination_file, os.path.basename(source_file)
                )
                shutil.move(source_file, destination_path)
            else:
                continue
        d.initializeJsonFile()
    else:
        return "백업파일이 없습니다."

@app.route("/t_choose_1_1", methods=["POST"])
def t_choose_1_1():
    file = request.files["file"]
    file.save(file.filename)

    # CSV 파일 읽기
    encoding = detect_encoding(file.filename)
    with open(file.filename, mode="r", encoding=encoding) as file:
        reader = csv.reader(file)
        columns = [list(x) for x in zip(*reader)]
        for a in range(len(columns[0])):
            id = int(columns[0][a])
            name = str(columns[1][a])
            d.saveStudentData(id, name, False)

    return "등록이 완료되었습니다."


@app.route("/t_choose_2_1", methods=["POST"])
def t_choose_2_1():
    id = int(request.form["student_number"])
    name = request.form["student_name"]
    d.saveStudentData(id, name, False)
    return "등록이 완료되었습니다."


@app.route("/t_choose_3_1", methods=["POST"])
def t_choose3_1():
    id = int(request.form["student_number"])
    students_data = d.getSpecificStudentData(id)
    
    template_variables = {"students": students_data}
    return render_template("t_choose_3_1.html", **template_variables)


@app.route("/t_choose_4_1", methods=["POST"])
def t_choose_4_1():
    id = int(request.form["student_number"])
    return d.deleteStudentData(id), "{}학번 학생의 데이터가 삭제되었습니다.".format(id)


@app.route("/t_choose_6_1", methods=["POST"])
def t_choose_6_1():
    # 데이터베이스에서 학생 정보를 가져옴
    date = str(request.form["date"])
    students_data = d.getStudentsDataOfDate(date)
    # 템플릿에 전달할 변수 설정
    template_variables = {"students": students_data}
    # 템플릿 렌더링
    return render_template("t_choose_6_1.html", **template_variables)


def t_choose_5_1():
    # 데이터베이스에서 학생 정보를 가져옴
    students_data = d.getStudentsData()
    # 템플릿에 전달할 변수 설정
    template_variables = {"students": students_data}
    # 템플릿 렌더링
    return render_template("t_choose_5_1.html", **template_variables)


#if __name__ == "__main__":
#    app.run(host='0.0.0.0', port=8080)


serve(app, host='0.0.0.0', port=8080)
