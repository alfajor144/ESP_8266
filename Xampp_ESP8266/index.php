<!DOCTYPE html>
<html>
	<head>
        <title>Ver usuarios BD</title>
        <script src="https://code.highcharts.com/highcharts.js"></script>
        <script src="https://code.highcharts.com/modules/exporting.js"></script>
        <script src="https://code.highcharts.com/modules/export-data.js"></script>
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
	</head>

	<body> 
	<style type="text/css">
		table {
			border-collapse: collapse;
			border-spacing: 0;
		}
		table {
			border: 0;
		}
		table td, table th {
			border: 2px solid black;
		}
	</style>

<?php
error_reporting(E_ALL ^ E_NOTICE);
$conexion = mysqli_connect('localhost', 'root', '');
mysqli_select_db($conexion,'ESP8266_THP');
mysqli_query($conexion, "SET NAMES 'utf8");

$sql = "SELECT Id, Fecha, Temperatura, Humedad, Presion FROM datos";
$result = mysqli_query($conexion, $sql);

?>

<div id="container" style="min-width: 310px; height: 400px; margin: 0 auto"></div>
<script type="text/javascript">
$(function(){
Highcharts.chart('container', {
    chart: {
        type: 'line'
    },
    title: {
        text: 'Temp & Hum'
    },
    yAxis: {
        title: {
            text: 'Temperature (°C) & Humidity (%) & Pressure (hPa)'
        }
    },
    plotOptions: {
        line: {
            dataLabels: {
                enabled: true
            },
            enableMouseTracking: false
        }
    },
    series: [{
        name: 'Temperature (°C)',
        data: [
            <?php
                if (mysqli_num_rows($result) > 0) {

                    while($row = mysqli_fetch_assoc($result)) {        
                        echo $row["Temperatura"].",";
                    }
                }
            ?>
            ]
    }, {
        name: 'Humidity (%)',
        data: [
            <?php
            $sql = "SELECT Id, Fecha, Temperatura, Humedad, Presion FROM datos";
            $result = mysqli_query($conexion, $sql);
                if (mysqli_num_rows($result) > 0) {

                    while($row = mysqli_fetch_assoc($result)) {        
                        echo $row["Humedad"].",";
                    }
                }
            ?>
        ]
    },{
        name: 'Presion (hPa)',
        data: [
            <?php
            $sql = "SELECT Id, Fecha, Temperatura, Humedad, Presion FROM datos";
            $result = mysqli_query($conexion, $sql);
                if (mysqli_num_rows($result) > 0) {

                    while($row = mysqli_fetch_assoc($result)) { 
                        $pres = (float)$row["Presion"]/100;
                        echo $pres.",";
                    }
                }
            ?>
        ]
    }]
});
});
</script>
<?php
$sql = "SELECT Id, Fecha, Temperatura, Humedad, Presion FROM datos";
$result = mysqli_query($conexion, $sql);

if (mysqli_num_rows($result) > 0) {
    echo "<table>";
    echo "<tr>
            <th>Id</th>
            <th>Fecha</th>
            <th>Temperatura</th>
            <th>Humedad</th>
            <th>Presion</th>
        </tr>";
    while($row = mysqli_fetch_assoc($result)) {
        echo "<tr>";
        echo "<td>".$row["Id"]."</td>";
        echo "<td>".$row["Fecha"]."</td>";
        echo "<td>".$row["Temperatura"]." C</td>";
        echo "<td>".$row["Humedad"]." %</td>";
        echo "<td>".$row["Presion"]." hPa</td>";
        echo "</tr>";
    }
    echo "</table>";
} else {
    echo "<h3>No se encontraron datos.</h3>";
}

mysqli_close($conexion);
?>