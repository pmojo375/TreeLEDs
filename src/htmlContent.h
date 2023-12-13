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
          height: 50px;
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
</head>

<body>

  <h1>LED Christmas Tree Control</h1>

  <label for="mode">Select Function:</label>
  <select id="mode">
      <option value="0">Normal</option>
      <option value="1">Color Waves</option>
      <option value="2">Twinkling Stars</option>
      <option value="3">Candy Cane</option>
      <option value="4">Rising Sparkles</option>
      <option value="5">Twinkle Fox</option>
      <option value="6">Fire</option>
  </select>
  <button onclick="sendMode()">Apply Mode</button>

  <br><br>

  <label for="incgHueState">Enable gHue Increment:</label>
  <input type="checkbox" id="incgHueState" checked>
  <button onclick="sendIncgHueState()">Apply</button>

  <br><br>

  <label for="palette">Select Color Palette:</label>
  <select id="palette">
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

  <label for="Color1">Color 1:</label>
  <input type="color" id="Color1" name="Color1" onchange="changeColor1(this.value)">

  <br><br>

  <label for="Color2">Color 2:</label>
  <input type="color" id="Color2" name="Color2" onchange="changeColor2(this.value)">

  <br><br>

  <label for="Color3">Color 3:</label>
  <input type="color" id="Color3" name="Color3" onchange="changeColor3(this.value)">

  <br><br>

  <label for="Color2">Color 4:</label>
  <input type="color" id="Color4" name="Color4" onchange="changeColor4(this.value)">

  <br><br>

  <label for="fps">FPS:</label>
  <input type="range" id="fps" name="fps" min="1" max="66" onchange="changeFPS(this.value)">

  <br><br>

  <label for="brightness">Brightness:</label>
  <input type="range" id="brightness" name="brightness" min="0" max="255" onchange="changeBrightness(this.value)">

  <br><br>

  <label for="fadeAmount">Fade Amount:</label>
  <input type="range" id="fadeAmount" name="fadeAmount" min="0" max="255" onchange="changeFadeAmount(this.value)">
  
  <br><br>

  <label for="fps_variability">FPS Variability:</label>
  <input type="range" id="fps_variability" name="fps_variability" min="0" max="66" onchange="changeFPS_Variability(this.value)">

  <script>
    var socket;
    
    function initWebSocket() {
        socket = new WebSocket('ws://' + window.location.hostname + '/ws');
        socket.onopen = function(event) {
            console.log('WebSocket connected');
        };
        socket.onclose = function(event) {
            console.log('WebSocket disconnected');
            setTimeout(initWebSocket, 2000);
        };
        socket.onmessage = function(event) {
          console.log("Received message:", event.data);
          var message = JSON.parse(event.data);
          console.log("Parsed message:", message);
          switch(message.type) {
              case 'Mode':
                  mode = message.value;
                  document.getElementById("mode").value = mode;
                  break;
              case 'Palette':
                  palette = message.value;
                  document.getElementById("palette").value = palette;
                  break;
              case 'Increment gHue':
                  gHueState = message.value;
                  if (gHueState == 1) {
                    document.getElementById("incgHueState").checked = true;
                  } else {
                    document.getElementById("incgHueState").checked = false;
                  }
                  break;
              case 'Color 1':
                  color1 = message.value;
                  document.getElementById("Color1").value = color1;
                  break;
              case 'Color 2':
                  color2 = message.value;
                  document.getElementById("Color2").value = color2;
                  break; 
              case 'Color 3':
                  color3 = message.value;
                  document.getElementById("Color3").value = color3;
                  break; 
              case 'Color 4':
                  color4 = message.value;
                  document.getElementById("Color4").value = color4;
                  break; 
              case 'FPS':
                  fps = message.value;
                  document.getElementById("fps").value = fps;
                  break;
              case 'Fade Amount':
                  fadeAmount = message.value;
                  document.getElementById("fadeAmount").value = fadeAmount;
                  break;
              case 'Brightness':
                  brightness = message.value;
                  document.getElementById("brightness").value = brightness;
                  break;
              case 'FPS Variability':
                  fps_variability = message.value;
                  document.getElementById("fps_variability").value = fps_variability;
                  break;
          }
        };
    }

    function sendMessage(type, value) {
        var message = JSON.stringify({type: type, value: value});
        socket.send(message);
    }

    window.onload = initWebSocket;

    function sendMode() {
      var mode = document.getElementById("mode").value;
      sendMessage("Mode", mode);
    }
    
    function sendIncgHueState() {
      var incgHueState = document.getElementById("incgHueState").checked;
      sendMessage("Increment gHue", incgHueState);
    }
    
    function sendPalette() {
      var palette = document.getElementById("palette").value;
      sendMessage("Palette", palette);
    }

    function changeColor1(value) {
        sendMessage("Color 1", value);
    }

    function changeColor2(value) {
        sendMessage("Color 2", value);
    }

    function changeColor3(value) {
        sendMessage("Color 3", value);
    }

    function changeColor4(value) {
        sendMessage("Color 4", value);
    }

    function changeFPS(value) {
        sendMessage("FPS", value);
    }

    function changeBrightness(value) {
        sendMessage("Brightness", value);
    }

    function changeFadeAmount(value) {
        sendMessage("Fade Amount", value);
    }

    function changeFPS_Variability(value) {
        sendMessage("FPS Variability", value);
    }
  </script>
</body>

</html>

)rawliteral";

#endif
