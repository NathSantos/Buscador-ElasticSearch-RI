const chk = document.getElementById('chk');
var titulo = document.querySelector("h1");
var srchBox = document.querySelector(".search-box");
var srchTxt = document.querySelector(".search-text");
var srchBtn = document.querySelector(".search-btn");
var srchBtnHover = document.querySelector(".search-box:hover.dark");
var labelBtn = document.querySelector(".label");
var labelBallBtn = document.querySelector(".label.ball");

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