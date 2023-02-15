var showHeadersButton = document.getElementById('btn-search');
var headers = document.getElementsByTagName('th');

showHeadersButton.addEventListener('click', function() {
  for (var i = 0; i < headers.length; i++) {
    headers[i].style.opacity = 1;
    headers[i].style.fontFamily = 'Poppins';
    headers[i].style.color = '#0a1b2d';
    headers[i].style.fontSize = '16px';
  }
});
