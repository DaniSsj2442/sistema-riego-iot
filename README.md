# sistema-riego-iot
Sistema inteligente de riego basado en IoT usando ESP32, MQTT TLS, Node-RED y Docker. Implementando diferentes métodos de seguridad como SSL, usuarios MQTT.

# Sistema Inteligente de Riego IoT

Sistema inteligente de riego automatizado basado en tecnologías IoT utilizando ESP32, MQTT seguro mediante TLS, Node-RED, Docker y MySQL.

---

# Características

- Monitoreo de humedad del suelo en tiempo real.
- Detección de luminosidad ambiente.
- Activación automática de bomba de agua.
- Comunicación MQTT mediante TLS.
- Dashboard interactivo con Node-RED.
- Almacenamiento histórico en MySQL.
- Arquitectura basada en Docker Compose.
- Integración de hardware real.

---

# Arquitectura del Sistema

El sistema está compuesto por:

- ESP32
- Sensores de humedad y luminosidad
- Broker MQTT Mosquitto
- Node-RED
- Base de datos MySQL
- Docker Compose
- Relé + ULN2003AN
- Bomba de agua

---

# Seguridad

La comunicación MQTT fue implementada utilizando:

- TLS/SSL
- Certificados digitales
- Autenticación mediante usuario y contraseña
- Puerto seguro 8883

---

# Topics MQTT

| Topic | Función |
|---|---|
| `riego/sensores` | Publicación de variables ambientales |
| `riego/control` | Comandos de activación de riego |

---

# Estructura del Proyecto

```bash
docs/           -> Informe y documentación
esp32/          -> Código ESP32
mosquitto/      -> Configuración MQTT TLS
node-red/       -> Flujos Node-RED
database/       -> Scripts SQL
```

---

# Tecnologías Utilizadas

- ESP32
- Arduino IDE
- MQTT
- Eclipse Mosquitto
- Node-RED
- Docker
- Docker Compose
- MySQL
- TLS/SSL

---

# ⚙️ Instalación General

## 1. Clonar repositorio

```bash
git clone URL_REPOSITORIO
```

## 2. Configurar Mosquitto

Agregar certificados TLS y usuarios MQTT.

## 3. Ejecutar Docker Compose

```bash
docker-compose up -d
```

## 4. Configurar ESP32

Completar:

- config.h
- certificates.h

## 5. Cargar código al ESP32

Usando Arduino IDE.

---

# Dashboard

El sistema incluye monitoreo visual en tiempo real utilizando Node-RED Dashboard.

---

# Autor

Daniel Santiago Pereira Alvarez

Proyecto académico - Redes y Telecomunicaciones
