<?php
namespace Heroes\hero\insanity;

class Insanity
{
    public $type;
    public $description;

    function __construct($type, $description)
    {
        $this->type = $type;
        $this->description = $description;
    }

}