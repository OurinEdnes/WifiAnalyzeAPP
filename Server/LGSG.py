from flask import Flask, request, jsonify
from flask_cors import CORS
import subprocess
import sys
import os

sys.stdout.reconfigure(encoding='utf-8')

app = Flask(__name__)
CORS(app, origins=["http://127.0.0.1:5501"])


@app.route("/auth", methods=["POST"])
def auth():
    try:
        data = request.json
        mode = data["mode"]
        user = data["username"]
        passwd = data["password"]

        print(f"[INFO] Mode: '{mode}', Username: '{user}', Password: '{passwd}'")

        result = subprocess.run(
            ["C:/xampp/htdocs/WifiAnalyze/BackEnd/LGSG.exe", mode, user, passwd],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )

        stdout_lines = result.stdout.strip().splitlines()
        stderr_lines = result.stderr.strip().splitlines()

        print("===== STDOUT dari LGSG.exe =====")
        for line in stdout_lines:
            print(line)
        print("===== END STDOUT =====")

        if stderr_lines:
            print("===== STDERR dari LGSG.exe =====")
            for line in stderr_lines:
                print(line)
            print("===== END STDERR =====")

        status = stdout_lines[-1] if stdout_lines else "FAIL"
        print(f"[RESULT] Status = {status}")
        return jsonify({ "status": status })

    except Exception as e:
        print("[EXCEPTION]", e)
        return jsonify({ "status": "SERVER_ERROR" }), 500


@app.route("/get_wifi_data", methods=["POST"])
def get_wifi_data():
    try:
        data = request.get_json()
        username = data.get("username")

        exe_path = os.path.abspath("C:/xampp/htdocs/WifiAnalyze/BackEnd/ReadSpeed.exe")
        result = subprocess.run(
            [exe_path, username],
            capture_output=True, text=True, timeout=5
        )

        output = result.stdout.strip()
        err = result.stderr.strip()

        if err:
            print("⚠️ ERROR dari ReadSpeed.exe:")
            print(err)

        return jsonify({ "wifi_speed": output })

    except Exception as e:
        print("[EXCEPTION get_wifi_data]", e)
        return jsonify({ "wifi_speed": "Gagal ambil data.\n" + str(e) }), 500


@app.route("/get_sorted_ap_data", methods=["POST"])
def get_sorted_ap_data():
    try:
        data = request.get_json()
        username = data.get("username")
        order = data.get("order", "asc")

        print(f"[INFO] Fetch sorted AP untuk {username} | Order: {order}")

        exe_path = os.path.abspath("C:/xampp/htdocs/WifiAnalyze/BackEnd/BackEnd/ReadSpeedSort.exe")
        result = subprocess.run(
            [exe_path, username, order.upper()],
            capture_output=True, text=True, timeout=5
        )

        output = result.stdout.strip()
        err = result.stderr.strip()

        if err:
            print("⚠️ ERROR dari SortSpeed.exe:")
            print(err)

        return jsonify({ "wifi_speed": output })

    except Exception as e:
        print("[EXCEPTION get_sorted_ap_data]", e)
        return jsonify({ "wifi_speed": "Gagal ambil data sorted.\n" + str(e) }), 500


@app.route("/get_total_lantai_speed", methods=["POST"])
def get_total_lantai_speed():
    try:
        data = request.get_json()
        username = data.get("username")
        order = data.get("order", "asc")  # default asc

        print(f"[INFO] Fetch total per lantai untuk user: {username}, Urutan: {order}")

        exe_path = os.path.abspath("C:/xampp/htdocs/WifiAnalyze/BackEnd/ReadSpeedByLantai.exe")
        result = subprocess.run(
            [exe_path, username, order.upper()],
            capture_output=True, text=True, timeout=5
        )

        output = result.stdout.strip()
        err = result.stderr.strip()

        if err:
            print("⚠️ ERROR dari ReadSpeedByLantai.exe:")
            print(err)

        return jsonify({ "wifi_speed": output })

    except Exception as e:
        print("[EXCEPTION get_total_lantai_speed]", e)
        return jsonify({ "wifi_speed": "Gagal ambil data total per lantai.\n" + str(e) }), 500

@app.route("/get_wifi_config", methods=["POST"])
def get_wifi_config():
    try:
        data = request.get_json()
        username = data.get("username")

        print(f"[INFO] Fetch wifi config untuk user: {username}")

        exe_path = os.path.abspath("C:/xampp/htdocs/WifiAnalyze/BackEnd/ReadConfig.exe")
        result = subprocess.run(
            [exe_path, username],
            capture_output=True, text=True, timeout=5
        )

        output = result.stdout.strip()
        err = result.stderr.strip()

        if err:
            print("⚠️ ERROR dari ReadConfig.exe:")
            print(err)

        return jsonify({ "wifi_config": output })

    except Exception as e:
        print("[EXCEPTION get_wifi_config]", e)
        return jsonify({ "wifi_config": "Gagal ambil konfigurasi.\n" + str(e) }), 500

@app.route("/get_wifi_users", methods=["POST"])
def get_wifi_users():
    try:
        data = request.get_json()
        username = data.get("username")

        print("="*40)
        print(f"[INFO] Endpoint: /get_wifi_users")
        print(f"[INFO] Fetch pengguna wifi untuk user: '{username}'")

        exe_path = os.path.abspath("C:/xampp/htdocs/WifiAnalyze/BackEnd/ReadUser.exe")
        print(f"[DEBUG] Jalankan EXE: {exe_path} {username}")

        result = subprocess.run(
            [exe_path, username],
            capture_output=True, text=True, timeout=5
        )

        output = result.stdout.strip()
        err = result.stderr.strip()

        print("[DEBUG] STDOUT dari ReadUser.exe:")
        print(output if output else "(kosong)")
        print("[DEBUG] STDERR dari ReadUser.exe:")
        print(err if err else "(kosong)")
        print("="*40)

        return jsonify({ "user_data": output })

    except Exception as e:
        print("[EXCEPTION get_wifi_users]", e)
        return jsonify({ "user_data": "Gagal ambil pengguna.\n" + str(e) }), 500

@app.route("/search_user", methods=["POST"])
def search_user():
    try:
        data = request.get_json()
        username = data.get("username")
        target_name = data.get("target")

        base_dir = r"C:\xampp\htdocs\WifiAnalyze\BackEnd"
        exe_path = os.path.join(base_dir, "SearchUser.exe")
        user_folder = os.path.join(base_dir, f"UserData({username})")
        print("PATH EXE:", exe_path)
        print("PATH FOLDER USER:", user_folder)
        print("ARGS:", [exe_path, user_folder, target_name])
        print("CWD:", os.getcwd())

        if not os.path.isfile(exe_path):
            print("[ERROR] File exe tidak ditemukan:", exe_path)
            return jsonify({"search_result": f"ERROR: File exe tidak ditemukan: {exe_path}"}), 500
        if not os.path.isdir(user_folder):
            print("[ERROR] Folder user tidak ditemukan:", user_folder)
            return jsonify({"search_result": f"ERROR: Folder user tidak ditemukan: {user_folder}"}), 500

        result = subprocess.run(
            [exe_path, user_folder, target_name],
            capture_output=True, text=True, timeout=5
        )

        output = result.stdout.strip()
        err = result.stderr.strip()

        if err:
            print("⚠️ ERROR dari SearchUser.exe:")
            print(err)

        return jsonify({ "search_result": output })

    except Exception as e:
        print("[EXCEPTION search_user]", e)
        return jsonify({ "search_result": "Gagal mencari pengguna.\n" + str(e) }), 500

if __name__ == "__main__":
    app.run(port=5000)
