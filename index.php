<?php 

header("Access-Control-Allow-Origin: *");
header('Access-Control-Allow-Methods: POST, GET, OPTIONS');

require __DIR__ . '/src/generate.php';
