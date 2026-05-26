CREATE DATABASE IF NOT EXISTS riego_iot;

USE riego_iot;

CREATE TABLE sensores (

    id INT AUTO_INCREMENT PRIMARY KEY,

    humedad INT,

    adc_humedad INT,

    luz INT,

    adc_luz INT,

    estado_luz VARCHAR(20),

    dispositivo VARCHAR(50),

    fecha TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
