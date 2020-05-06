const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ESP8266-WS</title>
  <style>
    html {
      font-family: Helvetica;
      text-align: center;
    }
    button {
      height: 30px;
      width: 100px;
      margin: 5px;
      font-size: 20px;
      border-radius: 5px;
      color: rgb(255, 255, 255);
      background-color: rgb(53, 155, 129);
      border: none;
    }
    button:hover {
      background-color: rgb(114, 116, 115);
      color: white;
    }
    .pl {
      background-color: rgb(143, 18, 18);
    }
    .st {
      background-color: rgb(11, 17, 43);
    }
    .res{
      background-color: rgb(223, 82, 26);
    }
    .rec{
      background-color: rgb(53, 165, 49);
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
    .card {
      background: rgb(0, 56, 121);
      box-sizing: border-box;
      color: rgb(255, 255, 255);
      border-radius: 10px;
      height: 450px;
    }
    .contenedor {
      position: fixed;
      top: 74px;
      bottom: 70px;
      width: 90%;
      margin-left: 2.5%;
      margin-right: 7.5%;
      overflow-y: scroll;
    }
    .dell {
      font-size:15px;
      margin-left: 7px;
      padding-left: 5px;
      height: 25px;
      border: 1px solid #ccc;
      border-radius: 4px;
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
        width: 30%;
        margin-left: 35%;
        margin-right: 35%;
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
      <h2 style="padding-top: 15px;">Servos</h2>
      S1: <span id="idSpan1">90</span>
      <input type="range" name="sliderR" min="1" max="179" class="slider" onchange="moverS()" id="IDSlider1"
        value="90"><br>
      S2: <span id="idSpan2">90</span>
      <input type="range" name="sliderR" min="1" max="179" class="slider" onchange="moverS()" id="IDSlider2"
        value="90"><br>
      S3: <span id="idSpan3">90</span>
      <input type="range" name="sliderR" min="1" max="179" class="slider" onchange="moverS()" id="IDSlider3"
        value="90"><br>
      S4: <span id="idSpan4">90</span>
      <input type="range" name="sliderR" min="1" max="179" class="slider" onchange="moverS()" id="IDSlider4"
        value="90"><br>
      S5: <span id="idSpan5">90</span>
      <input type="range" name="sliderR" min="1" max="179" class="slider" onchange="moverS()" id="IDSlider5"
        value="90"><br>
      <br>
      <hr>
      <br>
      <button class="res" onclick="resetrec()">Reset</button>
      <button class="rec" onclick="record()">Rec Pos</button>
      <span id="inpval">0</span>
      <br>
      <br>
      <hr>
      <br>
      Delay ms: <input id="del" class="dell" style="width: 50px;" type="number" value=700></input>
      <br>
      <br>
      <button onclick="play(1)" class="pl">play</button>
      <span id="splay"></span>
      <button onclick="play(0)" class="st">All 90</button>
      <br>
      <br>
      <br>
    </div>
    <div class="footer">
      <p><span>Desarrollado por CBM 2020</span></p>
    </div>
    <script>
      var po1=90;
      var po2=90;
      var po3=90;
      var po4=90;
      var po5=90;
      var p=0;
      var pos = {"pos1":90,"pos2":90,"pos3":90,"pos4":90,"pos5":90}; //pos: objeto que contiene las posiciones
      var arrObj = {  //arrObj: objeto que contiene a los objetos pos
          largo : 0,
          addElem: function addElem(elem) {
              [].push.call(this, elem);
              this.largo++;
          },
          removElem: function removElem() {//remueve el ultimo elemento
                [].pop.call(this);
                this.largo--;
            }
      };
      function record() {
        var poss = {"pos1":90,"pos2":90,"pos3":90,"pos4":90,"pos5":90};
        poss.pos1 = document.getElementById("IDSlider1").value; //obtengo las pos, de los sliders y las agrego al objeto pos
        poss.pos2 = document.getElementById("IDSlider2").value;
        poss.pos3 = document.getElementById("IDSlider3").value;
        poss.pos4 = document.getElementById("IDSlider4").value;
        poss.pos5 = document.getElementById("IDSlider5").value;
        arrObj.addElem(poss); //agrego el objeto pos al objeto arrObj
        for(var i = 0; i<arrObj.largo; i++){//---------debugeo
          console.log(i+": "+arrObj[i].pos1);
          console.log(i+": "+arrObj[i].pos2);
          console.log(i+": "+arrObj[i].pos3);
          console.log(i+": "+arrObj[i].pos4);
          console.log(i+": "+arrObj[i].pos5);
        }
        p++;
        document.getElementById("inpval").innerHTML=p;
        document.getElementById("splay").innerHTML="";
      }
      function sleep(ms) {
            return new Promise(resolve => setTimeout(resolve, ms)); //funcion del sleep
      }
      async function play(x) {
        var del = document.getElementById("del").value;
        if(del<200){
          alert("delay >= 200 ms");
          return;
        }
        if(del>60000){
          alert("delay < 1 min");
          return;
        }
        var xhttp = new XMLHttpRequest();
        if (x == 1) { // button: play
          for(var i=0;i<arrObj.largo;i++){
            po1 = arrObj[i].pos1;
            po2 = arrObj[i].pos2;
            po3 = arrObj[i].pos3;
            po4 = arrObj[i].pos4;
            po5 = arrObj[i].pos5;
            console.log(i+": po1: "+po1+", po2: "+po2+", po3: "+po3+", po4: "+po4+", po5: "+po5);//-------debugeo
            xhttp.open("GET", "set?pos1=" + po1 + "&pos2=" + po2 + "&pos3=" + po3 + "&pos4=" + po4 + "&pos5=" + po5, true); 
            xhttp.send();//envia los datos al servidor
            await sleep(del);//espera x milisegundos
            var t=i+1;
            document.getElementById("splay").innerHTML=t;
          }
          document.getElementById("splay").innerHTML="Fin";
        }
        else if (x == 0) { // button: all 90
          document.getElementById("IDSlider1").value=90; //setea el valor de los slider en 90
          document.getElementById("IDSlider2").value=90;
          document.getElementById("IDSlider3").value=90;
          document.getElementById("IDSlider4").value=90;
          document.getElementById("IDSlider5").value=90;

          document.getElementById("idSpan1").innerHTML = 90;//setea el texto de los spam en 90
          document.getElementById("idSpan2").innerHTML = 90;
          document.getElementById("idSpan3").innerHTML = 90;
          document.getElementById("idSpan4").innerHTML = 90;
          document.getElementById("idSpan5").innerHTML = 90;
          xhttp.open("GET", "set?pos1=90&pos2=90&pos3=90&pos4=90&pos5=90", true); //arma los parametros del URL
          xhttp.send(); //envia los datos al servidor
          document.getElementById("splay").innerHTML="";
        }
      }
      function resetrec(){
        document.getElementById("inpval").innerHTML=0; //pone el contador en 0
        p=0;
        var larg = arrObj.largo;
        for(var i=0;i<larg;i++){
          arrObj.removElem(); //elimina todos los pos del objeto arrObj
          console.log("largo: "+arrObj.largo);
        }
        document.getElementById("splay").innerHTML="";
      }
      function moverS() {
        var xhttp = new XMLHttpRequest();
        var pos1 = document.getElementById("IDSlider1").value;  //obtiene el valor del slider
        document.getElementById("idSpan1").innerHTML = pos1; //cambia el texto del spam con el valor del slider
        var pos2 = document.getElementById("IDSlider2").value;
        document.getElementById("idSpan2").innerHTML = pos2;
        var pos3 = document.getElementById("IDSlider3").value;
        document.getElementById("idSpan3").innerHTML = pos3;
        var pos4 = document.getElementById("IDSlider4").value;
        document.getElementById("idSpan4").innerHTML = pos4;
        var pos5 = document.getElementById("IDSlider5").value;
        document.getElementById("idSpan5").innerHTML = pos5;
        xhttp.open("GET", "set?pos1=" + pos1 + "&pos2=" + pos2 + "&pos3=" + pos3 + "&pos4=" + pos4 + "&pos5=" + pos5, true); //arma los parametros del URL
        xhttp.send();//envia los datos al servidor
        document.getElementById("splay").innerHTML="";
      }
    </script>
</body>
</html>
)=====";