<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

include 'classes/HeroGenerator.inc';

$heroGenerator = new HeroGenerator();
$character = $heroGenerator->generate();

echo json_encode($character);

echo 'dont forget unit tests';