// Head partials
// Style
const String styles = "<style>"
  ".status{"
  "width: 35vmin;"
  "height: 35vmin;"
  "border-radius: 50%;"
  "border: 10px solid #ce0000;"
  "padding: 5px;"
  "background: white;"
  "background-clip: content-box;"
  "transition: background-color 0.5s;"
  "}"
  "</style>";

// Body partials
const String header = "<div class='header'>"
  + String(HOSTNAME) +
  "</div>";

const String nav = "<div class='nav'>"
  "<a href='/'>Status</a>"
  "<a href='/update_form'>Firmware update</a>"
  "</div>";
  
const String footer= "<div class='footer'>"
  "<img src='https://maximemoreillon.com/images/logo/logo.png'>"
  "  <div>"
  "    <div>SONOFF firmware v1.0</div>"
  "    <div>Maxime Moreillon</div>"
  "  </div>"
  "</div>";

// Update form
String update_form = "<h2>Firmware update</h2>"
  "<form method='POST' action='/update' enctype='multipart/form-data'>"
  "<input type='file' name='update'>"
  "<input type='submit' value='Update'>"
  "</form>";

// Combinations
String head ="<head>"
  "<title>" + String(HOSTNAME) +"</title>"
  + styles +
  "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
  "<link rel='stylesheet' type='text/css' href='http://maximemoreillon.com/web_components/master_css/master.css'>"
  "</head>";

String pre_main = "<html>"
  + head + 
  "<body>"
  "<div class='wrapper'>"
  + header + nav +
  "<div class='main'>";
  
String post_main = "</div>"
  + footer +
  "</div>"
  "</body>"
  "</html>";

// Root
String root_main = ""
  "<div class='status' id='status_container' onclick='toggle()'></div>"
  "<script>"
  "websock = new WebSocket('ws://' + window.location.hostname + ':81/');"
  "websock.onopen = function(evt) { console.log('websock open'); };"
  "websock.onclose = function(evt) { console.log('websock close'); };"
  "websock.onerror = function(evt) { console.log(evt); };"
  "websock.onmessage = function(evt) {"
  "  var status_container = document.getElementById('status_container');"
  "  if(evt.data == 'ON'){"
  "    status_container.style.backgroundColor = '#ce0000';"
  "  }"
  " else if(evt.data == 'OFF'){"
  "    status_container.style.backgroundColor = '#ffffff';"
  "  }"
  "};"
  "function toggle(){"
  "  var xhttp = new XMLHttpRequest();"
  "  xhttp.open('GET','/toggle',true);"
  "  xhttp.send();"
  "}"
  "</script>";

// Not found
String not_found = "<h2>Not found</h2>";
