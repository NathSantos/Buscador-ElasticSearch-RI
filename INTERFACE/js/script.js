const chk = document.getElementById('chk');
var titulo = document.querySelector("h1");
var srchBox = document.querySelector(".search-box");
var srchTxt = document.querySelector(".search-text");
var srchBtn = document.querySelector(".lupa-btn");
var srchBtnHover = document.querySelector(".search-box:hover.dark");
var labelBtn = document.querySelector(".label");            // AJEITAR
var labelBallBtn = document.querySelector(".label .ball");   // AJEITAR

chk.addEventListener('change', function() {
    document.body.classList.toggle('dark');
    titulo.classList.toggle('dark');
    srchBox.classList.toggle('dark');
    srchTxt.classList.toggle('dark');
    srchBtn.classList.toggle('dark');
    srchBtnHover.classList.toggle('dark');
    labelBtn.classList.toggle('dark');
    labelBallBtn.classList.toggle('dark');
});

//var input = document.getElementById('searchbar').value
