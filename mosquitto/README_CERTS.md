# Certificados TLS

En esta carpeta deben ubicarse los certificados utilizados por Mosquitto para habilitar comunicación segura mediante TLS.

Archivos esperados:

- ca.crt
- server.crt
- server.key

Los certificados deben ser generados localmente utilizando OpenSSL o una autoridad certificadora propia.

Ejemplo de generación:

openssl genrsa -out ca.key 2048

openssl req -new -x509 -days 365 -key ca.key -out ca.crt
