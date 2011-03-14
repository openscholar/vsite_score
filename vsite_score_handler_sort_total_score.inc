<?php
class vsite_score_handler_sort_total_score extends views_handler_sort {

  function option_definition() {
    $options = array();

    $options['decay_profile'] = array('default' => '1');
    $options['order'] = array('default' => 'DESC');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $options = array();
    $dp = radioactivity_get_decay_profiles();
    foreach ($dp as $k => $p) {
      $options[$k] = $p['label'];
    }
    $form['decay_profile'] = array (
      '#type' => 'select',
      '#title' => t('Decay Profile'),
      '#options' => $options,
      '#default_value' => $this->options['decay_profile'],
    );
  }

  function query() {/*
    $sort_select = '(SELECT SUM(energy) FROM {radioactivity} AS vs_r
  														INNER JOIN {node} AS vs_n ON vs_r.id = vs_n.nid
  														INNER JOIN {og_ancestry} AS vs_og USING (nid)
  														WHERE vs_og.group_nid = n.nid)';
*/
    $sort_select = '(SELECT energy FROM {radioactivity} WHERE class="vsite" AND decay_profile = '.$this->options['decay_profile'].' AND id = node.nid)';

    $this->query->add_orderby(NULL, $sort_select, $this->options['order'], 'total_score');
  }
}