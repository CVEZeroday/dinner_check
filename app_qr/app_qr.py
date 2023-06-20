from flask import Flask, render_template, request
import dinnerchecker as d
from waitress import serve

student_csv_data = []

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html", res=-1)


@app.route("/studentp", methods=["POST"])
def studentp():
    try:
        student_number = int(request.form["student_number"])
        student_data = dict(d.getSpecificStudentData(student_number))
        result = student_data["studentNumber"]
        if result != -1:
            return render_template("index.html",str="{}번 학생의 QR코드입니다. 스크린샷으로 저장해주세요.".format(student_number),res=student_number)
        else:
            return render_template("index.html",str="{}번 학생은 등록되지 않은 학생입니다. 입력을 확인해주세요.".format(student_number),res=result)
    except ValueError:
        return render_template("index.html",str="입력값은 정수여야 합니다.",res=-1)


serve(app, host='0.0.0.0', port=8081)
