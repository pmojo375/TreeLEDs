// HtmlContent.h
#ifndef HtmlContent_h
#define HtmlContent_h

#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
  <title>LED Christmas Tree Control</title>
  <style>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
            padding: 20px;
            color: #333;
        }

        h1 {
            color: #4CAF50;
        }

        label {
            display: block;
            margin: 15px 0 5px;
        }

        input[type=color], input[type=range] {
            width: 100%;
            padding: 8px;
            border: 1px solid #ddd;
            border-radius: 4px;
            box-sizing: border-box;
        }

        button {
            background-color: #4CAF50;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 16px;
        }

        button:hover {
            background-color: #45a049;
        }

        .control-group {
            margin-bottom: 20px;
        }
    </style>
  </style>
</head>

<body>
  <h1>LED Christmas Tree Control</h1>

  <label for="functionSelect">Select Function:</label>
  <select id="functionSelect">
      <option value="0">Normal</option>
      <option value="1">Color Waves</option>
      <option value="2">Twinkling Stars</option>
      <option value="3">Candy Cane</option>
      <option value="4">Rising Sparkles</option>
      <option value="5">Meteor Rain</option>
  </select>
  <button onclick="sendFunction()">Apply Function</button>

  <br><br>

  <label for="hueChange">Enable gHue Increment:</label>
  <input type="checkbox" id="hueChange" checked>
  <button onclick="sendHueChange()">Apply</button>

  <br><br>

  <label for="paletteSelect">Select Color Palette:</label>
  <select id="paletteSelect">
      <option value="0">RainbowColors</option>
      <option value="1">RainbowStripeColors</option>
      <option value="2">CloudColors</option>
      <option value="3">LavaColors</option>
      <option value="4">OceanColors</option>
      <option value="5">ForestColors</option>
      <option value="6">PartyColors</option>
      <option value="7">HeatColors</option>
  </select>
  <button onclick="sendPalette()">Change Palette</button>

  <br><br>

  <label for="baseColor">Base Color:</label>
  <input type="color" id="baseColor" name="baseColor" onchange="changeBaseColor(this.value)">

  <br><br>

  <label for="secondaryColor1">Secondary Color 1:</label>
  <input type="color" id="secondaryColor1" name="secondaryColor1" onchange="changeSecondaryColor1(this.value)">

  <br><br>

  <label for="secondaryColor2">Secondary Color 2:</label>
  <input type="color" id="secondaryColor2" name="secondaryColor2" onchange="changeSecondaryColor2(this.value)">

  <br><br>

  <label for="secondaryColor2">Secondary Color 3:</label>
  <input type="color" id="secondaryColor3" name="secondaryColor3" onchange="changeSecondaryColor3(this.value)">

  <br><br>


  <label for="flickerRate">Per Second Update Rate:</label>
  <input type="range" id="flickerRate" name="flickerRate" min="1" max="100" onchange="changeFlickerRate(this.value)">

  <br><br>

  <label for="brightness">Brightness:</label>
  <input type="range" id="brightness" name="brightness" min="0" max="255" onchange="changeBrightness(this.value)">

  <br><br>

  <label for="fade_amount">Fade Amount:</label>
  <input type="range" id="fade_amount" name="fade_amount" min="0" max="255" onchange="changeFadeAmount(this.value)">
  
  <br><br>

  <label for="variability">Speed Variability:</label>
  <input type="range" id="variability" name="variability" min="0" max="200" onchange="changeVariability(this.value)">

  <script>
    // JavaScript functions to handle changes and send requests to ESP32

    function sendFunction() {

      var functionValue = document.getElementById("functionSelect").value;

      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            console.log('LED function changed to: ' + functionValue);
        }
      };
      var url = "http://192.168.4.1/setLEDFunction";
      xhttp.open("POST", url, true);
      xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      xhttp.send("function=" + functionValue);
    }

    function sendHueChange() {
      var toggle = document.getElementById("hueChange").checked;
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            console.log('gHue incrementation toggled: ' + toggle);
          }
      };
      var url = "http://192.168.4.1/toggleHueIncrement";
      xhttp.open("POST", url, true);
      xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      xhttp.send("hueIncrement=" + toggle);
    }

    function sendPalette() {
      var paletteValue = document.getElementById("paletteSelect").value;
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            console.log('Color palette changed to: ' + paletteValue);
          }
      };
      var url = "http://192.168.4.1/setColorPalette";
      xhttp.open("POST", url, true);
      xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      xhttp.send("palette=" + paletteValue);
    }


    function changeBaseColor(color) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          console.log('Base color changed to: ' + color);
        }
      };

      // Specify your ESP32 endpoint here
      var url = "http://192.168.4.1/setBaseColor";

      xhttp.open("POST", url, true);
      xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      xhttp.send("color=" + color);
    }


    function changeSecondaryColor1(color) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          console.log('Secondary color 1 changed to: ' + color);
        }
      };

      // Specify your ESP32 endpoint here
      var url = "http://192.168.4.1/setSecondaryColor1";

      xhttp.open("POST", url, true);
      xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      xhttp.send("color=" + color);
    }

    function changeSecondaryColor2(color) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          console.log('Secondary color 2 changed to: ' + color);
        }
      };

      // Specify your ESP32 endpoint here
      var url = "http://192.168.4.1/setSecondaryColor2";

      xhttp.open("POST", url, true);
      xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      xhttp.send("color=" + color);
    }

    function changeSecondaryColor3(color) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          console.log('Secondary color 3 changed to: ' + color);
        }
      };

      // Specify your ESP32 endpoint here
      var url = "http://192.168.4.1/setSecondaryColor3";

      xhttp.open("POST", url, true);
      xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      xhttp.send("color=" + color);
    }

    function changeFlickerRate(rate) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          console.log('Rate changed to: ' + rate);
        }
      };

      // Specify your ESP32 endpoint here
      var url = "http://192.168.4.1/setRate";

      xhttp.open("POST", url, true);
      xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      xhttp.send("rate=" + rate);
    }

    function changeBrightness(brightness) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          console.log('Rate changed to: ' + rate);
        }
      };

      // Specify your ESP32 endpoint here
      var url = "http://192.168.4.1/setBrightness";

      xhttp.open("POST", url, true);
      xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      xhttp.send("brightness=" + brightness);
    }

    function changeFadeAmount(fade_amount) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          console.log('Fade amount changed to: ' + fade_amount);
        }
      };

      // Specify your ESP32 endpoint here
      var url = "http://192.168.4.1/setFadeAmount";

      xhttp.open("POST", url, true);
      xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      xhttp.send("fade_amount=" + fade_amount);
    }

    function changeVariability(variability) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          console.log('Speed variability changed to: ' + variability);
        }
      };

      // Specify your ESP32 endpoint here
      var url = "http://192.168.4.1/setVariability";

      xhttp.open("POST", url, true);
      xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      xhttp.send("variability=" + variability);
    }
  </script>
</body>

</html>

)rawliteral";

#endif
