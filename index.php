<?php
    /* Include the ../src/fusioncharts.php file that contains functions to embed the charts.*/
    include("fusioncharts.php");
?>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="refresh" content="600" >
         <meta charset="UTF-8">
         <meta http-equiv="X-UA-Compatible" content="IE=Edge">
         <meta name="description" content="">
         <meta name="keywords" content="">
         <meta name="author" content="">
         <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
         <link rel="stylesheet" type="text/css" href="style.css" media="screen"/>
         <link rel="stylesheet" href="css/bootstrap.min.css">
         <link rel="stylesheet" href="css/font-awesome.min.css">
         <link rel="stylesheet" href="css/owl.carousel.css">
         <link rel="stylesheet" href="css/owl.theme.default.min.css">
         <link rel="stylesheet" href="css/style.css">
        <script src="https://cdn.fusioncharts.com/fusioncharts/latest/fusioncharts.js"></script>
        <script src="https://cdn.fusioncharts.com/fusioncharts/latest/themes/fusioncharts.theme.fusion.js"></script>
	<title> Naměřená Data </title>
</head>

<style>
.limiter {
  width: 100%;
  margin: 0 auto;
}

.container-table100 {
  width: 100%;
  min-height: 100vh;
  background: #c850c0;
  background: -webkit-linear-gradient(45deg, #ffffff, #000000);
  background: -o-linear-gradient(45deg, #ffffff, #000000);
  background: -moz-linear-gradient(45deg, #ffffff, #000000);
  background: linear-gradient(#ffffff, #2D708A);

  display: -webkit-box;
  display: -webkit-flex;
  display: -moz-box;
  display: -ms-flexbox;
  display: flex;
  align-items: center;
  justify-content: center;
  flex-wrap: wrap;
  padding: 33px 30px;
}

.wrap-table100 {
  width: 1170px;
}

table {
  border-spacing: 1;
  border-collapse: collapse;
  background: white;
  border-radius: 10px;
  overflow: hidden;
  width: 100%;
  margin: 0 auto;
  position: relative;
}
table * {
  position: relative;
}
table td, table th {
  padding-left: 8px;
}
table thead tr {
  height: 60px;
  background: #36304a;
}
table tbody tr {
  height: 50px;
}
table tbody tr:last-child {
  border: 0;
}
table td, table th {
  text-align: left;
}
table td.l, table th.l {
  text-align: right;
}
table td.c, table th.c {
  text-align: center;
}
table td.r, table th.r {
  text-align: center;
}


.table100-head th{
  font-family: OpenSans-Regular;
  font-size: 18px;
  color: #fff;
  line-height: 1.2;
  font-weight: unset;
}

tbody tr:nth-child(even) {
  background-color: #f5f5f5;
}

tbody tr {
  font-family: OpenSans-Regular;
  font-size: 15px;
  color: #808080;
  line-height: 1.2;
  font-weight: unset;
}

tbody tr:hover {
  color: #555555;
  background-color: #f5f5f5;
  cursor: pointer;
}

.column1 {
  width: 260px;
  padding-left: 40px;
}

.column2 {
  width: 160px;
}

.column3 {
  width: 245px;
}

.column4 {
  width: 110px;
  text-align: right;
}

.column5 {
  width: 170px;
  text-align: right;
}

.column6 {
  width: 222px;
  text-align: right;
  padding-right: 62px;
}
@media screen and (max-width: 992px) {

}

</style>
<body id="top" data-spy="scroll" data-target=".navbar-collapse" data-offset="50">

     <!-- PRE LOADER -->
     <section class="preloader">
          <div class="spinner">
               <span class="spinner-rotate"></span>
          </div>
     </section>


     <!-- MENU -->
     <section class="navbar custom-navbar navbar-fixed-top" role="navigation">
          <div class="container">

               <div class="navbar-header">
                    <button class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
                         <span class="icon icon-bar"></span>
                         <span class="icon icon-bar"></span>
                         <span class="icon icon-bar"></span>
                    </button>

                    <!-- lOGO TEXT HERE -->
                          <a href="home.php" class="navbar-brand"><img src="images/TechCrowd_logo_crop.jpg" class="img-responsive" alt=""></a>
               </div>

               <!-- MENU LINKS -->
               <div class="collapse navbar-collapse">
                    <ul class="nav navbar-nav navbar-nav-first">
                         <li><a href="home.php">Domů</a></li>
                         <li><a href="our-products.php">Naše produkty</a></li>
                         <li class="active"><a href="">Naměřená Data</a></li>
                         <li><a href="contact-us.php">Kontaktujte Nás</a></li>
                    </ul>
               </div>
          </div>
     </section>
     <!-- WIDGETS -->
     <section>
         <div class="container">
              <div class="row">
                <div class="col-sm-3" id="chart-2">
                Water level widget will render here!
                </div>
                <div class="col-sm-3" id="widget-battery">
                Battery widget will render here!
                </div>
                <div class="col-sm-3" id="chart-1">
                Temperature widget will render here!
                </div>
                <div class="col-sm-3" id="widget-container">
                Humidity widget will render here!
                </div>
            </div>
         </div>
     </section>
<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "hladina";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT id, value1, value2, value3, value4, reading_time FROM sensordata ORDER BY id DESC"; /*select items to display from the sensordata table in the data base*/

echo '
<section>
	<div class="limiter">
		<div class="container-table100">

			<div class="wrap-table100">
				<div class="table100">
                     <table cellspacing="5" cellpadding="5">
                        <thead>
                              <tr>
                                <th>ID</th>
                                <th>Datum a čas</th>
                                <th>Výška hladiny [cm]</th>
                                <th>Baterie [&#37] </th>
                                <th>Teplota [&deg;C]</th>
                                <th>Vlhkost [&#37;]</th>
                              </tr>
                        </thead>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_reading_time = $row["reading_time"];
        $row_value1 = $row["value1"];
        $row_value2 = $row["value2"]; 
        $row_value3 = $row["value3"]; 
        $row_value4 = $row["value4"];
        // Uncomment to set timezone to - 1 hour (you can change 1 to any number)
       $row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time - 1 hours"));
       $widgetDialDataArray = array($row_value4);
       $widgetDialDataArrayBattery = array($row_value2);

       //added php from gauge
    // Widget appearance configuration
    $arrChartConfig = array(
    "chart" => array(
    "caption" => "Vlhkost Vzduchu",
    "lowerLimit" => "0",
    "upperLimit" => "100",
    "showValue" => "1",
    "numberSuffix" => "%",
    "theme" => "fusion",
    "showToolTip" => "1"
    ));

    // Widget color range data
    $colorDataObj = array("color" => array(
        ["minValue" => "0", "maxValue" => "10", "code" => "#F2726F"],
        ["minValue" => "10", "maxValue" => "30", "code" => "#FFC533"],
        ["minValue" => "30", "maxValue" => "50", "code" => "#62B58F"],
        ["minValue" => "50", "maxValue" => "80", "code" => "#FFC533"],
        ["minValue" => "80", "maxValue" => "100", "code" => "#F2726F"],
    ));

    // Dial array
    $dial = array();

    // Widget dial data in array format, multiple values can be separated by comma e.g. ["81", "23", "45",...]
    for($i = 0; $i < count($widgetDialDataArray); $i++) {
        array_push($dial,array("value" => $widgetDialDataArray[$i]));
    }

    $arrChartConfig["colorRange"] = $colorDataObj;
    $arrChartConfig["dials"] = array( "dial" => $dial);

    // JSON Encode the data to retrieve the string containing the JSON representation of the data in the array.
    $jsonEncodedData = json_encode($arrChartConfig);

    // Widget object
    $Widget = new FusionCharts("angulargauge", "humidityWidget" , "300", "300", "widget-container", "json", $jsonEncodedData);

//____________________________________________________________________________________________________________________
// Widget appearance configuration BATTERY
    $arrChartConfigBattery = array(
    "chart" => array(
    "caption" => "Kapacita Baterie",
    "lowerLimit" => "0",
    "upperLimit" => "100",
    "showValue" => "1",
    "numberSuffix" => "%",
    "theme" => "fusion",
    "showToolTip" => "1",
    )
    );

    // Widget color range data
    $colorDataObjBattery = array("color" => array(
        ["minValue" => "0", "maxValue" => "25", "code" => "#F2726F"],
        ["minValue" => "25", "maxValue" => "50", "code" => "#FFC533"],
        ["minValue" => "50", "maxValue" => "100", "code" => "#62B58F"]
    ));

    // Dial array
    $dialBattery = array();

    // Widget dial data in array format, multiple values can be separated by comma e.g. ["81", "23", "45",...]
    for($i = 0; $i < count($widgetDialDataArrayBattery); $i++) {
        array_push($dialBattery,array("value" => $widgetDialDataArrayBattery[$i]));
    }

    $arrChartConfigBattery["colorRange"] = $colorDataObjBattery;
    $arrChartConfigBattery["dials"] = array( "dial" => $dialBattery);

    // JSON Encode the data to retrieve the string containing the JSON representation of the data in the array.
    $jsonEncodedDataBattery = json_encode($arrChartConfigBattery);

    // Widget object
    $WidgetBattery = new FusionCharts("angulargauge", "batteryWidget" , "300", "300", "widget-battery", "json", $jsonEncodedDataBattery);



    //______________thermo-meter added here
    $columnChartThermometer = new FusionCharts("thermometer", "thermometerWidget", "300","300", "chart-1", "json", '{
      "chart": {
        "caption": "Teplota",
        "subcaption": "u studny",
        "lowerlimit": "-20",
        "upperlimit": "60",
        "numbersuffix": "°C",
        "thmfillcolor": "#008ee4",
        "showgaugeborder": "1",
        "gaugebordercolor": "#008ee4",
        "gaugeborderthickness": "2",
        "plottooltext": "Venkovní teplota: <b>' . $row_value3 . ' °C</b>",
        "theme": "fusion",
        "showvalue": "1"
      },
      "value": ' . $row_value3 . '
    }');
    $row_value1_mod = $row_value1/100;
    //______________ cylinderWidget
    $columnChartCylinder = new FusionCharts("cylinder", "cylinderWidget", "300", "300", "chart-2", "json", '{
      "chart": {
        "caption": "Výška Hladiny",
        "lowerlimit": "0",
        "upperlimit": "80",
        "lowerlimitdisplay": "Prázdná",
        "upperlimitdisplay": "Plná",
        "numbersuffix": " m",
        "cylfillcolor": "#5D62B5",
        "plottooltext": "metrů vody ve studni <b>' . $row_value1_mod . ' m </b>",
        "cylfillhoveralpha": "85",
        "theme": "fusion"
      },
      "value": ' . $row_value1_mod . '
    }');

    // Render the Widget
    $Widget->render();
    $WidgetBattery->render();
    $columnChartThermometer->render();
    $columnChartCylinder->render();

        echo '<tbody>
                <tr>
                <td>' . $row_id . '</td>
                <td>' . $row_reading_time . '</td>
                <td>' . $row_value1 . '</td>
                <td>' . $row_value2 . '</td>
                <td>' . $row_value3 . '</td>
                <td>' . $row_value4 . '</td>
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
    </table>
</section>
<!-- FOOTER -->
     <footer id="footer">
          <div class="container">
               <div class="row">

                    <div class="col-md-4 col-sm-6">
                         <div class="footer-info">
                              <div class="section-title">
                                   <h2>Sídlo</h2>
                              </div>
                              <address>
                                   <p>Kounicova 46/48, 602 00 Brno-Královo Pole</p>
                              </address>

                              <ul class="social-icon">
                                   <li><a href="https://www.facebook.com/honza.antos.90" class="fa fa-facebook-square" attr="facebook icon"></a></li>
                                   <li><a href="#" class="fa fa-twitter"></a></li>
                                   <li><a href="https://www.instagram.com/_enty_/" class="fa fa-instagram"></a></li>
                              </ul>

                              <div class="copyright-text">
                                   <p>Copyright &copy; 2022 TechCrowd & Jan Antoš</p>
                              </div>
                         </div>
                    </div>

                    <div class="col-md-4 col-sm-6">
                         <div class="footer-info">
                              <div class="section-title">
                                   <h2>Kontakty</h2>
                              </div>
                              <address>
                                   <p>+420 735 549 704 </p>
                                   <p><a href="mailto:honza.ant@email.cz">honza.ant@email.cz</a></p>
                              </address>

                              <div class="footer_menu">
                                   <h2>Rychlé Odkazy</h2>
                                   <ul>
                                        <li><a href="home.php">Domů</a></li>
                                        <li><a href="https://www.techcrowd.cz/">Stránka TechCrowd</a></li>
                                        <li><a href="index.php">Naměřená data</a></li>
                                        <li><a href="contact-us.php">Kontaktujte nás</a></li>
                                   </ul>
                              </div>
                         </div>
                    </div>
               </div>
          </div>
     </footer>

     <!-- SCRIPTS -->
     <script src="js/jquery.js"></script>
     <script src="js/bootstrap.min.js"></script>
     <script src="js/owl.carousel.min.js"></script>
     <script src="js/smoothscroll.js"></script>
     <script src="js/custom.js"></script>

</body>
</html>
