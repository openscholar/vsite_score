<?php

function vsite_score_views_data() {
  require_once drupal_get_path('module', 'radioactivity') .'/radioactivity.inc';

  $data=array();

  foreach (radioactivity_get_decay_profiles() as $dpid => $decay_profile) {
    // s = sort, f = field
    $table_alias='radioactivity_vsite_'. $dpid;
    $data[$table_alias]['table']['group']=t('Radioactivity (@e)', array('@e' => $decay_profile['label']));
    $data[$table_alias]['table']['title']=t('Vsite energy');
    $data[$table_alias]['table']['help']=t('Vsite radioactive energy in decay profile @e.', array('@e' => $decay_profile['label']));

    // join to node
    $data[$table_alias]['table']['join']['node'] =
      array('left_field' => 'nid',
            'field' => 'id',
            'table' => 'radioactivity',
            'extra' => array(array('field' => 'class',
                                   'value' => 'vsite'),
                             array('field' => 'decay_profile',
                                   'value' => $dpid,
                                   'numeric' => TRUE)));

    $data[$table_alias]['energy'] = array(
      'title' => t('Vsite score'),
      'help' => t('The total score of the Vsite.'),
      'sort' => array(
      	'views_handler_sort'
     	),
    );
  }

  return $data;
}
