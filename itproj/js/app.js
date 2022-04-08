$(document).ready(function(){
  $.ajax({
    url: "http://localhost/chartjs/data.php",
    method: "GET",
    success: function(data) {
      console.log(data);
      var przebytadroga = [];
      var v2 = [];
		
      for(var i in data) {
        przebytadroga.push("t " + data[i].przebytadroga);
        v2.push(data[i].v2);
      }

      var chartdata = {
        labels: przebytadroga,
        datasets : [
          {
            label: 'wykres predkosci',
            backgroundColor: 'rgba(0, 0, 0, 0.75)',
            borderColor: 'rgba(200, 200, 200, 0.75)',
            hoverBackgroundColor: 'rgba(0, 0, 0, 1)',
            hoverBorderColor: 'rgba(200, 200, 200, 1)',
            data: v2
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