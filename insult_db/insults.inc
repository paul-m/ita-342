<?php

function get_db() {
  return array(
    'db'=> 'paulm77',
    'user' => 'paulm77',
    'password' => 'paulm77',
    'host' => "ovid.u.washington.edu",
    'port' => "2900",
    'table_prefix' => '',
  );
}

function crud_insult_db_connect(&$mysqli = NULL) {
  // create a new connection if one is needed.
  // return TRUE if we created one.
  if ($mysqli) {
    return FALSE;
  }
  $db = get_db();
  $mysqli = new mysqli($db['host'], $db['user'], $db['password'], $db['db'], $db['port']);
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: " . $mysqli->connect_error;
    return FALSE;
  }
  return TRUE;
}

function crud_insult_load_all() {
  // load all insults. there aren't that many.
  $mysqli = NULL;
  crud_insult_db_connect($mysqli);
  if ($mysqli) {
    $query = $mysqli->query("SELECT * FROM insult");
    $i=0;
    $result = array();
    while($i++ < $query->num_rows) {
      $row = $query->fetch_assoc();
      $result[] = $row;
    }
    $mysqli->close();
    return $result;
  }
  // no mysqli connection, so return NULL
  return NULL;
}

function load_insults() {
  // Keep a static insult array, so we only have to query it
  // once.
  static $insults = NULL;
  if ($insults) {
    return $insults;
  }
  // Gather all the insults.
  $db_insults = crud_insult_load_all();
  // Loop through the insults and add them to the big array.
  foreach ($db_insults as $insult) {
    if ($insult['list_1']) $insults['adv1'][] = $insult['list_1'];
    if ($insult['list_2']) $insults['adj2'][] = $insult['list_2'];
    if ($insult['list_3']) $insults['noun3'][] = $insult['list_3'];
  }
  // Give them to caller.
  return $insults;
}

/*
	$insult_1 = array(1 => "artless","bawdy","beslubbering","bootless","churlish","cockered","clouted","craven","currish","dankish","dissembling","droning","errant","fawning","fobbing","froward","frothy","gleeking","goatish","gorbellied","impertienent","infectious","jarring","loggerheaded","lumpish","mammering","mangled","mewling","paunchy","pribbling","puking","puny","qualling","rank","reeky","roguish","ruttish","saucy","spleeny","spongy","surly","tottering","unmuzzled","vain","venomed","villianous","warped","wayward","weedy","yeasty");
	$insult_2 = array(1 => "base-court","bat-fowling","beef-witted","beetle-headed","boil-brained","clapper-clawed","clay-brained","common-kissing","crook-pated","dismal-dreaming","dizzy-eyed","doghearted","dread-bolted","earth-vexing","elf-skinned","fat-kidneyed","fen-sucked","flap-mouthed","fly-bitten","folly-fallen","fool-born","full-gorged","guts-griping","half-faced","hasty-witted","hedge-born","hell-hated","idle-headed","ill-breeding","ill-nurtured","knotty-pated","milk-livered","motley-minded","onion-eyed","plume-plucked","pottle-deep","pox-marked","reeling-ripe","rough-hewn","rude-growing","rump-fed","shard-borne","sheep-biting","spur-galled","swag-bellied","tardy-gaited","tickle-brained","toad-spotted","unchin-snouted","weather-bitten");
	$insult_3 = array(1 => "apple-john","baggage","barnacle","bladder","boar-pig","bugbear","bum-bailey","canker-blossom","clack-dish","clotpole","coxcomb","codpiece","death-token","dewberry","flap-dragon","flax-wench","flirt-gill","foot-licker","fustilarian","giglet","gudgeon","haggard","harpy","hedge-pig","horn-beast","hugger-mugger","joithead","lewdster","lout","maggot-pie","malt-worm","mammet","measle","minnow","miscreant","moldwarp","mimble-news","nut-hook","pigeon-egg","pignut","puttock","pumpion","ratsbane","scut","skainsmate","strumpet","varlet","vassal","whey-face","wagtail");
*/
