from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/data', methods=['POST'])
def receive_data():
    for i in range(10):
        print("Пойман")
    # Проверяем, что данные пришли в формате JSON
    if not request.is_json:
        return jsonify({"status": "error", "message": "Request must be JSON"}), 400

    # Получаем данные из запроса
    data = request.get_json()

    # Проверяем, что данные содержат необходимые поля
    if "sensor" not in data or "value" not in data:
        return jsonify({"status": "error", "message": "Missing 'sensor' or 'value' in data"}), 400

    # Выводим полученные данные
    print(f"Received data: {data}")

    # Здесь можно добавить обработку данных (например, сохранение в базу данных)

    # Отправляем подтверждение
    return jsonify({"status": "success", "message": "Data received", "received_data": data}), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
