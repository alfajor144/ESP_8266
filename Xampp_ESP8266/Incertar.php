<?php
error_reporting(E_ALL ^ E_NOTICE);
$conexion = mysqli_connect('localhost', 'root', '');
mysqli_select_db($conexion,'ESP8266_THP');
mysqli_query($conexion, "SET NAMES 'utf8");
$temperatura = $_POST['temp'];
$humedad = $_POST['hum'];
$presion = $_POST['pres'];

mysqli_query($conexion,"INSERT INTO datos (Id, Fecha, Temperatura, Humedad, Presion) VALUES (NULL, CURRENT_TIMESTAMP, '$temperatura', '$humedad', $presion);");
mysqli_close($conexion);
echo "Datos ingresados correctamente!";
?>