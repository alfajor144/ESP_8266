const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="https://code.highcharts.com/highcharts.js"></script>
    <script src="https://code.highcharts.com/modules/series-label.js"></script>
    <script src="https://code.highcharts.com/modules/exporting.js"></script>
    <script src="https://code.highcharts.com/modules/export-data.js"></script>
    <script src="https://code.highcharts.com/modules/accessibility.js"></script>
    <title>ESP8266-WS</title>
    <style>
        html {
            font-family: Helvetica;
            text-align: center;
        }
        .footer {
            position: fixed;
            left: 0;
            bottom: 0;
            width: 100%;
            background-color: rgb(19, 31, 71);
            color: white;
            text-align: center;
        }
        .header {
            position: fixed;
            left: 0;
            top: 0;
            width: 100%;
            background-color: rgb(80, 223, 187);
            color: white;
            text-align: center;
            font-size: 15px;
        }
        .selectstyle {
            background-color: rgb(49, 160, 136);
            border: none;
            color: white;
            padding: 10px 20px;
            border-radius: 5px;
        }
        .card {
            background: rgb(0, 56, 121);
            box-sizing: border-box;
            color: rgb(255, 255, 255);
            border-radius: 10px;
            height: 360px;
        }
        .contenedor {
            position: fixed;
            top: 120px;
            bottom: 70px;
            width: 90%;
            margin-left: 2.5%;
            margin-right: 7.5%;
            overflow-y: scroll;
        }
        #contt {
            width: 100%;
        }
        #idd {
            width: 50px;
            height: 30px;
            background-color: rgb(128, 128, 128);
            border-style: solid;
            border-color: rgb(19, 31, 71);
            border-radius: 5px;
            display: inline-block;
        }
        #idH {
            position: relative;
            top: -10px;
            width: 50px;
            height: 20px;
            display: inline-block;
        }

        #idUp {
            background-color: rgb(23, 92, 172);
            border: none;
            color: white;
            padding: 10px 20px;
            text-decoration: none;
            font-size: 15px;
            margin: 4px;
        }

        @media screen and (min-width: 500px) {
            .contenedor {
                width: 80%;
                margin-left: 10%;
                margin-right: 10%;
            }
        }

        @media screen and (min-width: 650px) {
            .contenedor {
                width: 60%;
                margin-left: 20%;
                margin-right: 20%;
            }
        }

        @media screen and (min-width: 800px) {
            .contenedor {
                width: 50%;
                margin-left: 25%;
                margin-right: 25%;
            }
        }
    </style>
</head>
<body>
    <div class="header">
        <h1>ESP8266 - WS</h1>
    </div>
    <div class="contenedor">
        <div id="cardid" class="card">
            <div class="contenedor2">
                <div style="padding-top: 5px;">
                    <h3>Chart LDR: <samp id="sid0">0</samp></h3>
                </div>
                <figure class="highcharts-figure">
                    <div id="container"></div>
                </figure>
            </div>
        </div>
        <div class="footer">
            <p><span>Desarrollado por CBM 2020</span></p>
        </div>
        <script>
            setInterval(function () {
                getDatac();
            }, 540); //0.54 minimo posible

            var x = 0;
            function getDatac() {
                var xhttp2 = new XMLHttpRequest();
                xhttp2.onreadystatechange = function () {
                    if (this.readyState == 4 && this.status == 200) {
                        var myJSON = this.responseText;
                        var myObj = JSON.parse(myJSON);
                        var valH = myObj.h;
                        document.getElementById("sid0").innerHTML = valH;
                        var y = parseFloat(valH);
                        if (chartT.series[0].data.length > 40) {
                            chartT.series[0].addPoint([x, y], true, true, true);
                            x++;
                        } else {
                            chartT.series[0].addPoint([x, y], true, false, true);
                            x++;
                        }
                    }
                };
                xhttp2.open("GET", "readSensors", true);
                xhttp2.send();
            }

            var chartT = Highcharts.chart('container', {
                legend: {
                    enabled: false // sin lellenda
                },
                title: {
                    text: '' // titulo de la grafica
                },
                yAxis: {
                    title: {
                        text: '' //titulo del eje Y
                    }
                },
                xAxis: {
                    visible: false // eje x invisible
                },
                plotOptions: {
                    series: {
                        color: 'rgb(10,200,150)' //color de las columnas
                    },
                    line: {
                        animation: false,
                        dataLabels: { enabled: false },
                        marker: { enabled: false } // sin puntos en los picos
                    }
                },
                chart: {
                    height: 250, //altura d la grafica
                    renderTo: 'container',
                    type: 'line', // tipo Columna
                },
                credits: {
                    enabled: false  // sin creditos al final
                },
                series: [{
                    name: 'Installation',
                    data: [],
                    lineWidth: 2 // grosor de la linea
                }]
            });
        </script>
</body>
</html>
)=====";
