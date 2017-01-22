<?php
error_reporting(E_ALL);
ini_set('display_errors', 1);

// composer autoloading
require_once __DIR__.'/vendor/autoload.php';


// generate a character and output the json
echo (new \Heroes\HeroGenerator())->generate();
