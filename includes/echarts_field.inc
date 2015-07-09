<?php


/**
* Based on addAxisX by Randall Sibaja R.
**/
function echarts_field_get_data_from_json($key, $json){
  
  $output = array();
  
  foreach($json->values as $row){
    $output[] = $row->$key;
  }

  return $output;

}

/**
* Based on createSeries by Randall Sibaja R.
**/
function echarts_field_get_series($xaxis, $series, $data, $graph_type, $showvalue = ''){

  $output = array();

  if( ($graph_type == 'pie') || ($graph_type == 'funnel') ){
    
    foreach($data->values as $row){
      if(in_array($row->$xaxis, $series)){
        $output[] = array(
          'name' => $row->$xaxis,
          'value' => str_replace(',', '.', $row->$showvalue),
        );
      }
    }

  }else if ( ($graph_type == 'bar') || ($graph_type == 'line') ){
      
    foreach ($series as $key => $v){
    
      $data_temp = array();
      
      foreach($data->values as $row){
        $data_temp[] = str_replace(',', '.', $row->$v);
      }

      $mark = array(
        'data' => array(
          'type' => 'average',
          'name'=> 'Promedio',
        )
      );

      $output[] = array(
        'name' => $v,
        'type'=> $graph_type,
        'markPoint' => $mark,
        'data'=> $data_temp
      );

    }
  }

  return $output;
  
}


/**
* Based on createBarLineChart by Randall Sibaja R.
**/
function echarts_field_generate_setting_bar_line_graph($json, $xaxis, $series, $type, $title = ''){

  $output = array(
    'chartType' => $type,
    'useType' => array($type),
    'containerId' => 'barline_chart',
    'options' => array(
        'tooltip' => array('trigger' => 'axis'),          
        'title' => array('text' => $title),
        'legend' => array(
        'data' => $series,
        'orient' => 'horizontal',
        ),
        'toolbox' => array(
            'show' => TRUE,
            'feature' => array(
              'mark' => array('show' => TRUE, 'title' => array('mark' => 'Marcar', 'markUndo' => 'Deshacer','markClear' => 'Limpiar Marcas')),
              'dataView' => array(
              'show' => TRUE,
              'readOnly' => false,
              'title' => 'Ver Datos',
              'lang' => array('Datos', 'Regresar', '')          
              ),
            'restore' => array('show' => TRUE, 'title' => 'Refrescar'),
            'saveAsImage' => array('show' => TRUE, 'title' => 'Guardar', 'type' => 'png'),
          )
        ),
        'dataZoom' => array(
            'show' => true,
            'realtime' => true,
            'start' => 10,
            'end' => 100
        ),
      'calculable' => true,
      'xAxis' => array(
          '0' => array(
            'type' => 'category',
            'data' => echarts_field_get_data_from_json($xaxis, $json)
          )
      ),
      'yAxis' => array(
        '0' => array(
          'type' => 'value'
        )
      ),
      'series' => echarts_field_get_series($xaxis, $series, $json, $type),
    )
  );

  return $output;

}