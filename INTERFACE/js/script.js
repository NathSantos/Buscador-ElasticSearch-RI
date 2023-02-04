const chk = document.getElementById('chk');
var titulo = document.querySelector("h1");
var srchBox = document.querySelector(".search-box");
var srchTxt = document.querySelector(".search-text");
var srchBtn = document.querySelector(".lupa-btn");
var labelBtn = document.querySelector(".label");            // AJEITAR
var labelBallBtn = document.querySelector(".label .ball");   // AJEITAR

var input = document.getElementById("box");
// Execute a function when the user presses a key on the keyboard
input.addEventListener("keypress", function(event) {
  // If the user presses the "Enter" key on the keyboard
  if (event.key === "Enter") {
    // Cancel the default action, if needed
    event.preventDefault();
    // Trigger the button element with a click
    var str_consulta = document.getElementById("searchbar").value;
    console.log("Consulta Digitada: " + str_consulta);
  }
}); 

chk.addEventListener('change', function() {
    document.body.classList.toggle('dark');
    titulo.classList.toggle('dark');
    srchBox.classList.toggle('dark');
    srchTxt.classList.toggle('dark');
    srchBtn.classList.toggle('dark');
    labelBtn.classList.toggle('dark');
    labelBallBtn.classList.toggle('dark');
});

