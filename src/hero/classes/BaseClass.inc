<?php
namespace Heroes\hero\classes;

use Heroes\hero\Hero;

abstract class BaseClass
{
    abstract function create(Hero &$hero);
}
