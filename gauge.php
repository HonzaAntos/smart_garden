<?php
    /* Include the ../src/fusioncharts.php file that contains functions to embed the charts.*/
    include("fusioncharts.php");
?>
<html>
    <head>
        <title>FusionCharts | My First Widget</title>

        <script src="https://cdn.fusioncharts.com/fusioncharts/latest/fusioncharts.js"></script>

        <script src="https://cdn.fusioncharts.com/fusioncharts/latest/themes/fusioncharts.theme.fusion.js"></script>
    </head>
    <body>

<?php
// Widget appearance configuration
$arrChartConfig = array(
"chart" => array(
"caption" => "Humidity",
"lowerLimit" => "0",
"upperLimit" => "100",
"showValue" => "1",
"numberSuffix" => "%",
"theme" => "fusion",
"showToolTip" => "0"
)
);

    // Widget color range data
    $colorDataObj = array("color" => array(
        ["minValue" => "75", "maxValue" => "100", "code" => "#F2726F"],
        ["minValue" => "50", "maxValue" => "75", "code" => "#FFC533"],
        ["minValue" => "0", "maxValue" => "50", "code" => "#62B58F"]
    ));

    // Dial array
    $dial = array();

    // Widget dial data in array format, multiple values can be separated by comma e.g. ["81", "23", "45",...]
    $widgetDialDataArray = array("20,81,23,98");
    for($i = 0; $i < count($widgetDialDataArray); $i++) {
        array_push($dial,array("value" => $widgetDialDataArray[$i]));
    }

    $arrChartConfig["colorRange"] = $colorDataObj;
    $arrChartConfig["dials"] = array( "dial" => $dial);

    // JSON Encode the data to retrieve the string containing the JSON representation of the data in the array.
    $jsonEncodedData = json_encode($arrChartConfig);

    // Widget object
    $Widget = new FusionCharts("angulargauge", "MyFirstWidget" , "400", "250", "widget-container", "json", $jsonEncodedData);

    // Render the Widget
    $Widget->render();

?>
<center>
<div id="widget-container">Widget will render here!</div>
</center>
</body>
</html>