
var margin = {top: 10, right: 30, bottom: 30, left: 60};
var width = 800 - margin.left - margin.right;
var height = 450 - margin.top - margin.bottom;




function getDate(date){
  return date.split("T")[0];
}

function getHour(date){
  return date.split("T")[1].split(":")[0];
}


function make_lines(dataF){
      if (dataF.length != 0){
  		var tempLine = d3.select("#temperatureLine").append("svg")
  		.attr("preserveAspectRatio", "xMinYMin meet")
  		.attr("viewBox", "0 0 800 480")
  		.append("g")
  		.attr("transform",
  				"translate(" + margin.left+ ", 0 )");
  		//create xAxis
  		tempLine.append("g")
  			.attr("class", "xAxis");
  		//create yAxis
  		tempLine.append("g")
  			.attr("class", "yAxis");
  		tempLine.append("text")
  			.attr("text-anchor", "end")
  			.attr("transform", "rotate(-90)")
  			.attr("y", -margin.left+20)
  			.attr("x", -margin.top -50)
  			.text("Temperature");
  		tempLine.append("text")
  			.attr("transform",
  				"translate(" + (width) + " ," +
  							(height +32) + ")")
  			.style("text-anchor", "middle")
  			.text("Hours");

        var x = d3.scaleBand().range([0, width]).padding(.3)
		      .domain(dataF.map(function(d) {return d.deviceData.date; }));;
        var x_tick = d3.scaleBand().range([0, width]).padding(.3)
    		      .domain(dataF.map(function(d) {return getHour(d.deviceData.date); }));
	      var y = d3.scaleLinear().range([height, 0])
		      .domain([d3.min(dataF, d=> +d.deviceData.dhtTemperature) - 3, d3.max(dataF, d => +d.deviceData.dhtTemperature) + 3 ]);
        tempLine.select(".xAxis")
			     .attr("transform", "translate(0," + height + ")")
			     .call(d3.axisBottom(x_tick));
		    tempLine.select(".yAxis")
			     .call(d3.axisLeft(y));

        tempLine.append("path")
         .datum(dataF)
         .attr("fill", "none")
         .attr("stroke", "steelblue")
         .attr("stroke-width", 1.5)
         .attr("d", d3.line()
           .x(function(d) { return x(d.deviceData.date) })
           .y(function(d) { return y(d.deviceData.dhtTemperature) }));


  	     //Humidity graph

     		var humLine = d3.select("#humidityLine").append("svg")
     		.attr("preserveAspectRatio", "xMinYMin meet")
     		.attr("viewBox", "0 0 800 480")
     		.append("g")
     		.attr("transform",
     				"translate(" + margin.left+ ", 0 )");
     		//create xAxis
     		humLine.append("g")
     			.attr("class", "xAxis");
     		//create yAxis
     		humLine.append("g")
     			.attr("class", "yAxis");
     		humLine.append("text")
     			.attr("text-anchor", "end")
     			.attr("transform", "rotate(-90)")
     			.attr("y", -margin.left+20)
     			.attr("x", -margin.top -50)
     			.text("Humidity");
     		humLine.append("text")
     			.attr("transform",
     				"translate(" + (width) + " ," +
     							(height +32) + ")")
     			.style("text-anchor", "middle")
     			.text("Hours");

	      var y = d3.scaleLinear().range([height, 0])
		      .domain([d3.min(dataF, d=> +d.deviceData.dhtHumidity -3), d3.max(dataF, d => +d.deviceData.dhtHumidity) + 3 ]);

        humLine.select(".xAxis")
			     .attr("transform", "translate(0," + height + ")")
			     .call(d3.axisBottom(x_tick));
		    humLine.select(".yAxis")
			     .call(d3.axisLeft(y));

        humLine.append("path")
         .datum(dataF)
         .attr("fill", "none")
         .attr("stroke", "red")
         .attr("stroke-width", 1.5)
         .attr("d", d3.line()
           .x(function(d) { return x(d.deviceData.date) })
           .y(function(d) { return y(d.deviceData.dhtHumidity) }));
         } else {

         }
}


function getGraph(){
   d3.select('#temperatureLine').select('svg').remove();
   d3.select('#humidityLine').select('svg').remove();
   var date_choosen=document.getElementById("input-date").value;
//   url = 'http://ec2-18-222-178-37.us-east-2.compute.amazonaws.com/json/' + date_choosen + '.json';
   url = document.location + 'json/' + date_choosen + '.json';
   d3.json(url).then(function(data){
     make_lines(data);
     temperatureMax=d3.max(data, d => d.deviceData.dhtTemperature);
     temperatureMin=d3.min(data, d=> d.deviceData.dhtTemperature);
     humidityMax=d3.max(data, d=> d.deviceData.dhtHumidity);
     humidityMin=d3.min(data, d=> d.deviceData.dhtHumidity);
//     document.getElementById('info').innerHtml='Temperature MAX: ' + temperatureMax + '	MIN: ' + temperatureMin + '</br> Humidity MAX: ' + humidityMax + '	MIN: ' + humidityMin; 
   })
}


function changeDate(event){
   getGraph();
};


window.addEventListener("load", function(event){
   getGraph();
});
