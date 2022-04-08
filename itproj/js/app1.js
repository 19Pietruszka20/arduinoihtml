$(document).ready(function(){
  $.ajax({
    url: "http://localhost/itproj/data1.php",
    method: "GET",
    success: function(data) {
      console.log(data);
      var czas = [];
      var przebytadroga = [];
		
      for(var i in data) {
        czas.push("t " + data[i].czas);
        przebytadroga.push(data[i].przebytadroga);
      }

      var chartdata = {
        labels: czas,
        datasets : [
          {
            label: 'wykres przebytej drogi',
            backgroundColor: 'rgba(0, 0, 0, 0.75)',
            borderColor: 'rgba(200, 200, 200, 0.75)',
            hoverBackgroundColor: 'rgba(0, 0, 0, 1)',
            hoverBorderColor: 'rgba(200, 200, 200, 1)',
            data: przebytadroga
          }
        ]
      };

      var ctx = $("#mycanvas");

      var myLineChart = new Chart(ctx, {
        type: 'line',
        data: chartdata,
      });
    },
    error: function(data) {
      console.log(data);
    }
  });
});