<?php 

if($_SERVER['REQUEST_METHOD'] == "OPTIONS") {
    header("Access-Control-Allow-Origin: *");
    header('Access-Control-Allow-Methods: POST, GET, OPTIONS');
    header("Content-Length: 0");
    header("Content-Type: text/plain");
    exit();
}

require __DIR__ . '/src/generate.php';
