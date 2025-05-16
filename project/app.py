from flask import Flask, render_template, request, redirect, session
import csv
import os

app = Flask(__name__)
app.secret_key = "super_secret"

DATA_FILE = "data/patients.csv"
USERS = {}  # In-memory user store for demo; replace with DB in prod

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        role = request.form["role"]
        username = request.form["username"]
        password = request.form["password"]
        if username in USERS and USERS[username]["password"] == password and USERS[username]["role"] == role:
            session["user"] = username
            session["role"] = role
            return redirect("/patients" if role == "doctor" else "/")
        else:
            return "Invalid credentials", 403
    return render_template("login.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        role = request.form["role"]
        username = request.form["username"]
        password = request.form["password"]
        USERS[username] = {"password": password, "role": role}
        return redirect("/login")
    return render_template("register.html")

@app.route("/patients")
def patients():
    if session.get("role") != "doctor":
        return "Access denied", 403

    patients = []
    if os.path.exists(DATA_FILE):
        with open(DATA_FILE, newline='') as f:
            reader = csv.DictReader(f)
            for row in reader:
                patients.append(row)
    return render_template("patient_list.html", patients=patients)

@app.route("/mark_treated/<id>", methods=["POST"])
def mark_treated(id):
    update_patient_status(id, "Treated")
    return redirect("/patients")

@app.route("/remove_patient/<id>", methods=["POST"])
def remove_patient(id):
    remove_patient_by_id(id)
    return redirect("/patients")

# Helper functions
def update_patient_status(pid, status):
    updated = []
    with open(DATA_FILE, newline='') as f:
        reader = csv.DictReader(f)
        for row in reader:
            if row['id'] == pid:
                row['status'] = status
            updated.append(row)

    with open(DATA_FILE, 'w', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=["id", "name", "severity", "status"])
        writer.writeheader()
        writer.writerows(updated)

def remove_patient_by_id(pid):
    remaining = []
    with open(DATA_FILE, newline='') as f:
        reader = csv.DictReader(f)
        for row in reader:
            if row['id'] != pid:
                remaining.append(row)

    with open(DATA_FILE, 'w', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=["id", "name", "severity", "status"])
        writer.writeheader()
        writer.writerows(remaining)

if __name__ == "__main__":
    app.run(debug=True)
