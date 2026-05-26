# Manual de Instalación

## 1. Requisitos

- Docker
- Docker Compose
- Arduino IDE
- ESP32
- Node-RED
- Eclipse Mosquitto
- MySQL

---

# 2. Clonar Repositorio

```bash
git clone URL_REPOSITORIO
```

---

# 3. Configurar MQTT TLS

Ubicar certificados TLS dentro de la carpeta:

```bash
mosquitto/certs/
```

Archivos requeridos:

- ca.crt
- server.crt
- server.key

---

# 4. Configurar ESP32

Crear los archivos:

- config.h
- certificates.h

basados en:

- config.example.h
- certificates.example.h

---

# 5. Ejecutar Contenedores Docker

Desde la carpeta principal ejecutar:

```bash
docker-compose up -d
```

---

# 6. Verificar Servicios

Comprobar ejecución:

```bash
docker ps
```

Servicios esperados:

- Mosquitto MQTT
- Node-RED
- MySQL

---

# 7. Acceder a Node-RED

Abrir navegador:

```bash
http://localhost:1880
```

---

# 8. Cargar Código ESP32

Abrir:

```bash
esp32/esp32_riego.ino
```

Compilar y cargar utilizando Arduino IDE.

---

# 9. Verificar Comunicación MQTT

Topics utilizados:

- riego/sensores
- riego/control

Puerto seguro TLS:

```bash
8883
```

---

# 10. Funcionamiento General

El ESP32 enviará datos de sensores hacia MQTT y Node-RED ejecutará automáticamente la lógica de control del sistema de riego.
