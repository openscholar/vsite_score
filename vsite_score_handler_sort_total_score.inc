<?php
class vsite_score_handler_sort_total_score extends views_handler_sort {
  function query() {
    $sort_select = '(SELECT SUM(energy) FROM {radioactivity} AS vs_r
  														INNER JOIN {node} AS vs_n ON vs_r.id = vs_n.nid
  														INNER JOIN {og_ancestry} AS vs_og USING (nid)
  														WHERE vs_og.group_nid = n.nid)';


    $this->query->add_orderby(NULL, $sort_select, $this->options['order'], 'total_score');
  }
}