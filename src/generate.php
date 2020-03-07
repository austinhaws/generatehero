<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

// composer autoloading
require_once __DIR__.'/../vendor/autoload.php';


try {
    // generate a character and output the json
    echo json_encode((new \Heroes\HeroGenerator())->generate($_GET));
} catch (Exception $e) {
    echo $e->getMessage();
}
